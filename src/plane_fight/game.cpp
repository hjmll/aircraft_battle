#include "game.h"
#include "iostream"
#include<graphics.h>
#include<ctime>
#define Width 1024
#define Length 768

// 负责人：技术官
Game::Game()
{
	bestScore = 0;
	this->fps = 60;			// 默认 60 帧
	score = 0;
	enemyCD = fps / 2;		// 最高每秒 2 发
	defualtCD = 5 * fps;	// 每 5 秒添加一个敌
	bossCD = 0;				// 不知道是啥
}


// 负责人：技术官
Game::Game(int fps)
{
	bestScore = 0;
	this->fps = fps;
	score = 0;
	enemyCD = fps/2;	// 最高每秒 2 发
	defualtCD = 5*fps;	// 每 5 秒添加一个敌人
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
		 enemyCD = 100;
	 }
	 else
	 {
		 enemyCD--;
		 bossCD--;
		 if (enemyCD == 0)
		 {
			 if (type == 0)//生成红色敌机
			 {
				 e_pos.x = rand() % (Width / 2 - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.E_RED);
				 enemyCD = 100;
			 }
			 else if (type == 1)//生成绿色敌机
			 {
				 e_pos.x = rand() % (Width / 2 - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.E_GREEN);
				 enemyCD = 100;
			 }
			 else if (type == 2)//生成普通敌机
			 {
				 e_pos.x = rand() % (Width / 2 - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.NORMAL_A);
				 enemyCD = 100;
			 }
			 else if (type == 3)//生成会射击的敌机
			 {
				 e_pos.x = rand() % (Width / 2 - E_Wideh);
				 e_pos.y = -E_Height;
				 enemys.addEnemy(e_pos, 90, 4, t_enemy.NORMAL_B);
				 enemyCD = 100;
			 }
		 }
	 }
	 //if (R_CD <= 0)
	 //{
		// e_pos.x = rand() % Width;
		// e_pos.y = 0;
		// enemys.addEnemy(e_pos, 90, 0.1, t_enemy.E_RED);
		// enemyCD = 150;
		// R_CD = 500;
	 //}
	 //if (G_CD <= 0)
	 //{
		// e_pos.x = rand() % Width;
		// e_pos.y = 0;
		// enemys.addEnemy(e_pos, 90, 0.1, t_enemy.E_GREEN);
		// enemyCD = 150;
		// G_CD = 800;
	 //}
	 //if (shoot_CD <= 0)
	 //{
		// e_pos.x = rand() % Width;
		// e_pos.y = 0;
		// enemys.addEnemy(e_pos, 90, 0.15, t_enemy.NORMAL_B);
		// shoot_CD = 600;
	 //}
	 //if (enemyCD <= 0)
	 //{
		// e_pos.x = rand() % Width;
		// e_pos.y = 0;
		// enemys.addEnemy(e_pos, 90, 0.15, t_enemy.NORMAL_A);
		// enemyCD = 150;
	 //}
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
* 返回值：void
*/
void Game::checkCrash()
{

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
		p_y -= 5;
	}
	if (GetAsyncKeyState('S')) {
		p_y += 5;
	}
	if (GetAsyncKeyState('A')) {
		p_x -= 5;
	}
	if (GetAsyncKeyState('D')) {
		p_x += 5;
	}
	if (GetAsyncKeyState(VK_ESCAPE)) 
	{
		showPause();
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		player.attack();
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
			if (m.x < 670 && m.x>530 && m.y < 450 && m.y>310) {//开发人员介绍
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
	closegraph();
	int bk_speed;//背景图的移到速度
	bk_speed = 3;
	initgraph(Width / 2, Length);
	int bk_y = -Length;
	int p_x, p_y;
	IMAGE bk;
	IMAGE p_img[2];
	loadimage(&bk, "../飞机资料/bk/tbk.png",Width/2,Length*2);
	loadimage(&p_img[0], "../飞机资料/player/At1.jpg");
	loadimage(&p_img[1], "../飞机资料/player/At2.jpg");
	//setbkmode(TRANSPARENT);
	p_x = Width / 4 - p_img[1].getwidth() / 2;
	p_y = Length - p_img[1].getheight();
	while (true) {
		BeginBatchDraw();

		bk_y += bk_speed;
		if (bk_y == 0)
		{
			bk_y = -Length;
		}
		putimage(0, bk_y, &bk);
		checkKeyDown(p_x, p_y);
		putimage(p_x, p_y, &p_img[0],SRCAND);
		putimage(p_x, p_y, &p_img[1],SRCPAINT);


		addEnemy();
		enemys.move();

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
		EndBatchDraw();

	}
	return MENU;
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
	loadimage(&image1, "../原型图/game/pause.png", Width/2, Length);
	putimage(0, 0, &image1);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x < 500 && m.x>370 && m.y < 350 && m.y>230) {//继续游戏
				BeginBatchDraw();
				return GAME;
				m.message = NULL;
			}
			if (m.x < 770 && m.x>660 && m.y < 450 && m.y>340) {//返回菜单
				return MENU;
				m.message = NULL;
			}

			if (m.x < 550 && m.x>370 && m.y < 550 && m.y>440) {//退出游戏
				exit(0);
				m.message = NULL;
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

			if (m.x < 854 && m.x>780 && m.y < 488 && m.y>435) {//返回菜单
				return MENU;
				m.message = NULL;
			}

			if (m.x < 972 && m.x>890 && m.y < 487 && m.y>435) {//下一页
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

			if (m.x < 775 && m.x>695 && m.y < 530 && m.y>481) {//返回菜单
				return MENU;
				m.message = NULL;
			}
			if (m.x < 939 && m.x>852 && m.y < 527 && m.y>480) {//返回上一页
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
	return MENU;
}