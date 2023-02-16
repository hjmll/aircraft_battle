#include "game.h"
#include "iostream"
#include <fstream>
#include <graphics.h>
#include <mmsystem.h>
#include <ctime>

#pragma comment(lib,"winmm.lib")

// 负责人：技术官
Game::Game()
{
	bestScore = 0;
	this->fps = 60;			// 默认 60 帧
	score = 0;
	enemyCD = fps / 2;		// 最高每秒 2 发
	defualtCD = fps;	// 每 1 秒添加一个敌
	bossCD = 0;				// 不知道是啥
}


// 负责人：技术官
Game::Game(int fps)
{
	bestScore = 0;
	this->fps = fps;
	score = 0;
	enemyCD = fps/2;	// 最高每秒 2 发
	defualtCD = fps;	// 每 1 秒添加一个敌人
	bossCD = 0;			// 不知道是啥

}

void Game::run()
{
	initgraph(Width, Length);
	Page nextPage = Game::MENU; // 启动游戏时，默认进入菜单页  
	/*
	* showXxxx()函数负责展示对应界面，其返回值为下一个页面的枚举值
	* 例如，启动游戏时首先进入MENU页面，接下来玩家点击开始游戏
	* 则MENU页面退出，返回值为GAME，于是下一个展示的页面为游戏页面
	* 而后玩家又点击暂停，于是GAME页面退出，返回值为PAUSE，下一个展示的页面为暂停页面
	* 以此类推...
	*/
	while (true) {
		switch (nextPage){
		case MENU:
			nextPage = showMenu();
			break;
		case GAME:
			nextPage = showGame();
			break;
		case PAUSE:
			nextPage = showPause();
			break;
		case WIN:
			nextPage = showWin();
			break;
		case LOSE:
			nextPage = showLose();
			break;
		case RULE1:
			nextPage = showRule1();
			break;
		case RULE2:
			nextPage = showRule2();
			break;
		case DEVELOPER:
			nextPage = showDeveloper();
			break;
		}
	}
}


/*
* 负责人：
* 功能：初始化游戏数据
*	如敌人、子弹数量清零，buff清零，血量重设为3等...
* 参数：void
* 返回值：void
*/
void Game::init()
{
	enemyCD = 30;//第一个敌人30*16毫秒后生成
	bossCD = 15000;
	attackCD = 5;
	enemyAttackCD = 30;
	score = 0;
}

/*
* 发射子弹
* 
* 
*/
void Game::playerAttack()
{
	int b_num = 0;
	double angle = 0;
	if (attackCD <=0)
	{
		Point p_pos[5];
		if (player.getHp() > 70)
		{
			//当生命值大于5时，在飞机坐标位置生成一枚子弹，角度为90度(后期慢慢调)，速度为玩家飞机速度+10，子弹归属为玩家，发射默认子弹
			b_num = 1;
			for (int i = 0; i < b_num; i++)
			{
				p_pos[i] = player.getPos();
				p_pos[i].x = p_pos[i].x + E_Wideh / 2 - B_Width / 2;
				p_pos[i].y = p_pos[i].y - B_Width;
				bullets.addBullet(p_pos[i], -90, p_speed + 10, Bullet::BASKERBALL, Bullet::PLAYER);
			}
   			attackCD = 5;
		}
		else if (player.getHp() > 40)
		{
			b_num = 3;
			angle = 45;
			p_pos[2] = player.getPos();
			p_pos[1].x = p_pos[2].x + E_Wideh / 2 - B_Width / 2;
			p_pos[1].y = p_pos[2].y - B_Width;
			p_pos[0].x = p_pos[2].x + (E_Wideh / 2 - B_Width / 2) * 2;
			p_pos[0].y = p_pos[2].y;
			for (int i = 0; i < b_num; i++)
			{
				bullets.addBullet(p_pos[i], -angle * (i + 1), p_speed + 10, Bullet::BASKERBALL, Bullet::PLAYER);
			}
			attackCD = 10;
		}
		else
		{
			b_num = 5;
			angle = 30;
			p_pos[4].x = player.getPos().x - (E_Wideh / 2 - B_Width / 2);
			p_pos[4].y = player.getPos().y + B_Width * 2;
			p_pos[3] = player.getPos();
			p_pos[2].x = p_pos[3].x + (E_Wideh / 2 - B_Width / 2);
			p_pos[2].y = p_pos[3].y - B_Width;
			p_pos[1].x = p_pos[3].x + (E_Wideh / 2 - B_Width / 2) * 2;
			p_pos[1].y = p_pos[3].y;
			p_pos[0].x = p_pos[4].x + (E_Wideh / 2 - B_Width / 2) * 4;
			p_pos[0].y = p_pos[4].y;
			for (int i = 0; i < b_num; i++)
			{
				bullets.addBullet(p_pos[i], -angle * (i + 1), p_speed + 10, Bullet::BASKERBALL, Bullet::PLAYER);
			}
			attackCD = 10;
		}
	}
}


/*
* 负责人：傅全有
* 功能：敌机攻击
*	根据敌机类型，在敌机坐标（getPos()函数）附近生成子弹
*	散射也在此处实现，例如5发散射，则同时生成5个不同位置不同方向的子弹
* 参数：void
* 返回值：void
*/
void Game::enemyAttack()
{
	int b_num = 0;
	double angle = 0;
	for (int i = 0; i < enemys.getNum(); ++i) {
		Point e_pos[5];
		switch (enemys.getEnemy(i).getType())
		{
		case Enemys::NORMAL_A:
		case Enemys::E_GREEN:
		case Enemys::E_RED:
			break;
		case Enemys::NORMAL_B:
			b_num = 1;
			for (int j = 0; j < b_num; j++)
			{
				e_pos[j] = enemys.getEnemy(i).getPos();
				e_pos[j].x = e_pos[j].x + E_Wideh / 2 - B_Width / 2;
				e_pos[j].y = e_pos[j].y + E_Height;
				bullets.addBullet(e_pos[j], 90, p_speed + 10, Bullet::BULLET1, Bullet::ENEMY);
			}
			enemyAttackCD = 30;
			break;
		case Enemys::BOSS:
			b_num = 5;
			angle = 360;
			for (int j = 0; j < b_num; j++)
			{
				e_pos[j] = enemys.getEnemy(i).getPos();
				e_pos[j].x = e_pos[j].x + E_Wideh / 2 - B_Width / 2;
				e_pos[j].y = e_pos[j].y - B_Width;
				bullets.addBullet(e_pos[j], angle / (i + 1), p_speed - 5, Bullet::BASKERBALL, Bullet::ENEMY);
			} 
			enemyAttackCD = 30;
			break;
		}
	}
}

/*
* 负责人：易骏清
* 功能：尝试生成新敌机
*	如果enemyCD不为零，则CD值-1
*	如果enemyCD为零，则enemyCD = defualtCD，在随机x处生成敌机
* 参数：void
* 返回值：void
*/
void Game::addEnemy()
{
	int type = 0;
	srand((unsigned)time(0));
	Point e_pos;
	Enemy t_enemy;
	type = rand() % 4;//随机生成
	 if (bossCD == 0)
	 {
		 e_pos.x = rand() % (Width / 2 - E_Wideh*2);
		 e_pos.y = -E_Height*2;
		 enemys.addEnemy(e_pos, 90, 4, t_enemy.BOSS);
		 enemyCD = defualtCD;
	 }
	 else
	 {
		 enemyCD--;
		 bossCD--;
		 if (enemyCD == 0)
		 {
			 if (type == 0)//生成红色敌机
			 {
				 e_pos.x = rand() % (Width  - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.E_RED);
				 enemyCD = defualtCD;
			 }
			 else if (type == 1)//生成绿色敌机
			 {
				 e_pos.x = rand() % (Width  - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.E_GREEN);
				 enemyCD = defualtCD;
			 }
			 else if (type == 2)//生成普通敌机
			 {
				 e_pos.x = rand() % (Width  - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.NORMAL_A);
				 enemyCD = defualtCD;
			 }
			 else if (type == 3)//生成会射击的敌机
			 {
				 e_pos.x = rand() % (Width  - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.NORMAL_B);
				 enemyCD = defualtCD;
				 enemyAttackCD = 30;
			 }
		 }
	 }
}

/*
* 负责人：
* 功能：碰撞检测，核心函数
*	1. 枚举所有子弹
*		1) 如果为敌方子弹，判断是否与玩家飞机相撞（通过二者距离判断）
*		   如果相撞且无敌buff时间为0，删除子弹，玩家根据子弹类型受到伤害
		   如果受伤后生命值小于0，则return LOSE
*		   如果受伤后生命值大于0，则获得无敌buff
*		2) 如果为我方子弹，枚举敌方所有飞机，分别判断是否与敌机碰撞
*		   如果与敌机相撞，删除子弹，敌机根据子弹受到伤害
		   如果受伤后生命值小于0，则视为敌机被击落，根据敌机类型获得buff
		   如果被击落的敌机为BOSS类型，则return WIN
	2. 枚举所有敌机，判断是否与玩家相撞，之后的逻辑同上

* 参数：void
* 返回值：0. 游戏继续 1. 胜利 2. 失败
*/
int Game::checkCrash()
{
	// 子弹碰撞
	for (int i = 0; i < bullets.getNum(); i++) {
		//Bullet b = bullets.getBullet(i);
		if (bullets.getBullet(i).getBelone() == Bullet::Belone::ENEMY) {
			if (player.getBuffTime(Player::unbreakable) > 0) {
				continue; // 无敌时间，不计算碰撞
			}
			if (max(fabs(bullets.getBullet(i).getPos().x - player.getPos().x), fabs(bullets.getBullet(i).getPos().y - player.getPos().y)) < 50) {
				// 切雪比夫距离小于60视为碰撞
				bullets.delBullet(i); // 删除子弹
				player.hurt(20); // 掉血量为20，待调整
				cout << player.getHp() << endl;
				if (player.getHp() <= 0) {
					return 2; // 失败
				}
				player.addBuff(Player::unbreakable, 120); // 获得120帧无敌时间
			}
		}
		else {
			for (int j = 0; j < enemys.getNum(); j++) {
				//Enemy e = enemys.getEnemy(j);
				if (max(fabs(bullets.getBullet(i).getPos().x - enemys.getEnemy(j).getPos().x), fabs(bullets.getBullet(i).getPos().y - enemys.getEnemy(j).getPos().y)) < 60 && bullets.getBullet(i).getBelone() == Bullet::Belone::PLAYER) {
					bullets.delBullet(i); // 删除子弹
					enemys.getEnemy(j).hurt(20); // 掉血量为20，待调整
					if (enemys.getEnemy(j).getHp() <= 0) {
						mciSendString("close ../飞机资料/battlemusic/kill2_1.mp3", NULL, 0, NULL);
						mciSendString("play ../飞机资料/battlemusic/kill2_1.mp3", NULL, 0, NULL);
						enemys.delEnemy(j); // 敌机被击落
						// 此处添加玩家飞机buff
					}
				}
			}
		}
	}

	// 敌我碰撞
	for (int i = 0; i < enemys.getNum(); i++) {
		//Enemy e = enemys.getEnemy(i);
		if (player.getBuffTime(Player::unbreakable) > 0) {
			continue; // 无敌时间，不计算碰撞
		}
		if (max(fabs(enemys.getEnemy(i).getPos().x - player.getPos().x), fabs(enemys.getEnemy(i).getPos().y - player.getPos().y)) < 80) {
			// 切雪比夫距离小于80视为碰撞
			player.hurt(20); // 掉血量为1，待调整
			enemys.getEnemy(i).hurt(20);
			cout << player.getHp() << endl;
			if (player.getHp() <= 0) {
				return 2; // 失败
			}
			if (enemys.getEnemy(i).getHp() <= 0) {
				enemys.delEnemy(i); // 敌机被击落
				// 此处添加玩家飞机buff
			}
			player.addBuff(Player::unbreakable, 120); // 获得120帧无敌时间
		}
	}
	return 0;
}

/*
	负责人：傅全有
	功能：按键检测及偏移量修改
		1.按下 w/W -> y轴偏移减小3
		2.按下 s/S -> y轴偏移增加3
		3.按下 a/A -> x轴偏移减小2
		4.按下 d/D -> x轴偏移增加2

	参数：
		int &p_x 原始x坐标
		int &p_y 原始y坐标'
	返回值:
		void
*/
void Game::checkKeyDown(int& p_x, int& p_y)
{
	if (GetAsyncKeyState('W')) {
		p_y -= p_speed;
	}
	if (GetAsyncKeyState('S')) {
		p_y += p_speed;
	}
	if (GetAsyncKeyState('A')) {
		p_x -= p_speed;
	}
	if (GetAsyncKeyState('D')) {
		p_x += p_speed;
	}
	if (GetAsyncKeyState(VK_ESCAPE)) 
	{
		if (showPause() == MENU)
		{
			showMenu();
		}
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		mciSendString("close ../飞机资料/battlemusic/shoot_1.mp3", NULL, 0, NULL);
		playerAttack();
	}
}

/*
* 负责人：贺金梅
* 功能：展示菜单页
*	- 开始游戏：return GAME
*	- 游戏规则：return RULE（扩展）
*	- 开发人员：return DEVELOPER（扩展）
*	- 退出游戏：直接调用 exit(0);
* 参数：void
* 返回值：GAME::Page，下一个页面的枚举值
*/
Game::Page Game::showMenu()
{
	cleardevice();
	init();
	IMAGE image;
	//打印背景图
	loadimage(&image, "../原型图/菜单/menu.png", Width, Length);
	putimage(0, 0, &image);
	//solidrectangle(790, 310, 920, 450);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x < 230 && m.x>70 && m.y < 450 && m.y>310) {//开始游戏
				return GAME;
				m.message = NULL;
			}
			if (m.x < 420 && m.x>300 && m.y < 450 && m.y>310) {//游戏规则
				return RULE1;
				m.message = NULL;
			}
			if (m.x < 670 && m.x>550 && m.y < 450 && m.y>310) {//开发人员介绍
				return DEVELOPER;
				m.message = NULL;
			}
			if (m.x < 920 && m.x>790 && m.y < 450 && m.y>310) {//退出游戏
				exit(0);
				m.message = NULL;
			}
		}

	}

	return MENU;
}

/*
* 负责人：易骏清
* 功能：展示游戏页面，游戏核心流程
*	- 移动、攻击、生成敌人、碰撞检测、胜利判断、死亡判断
* 参数：void
* 返回值：GAME::Page，下一个页面的枚举值
*/
Game::Page Game::showGame()
{
	mciSendString("open ../飞机资料/battlemusic/zhandou_1.mp3", NULL, 0, NULL);
	mciSendString("open ../飞机资料/battlemusic/shoot_1.mp3", NULL, 0, NULL);
	mciSendString("open ../飞机资料/battlemusic/kill2_1.mp3", NULL, 0, NULL);


	mciSendString("play ../飞机资料/battlemusic/zhandou_1.mp3 repeat", NULL, 0, NULL);
	closegraph();
	int bk_speed;//背景图的移到速度
	bk_speed = 3;
	initgraph(Width, Length,SHOWCONSOLE);
	int bk_y = -Length;
	IMAGE bk;
	IMAGE p_img[2];
	Point p_pos;
	loadimage(&bk, "../飞机资料/bk/OUT.png",Width,Length*2);
	loadimage(&p_img[0], "../飞机资料/player/At1.jpg", E_Wideh, E_Height);
	loadimage(&p_img[1], "../飞机资料/player/At2.jpg", E_Wideh, E_Height);

	p_pos.x = Width / 2 - E_Wideh/2;
	p_pos.y = Length - E_Height;

	setbkcolor(BLACK);
	setbkmode(TRANSPARENT);

	while (true) {
		BeginBatchDraw();

		bk_y += bk_speed;
		if (bk_y == 0)
		{
			bk_y = -Length;
		}
		putimage(0, bk_y, &bk);
		attackCD--;
		enemyAttackCD--;
		bossCD--;
		checkKeyDown(p_pos.x, p_pos.y);
		p_pos = player.playermove(p_pos.x, p_pos.y);
		putimage(p_pos.x, p_pos.y, &p_img[0],SRCAND);
		putimage(p_pos.x, p_pos.y, &p_img[1],SRCPAINT);


		if (bossCD >= 0)
		{
			addEnemy();
		}
		enemys.move();

		//敌人攻击
		if (enemyAttackCD <= 0) {
			enemyAttack();
		}
		bullets.move();
		mciSendString("play ../飞机资料/battlemusic/shoot_1.mp3", NULL, 0, NULL);

		// 碰撞检测
		switch (checkCrash()) {
		case 0:
			break;
		case 1:
			mciSendString("close ../飞机资料/battlemusic/zhandou_1.mp3 repeat", NULL, 0, NULL);
			return WIN;
		case 2:
			mciSendString("close ../飞机资料/battlemusic/zhandou_1.mp3 repeat", NULL, 0, NULL);
			EndBatchDraw();
			return LOSE;
		}

		Sleep(16);

		// 玩家、敌人、子弹移动
		//enemys.move();
		//bullets.move();

		//// 玩家、敌人攻击
		//player.attack();
		//enemys.attack();

		//// 生成新敌机
		//addEnemy();
		//
		//// 碰撞检测
		//checkCrash();

		// 渲染页面：获取玩家、敌机、子弹坐标等信息，绘制页面
		settextstyle(32, 0, _T("黑体"));
		outtextxy(788, 0, _T("当前分数："));
		char s[5];
		sprintf_s(s, "%d", score);
		outtextxy(950, 0, s);

		outtextxy(0, 720, _T("当前生命："));
		char t[5];
		sprintf_s(t, "%d", player.getHp());
		outtextxy(160, 720, t);


		EndBatchDraw();

	}
}

/*
* 负责人：贺金梅
* 功能：展示暂停页
*	- 继续游戏：return GAME
*	- 重新开始：先调用init()初始化游戏数据，而后return GAME
*	- 游戏规则：return RULE（扩展）
*	- 返回菜单：return MENU
* 参数：void
* 返回值：GAME::Page，下一个页面的枚举值
*/
Game::Page Game::showPause()
{
	EndBatchDraw();//先停止批量绘图
	cleardevice();
	IMAGE image1;
	//打印暂停页面
	loadimage(&image1, "../原型图/game/暂停.png", Width, Length);
	putimage(0, 0, &image1);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x < 500 && m.x>365 && m.y < 335 && m.y>183) {//继续游戏
					return GAME;
					m.message = NULL;
				}
				if (m.x < 765 && m.x>645 && m.y < 467 && m.y>330) {//返回菜单
					return MENU;
					m.message = NULL;
				}

				if (m.x < 500 && m.x>365 && m.y < 615 && m.y>467) {//退出游戏
					exit(0);
					m.message = NULL;
				}
			}
		}

	}
	return MENU;
}

/*
* 负责人：
* 功能：展示游戏胜利页
*	首先初始化游戏数据，调用init()
*	记录最好成绩
*	- 再来一局：return GAME
*	- 返回菜单：return MENU
* 参数：void
* 返回值：GAME::Page，下一个页面的枚举值
*/
Game::Page Game::showWin()
{
	init();
	cleardevice();
	ofstream outfile;// 以写模式打开文件
	outfile.open("scorlist.txt");//打开成绩记录文件
	outfile << score << endl;//将当前成绩写入文件并保存
	outfile.close();//关闭文件
	ifstream infile("scorlist.txt", ios::in);//从成绩记录文件读取信息
	int a;
	while (infile >> a)//在文件中遍历查找最高分，当达到文件尾，则循环处理结束。
	{
		if (a > bestScore)
			bestScore = a;
	}
	if (score == bestScore)//如果当前成绩是最高分，打印最高分界面
	{
		IMAGE bestwin;
		loadimage(&bestwin, "../原型图/game/win1.png", 1024, 768);
		putimage(0, 0, &bestwin);
		ExMessage m;
		while (1)
		{
			m = getmessage(EX_MOUSE);
			if (m.message == WM_LBUTTONDOWN)
			{
				if (m.x < 270 && m.x>160 && m.y < 397 && m.y>343)//重新游戏
				{
					return GAME;
					m.message = NULL;
				}
				if (m.x < 270 && m.x>160 && m.y < 487 && m.y>433)//返回菜单
				{
					return MENU;
					m.message = NULL;
				}
				if (m.x < 270 && m.x>160 && m.y < 650 && m.y>575)//退出游戏
				{
					exit(0);
					m.message = NULL;
				}
			}
			return MENU;
		}
	}
	else//如果当前成绩不是最高分，打印普通界面
	{
		IMAGE bestwin;
		loadimage(&bestwin, "../原型图/game/win2.png", 1024, 768);
		putimage(0, 0, &bestwin);
		ExMessage m;
		while (1)
		{
			m = getmessage(EX_MOUSE);
			if (m.message == WM_LBUTTONDOWN)
			{
				if (m.x < 270 && m.x>160 && m.y < 397 && m.y>343)//重新游戏
				{
					return GAME;
					m.message = NULL;
				}
				if (m.x < 270 && m.x>160 && m.y < 487 && m.y>433)//返回菜单
				{
					return MENU;
					m.message = NULL;
				}
				if (m.x < 270 && m.x>160 && m.y < 577 && m.y>523)//退出游戏
				{
					exit(0);
					m.message = NULL;
				}
			}
			return MENU;
		}
	}
	return MENU;
}

/*
* 负责人：贺金梅
* 功能：展示游戏失败页
*	首先初始化游戏数据，调用init()
*	- 再来一局：return GAME
*	- 返回菜单：return MENU
* 参数：void
* 返回值：GAME::Page，下一个页面的枚举值
*/
Game::Page Game::showLose()
{
	init();
	cleardevice();
	IMAGE image6;
	//打印失败页面
	loadimage(&image6, "../原型图/game/游戏失败.png", 1024, 768);
	putimage(0, 0, &image6);
	//solidrectangle(160, 343, 270, 397);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x < 270 && m.x>160 && m.y < 397 && m.y>343) {//重新游戏
				return GAME;
				m.message = NULL;
			}
			if (m.x < 270 && m.x>160 && m.y < 487 && m.y>433) {//返回菜单
				return MENU;
				m.message = NULL;
			}

			if (m.x < 270 && m.x>160 && m.y < 577 && m.y>523) {//退出游戏
				exit(0);
				m.message = NULL;
			}
		}

	}
}


/*
* 功能：展示规则1
* 可以切换
*/
Game::Page Game::showRule1()
{
	cleardevice();
	IMAGE image3;
	//打印规则介绍页面
	loadimage(&image3, "../原型图/菜单/rule1.png", 1024, 768);
	putimage(0, 0, &image3);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 860 && m.x>785 && m.y < 522 && m.y>453) {//返回菜单
				return MENU;
				m.message = NULL;
			}

			if (m.x < 988 && m.x>896 && m.y < 522 && m.y>453) {//下一页
				return RULE2;
				m.message = NULL;
			}
		}
	}
}

/*
* 功能：展示规则2
* 可以切换
*/
Game::Page Game::showRule2()
{
	cleardevice();
	IMAGE image4;
	loadimage(&image4, "../原型图/菜单/rule2.png", 1024, 768);
	putimage(0, 0, &image4);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 775 && m.x>698 && m.y < 580 && m.y>515) {//返回菜单
				return MENU;
				m.message = NULL;
			}
			if (m.x < 940 && m.x>848 && m.y < 580 && m.y>515) {//返回上一页
				return RULE1;
				m.message = NULL;
			}
		}
	}
}

/*
* 功能：展示开发人员名单
*/
Game::Page Game::showDeveloper()
{
	cleardevice();
	char s[] = "返回主菜单";
	IMAGE image5;
	loadimage(&image5, "../原型图/菜单/developers.png", 1024, 768);
	putimage(0, 0, &image5);
	outtextxy(10, 35, s);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 90 && m.x>10 && m.y < 50 && m.y>35) {//返回菜单
				return MENU;
				m.message = NULL;
			}
			if (m.x < 940 && m.x>848 && m.y < 580 && m.y>515) {//返回上一页
				return RULE1;
				m.message = NULL;
			}
		}
	}
	return MENU;
}