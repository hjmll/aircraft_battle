#include "game.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <graphics.h>
#include <mmsystem.h>
#include <ctime>


#pragma comment(lib,"winmm.lib")


// �����ˣ�panta
Game::Game(int fps)
{
	this->fps = fps;
	score = 0;
	preTime = clock();
	enemyCD = fps/2;	// ���ÿ�� 2 ��
	defualtCD = fps;	// ÿ 1 �����һ������
	bossCD = 0;
	attackCD = 25;
	enemyAttackCD = 0;
}

void Game::run()
{
	initgraph(Width, Length);
	Page nextPage = Game::MENU; // ������Ϸʱ��Ĭ�Ͻ���˵�ҳ
	/*
	* showXxxx()��������չʾ��Ӧ���棬�䷵��ֵΪ��һ��ҳ���ö��ֵ
	* ���磬������Ϸʱ���Ƚ���MENUҳ�棬��������ҵ����ʼ��Ϸ
	* ��MENUҳ���˳�������ֵΪGAME��������һ��չʾ��ҳ��Ϊ��Ϸҳ��
	* ��������ֵ����ͣ������GAMEҳ���˳�������ֵΪPAUSE����һ��չʾ��ҳ��Ϊ��ͣҳ��
	* �Դ�����...
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
* �����ˣ�
* ���ܣ���ʼ����Ϸ����
*	����ˡ��ӵ��������㣬buff���㣬Ѫ������Ϊ3��...
* ������void
* ����ֵ��void
*/
void Game::init()
{
	enemyCD = 30;		//��һ������30fps������
	bossCD = 50*fps;
	attackCD = 20;
	enemyAttackCD = 30;
	score = 0;
	player.reset();		// ���÷ɻ�״̬
	bullets.clear();	// ����ӵ�
	enemys.clear();		// ��յл�
}

// ��ҷ����ӵ�
void Game::playerAttack()
{
	int b_num = 0;
	double angle = 0;
	if (attackCD <=0)
	{
		mciSendString("play ../�ɻ�����/battlemusic/shoot_1.mp3 from 0", NULL, 0, NULL); // ��ͷ��ʼ��������
		Point p_pos[5];
		if (player.getHp() > 70)
		{
			//������ֵ����5ʱ���ڷɻ�����λ������һö�ӵ����Ƕ�Ϊ90��(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����Ĭ���ӵ�
			b_num = 1;
			for (int i = 0; i < b_num; i++)
			{
				p_pos[i] = player.getPos();
				p_pos[i].x = p_pos[i].x;
				p_pos[i].y = p_pos[i].y;
				bullets.addBullet(p_pos[i], -90, p_speed + 10, Bullet::BASKERBALL, Bullet::PLAYER);
			}
   			attackCD = 15;
		}
		else if (player.getHp() > 40)
		{
			b_num = 3;
			angle = 45;
			p_pos[1] = player.getPos();
			p_pos[2].x = p_pos[1].x - E_Wideh / 2;
			p_pos[2].y = p_pos[1].y;
			p_pos[0].x = p_pos[1].x + E_Wideh / 2;
			p_pos[0].y = p_pos[1].y;
			for (int i = 0; i < b_num; i++)
			{
				bullets.addBullet(p_pos[i], -angle * (i + 1), p_speed + 10, Bullet::BASKERBALL, Bullet::PLAYER);
			}
			attackCD = 25;
		}
		else
		{
			b_num = 5;
			angle = 30;
			p_pos[4].x = player.getPos().x - (E_Wideh / 2 - B_Width / 2);
			p_pos[4].y = player.getPos().y + B_Width * 2;
			p_pos[3].x = player.getPos().x - (E_Wideh / 2 - B_Width / 2) / 2;
			p_pos[3].y = player.getPos().y;
			p_pos[2] = player.getPos();
			p_pos[1].x = p_pos[3].x + (E_Wideh / 2 - B_Width / 2) / 2;
			p_pos[1].y = p_pos[3].y;
			p_pos[0].x = p_pos[4].x + (E_Wideh / 2 - B_Width / 2);
			p_pos[0].y = p_pos[4].y;
			for (int i = 0; i < b_num; i++)
			{
				bullets.addBullet(p_pos[i], -angle * (i + 1), p_speed + 10, Bullet::BASKERBALL, Bullet::PLAYER);
			}
			attackCD = 30;
		}
	}
}


/*
* �����ˣ���ȫ��
* ���ܣ��л�����
*	���ݵл����ͣ��ڵл����꣨getPos()���������������ӵ�
*	ɢ��Ҳ�ڴ˴�ʵ�֣�����5��ɢ�䣬��ͬʱ����5����ͬλ�ò�ͬ������ӵ�
* ������void
* ����ֵ��void
*/
void Game::enemyAttack()
{
	int b_num = 0;
	double angle = 0;
	for (int i = 0; i < enemys.getNum(); ++i) {
		Point p_pos[5];
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
				p_pos[j] = enemys.getEnemy(i).getPos();
				p_pos[j].y = p_pos[j].y + E_Height / 2;
				bullets.addBullet(p_pos[j], 90, p_speed + 10, Bullet::BULLET1, Bullet::ENEMY);
			}
			enemyAttackCD = 30;
			break;
		case Enemys::BOSS:
			int dx = rand() % (2 * E_Wideh);
			b_num = 5;
			angle = 30;
			p_pos[0] = enemys.getEnemy(i).getPos();
			p_pos[0].y = p_pos[0].y + E_Height * 2;


			p_pos[2].x = p_pos[0].x + E_Wideh;
			p_pos[2].y = p_pos[0].y;


			p_pos[3].x = p_pos[2].x - (E_Wideh / 2 - B_Width / 2);
			p_pos[3].y = p_pos[2].y - B_Width;
			p_pos[4].x = p_pos[2].x - (E_Wideh / 2 - B_Width / 2) * 2;
			p_pos[4].y = p_pos[2].y - B_Width * 2;
			p_pos[1].y = p_pos[3].y;
			p_pos[1].x = p_pos[2].x + (E_Wideh / 2 - B_Width / 2);
			p_pos[0].y = p_pos[4].y;
			p_pos[0].x = p_pos[2].x + (E_Wideh / 2 - B_Width / 2) * 2;
			for (int j = 0; j < b_num; j++)
			{
				p_pos[j].x -= dx;
				bullets.addBullet(p_pos[j], angle * (j + 1), p_speed - 3, Bullet::BOOS, Bullet::ENEMY);
			}
			enemyAttackCD = 30;
			break;
		}
	}
}

/*
* �����ˣ��׿���
* ���ܣ����������µл�
*	���enemyCD��Ϊ�㣬��CDֵ-1
*	���enemyCDΪ�㣬��enemyCD = defualtCD�������x�����ɵл�
* ������void
* ����ֵ��void
*/
void Game::addEnemy()
{
	int type = 0;
	srand((unsigned)time(0));
	Point e_pos;
	Enemy t_enemy;
	type = rand() % 4;//�������
	if (bossCD == 1)
	{
		mciSendString("close ../�ɻ�����/battlemusic/zhandou_1.mp3", NULL, 0, NULL);
		mciSendString("play ../�ɻ�����/battlemusic/boss_coming.mp3 repeat", NULL, 0, NULL);
		enemys.clear();
		bullets.clear();
		e_pos.x = rand() % (Width - E_Wideh * 2);
		e_pos.y = -E_Height * 2;
		enemys.addEnemy(e_pos, 90, 4, t_enemy.BOSS);
		bossCD--;
	}
	else
	{
		enemyCD--;
		bossCD--;
		if (enemyCD == 0)
		{
			if (type == 0)//���ɺ�ɫ�л�
			{
				e_pos.x = rand() % (Width - E_Wideh);
				e_pos.y = -E_Height;
				enemys.addEnemy(e_pos, 90, 4, t_enemy.E_RED);
				enemyCD = defualtCD;
			}
			else if (type == 1)//������ɫ�л�
			{
				e_pos.x = rand() % (Width - E_Wideh);
				e_pos.y = -E_Height;
				enemys.addEnemy(e_pos, 90, 4, t_enemy.E_GREEN);
				enemyCD = defualtCD;
			}
			else if (type == 2)//������ͨ�л�
			{
				e_pos.x = rand() % (Width - E_Wideh);
				e_pos.y = -E_Height;
				enemys.addEnemy(e_pos, 90, 4, t_enemy.NORMAL_A);
				enemyCD = defualtCD;
			}
			else if (type == 3)//���ɻ�����ĵл�
			{
				e_pos.x = rand() % (Width - E_Wideh);
				e_pos.y = -E_Height;
				enemys.addEnemy(e_pos, 90, 4, t_enemy.NORMAL_B);
				enemyCD = defualtCD;
				enemyAttackCD = 30;
			}
		}
	}
}

/*
* �����ˣ�
* ���ܣ���ײ��⣬���ĺ���
*	1. ö�������ӵ�
*		1) ���Ϊ�з��ӵ����ж��Ƿ�����ҷɻ���ײ��ͨ�����߾����жϣ�
*		   �����ײ���޵�buffʱ��Ϊ0��ɾ���ӵ�����Ҹ����ӵ������ܵ��˺�
		   ������˺�����ֵС��0����return LOSE
*		   ������˺�����ֵ����0�������޵�buff
*		2) ���Ϊ�ҷ��ӵ���ö�ٵз����зɻ����ֱ��ж��Ƿ���л���ײ
*		   �����л���ײ��ɾ���ӵ����л������ӵ��ܵ��˺�
		   ������˺�����ֵС��0������Ϊ�л������䣬���ݵл����ͻ��buff
		   ���������ĵл�ΪBOSS���ͣ���return WIN
	2. ö�����ел����ж��Ƿ��������ײ��֮����߼�ͬ��

* ������void
* ����ֵ��0. ��Ϸ���� 1. ʤ�� 2. ʧ��
*/
int Game::checkCrash()
{
	int extraDMG = 0;
	// �ӵ���ײ
	for (int i = 0; i < bullets.getNum(); i++) {
		Bullet& b = bullets.getBullet(i);
		if (b.getBelone() == Bullet::Belone::ENEMY) {
			if (player.getBuffTime(Player::unbreakable) > 0) {
				continue; // �޵�ʱ�䣬��������ײ
			}
			if (max(fabs(b.getPos().x - player.getPos().x), fabs(b.getPos().y - player.getPos().y)) < 50) {
				// ��ѩ�ȷ����С��60��Ϊ��ײ
				bullets.delBullet(i); // ɾ���ӵ�
				mciSendString("play ../�ɻ�����/battlemusic/kill1_1.mp3 from 0", NULL, 0, NULL);
				player.hurt(20); // ��Ѫ��Ϊ20��������
				if (player.getHp() <= 0) {
					return 2; // ʧ��
				}
				player.addBuff(Player::unbreakable, 80); // ���120֡�޵�ʱ��
			}
		}
		else {
			for (int j = 0; j < enemys.getNum(); j++) {
				Enemy& e = enemys.getEnemy(j);
				int d = (e.getType() == Enemy::BOSS) ? (E_Wideh+B_Width) : (E_Wideh + B_Width)/2;
				if (max(fabs(b.getPos().x - e.getPos().x), fabs(b.getPos().y - e.getPos().y)) < d && b.getBelone() == Bullet::Belone::PLAYER) {
					bullets.delBullet(i); // ɾ���ӵ�
					if (player.getBuffTime(Player::specialBullet) != 0)
						extraDMG = 20;
					e.hurt(20 + extraDMG);
					//��������л�
					switch (e.getType()) {
					case Enemys::E_GREEN://�ָ�Ѫ��
						if (player.getHp() + 10 <= 100)
							player.setHp(player.getHp() + 10);
						else
							player.setHp(100);
						break;
					case Enemys::E_RED://�۳�Ѫ��
						player.hurt(5);
						if (player.getHp() <= 0) {
							return 2; // ʧ��
						}
						break;
					}

					if (e.getHp() <= 0) {
						mciSendString("play ../�ɻ�����/battlemusic/kill4_1.mp3 from 0", NULL, 0, NULL);	// ��ɱ��Ч
						enemys.delEnemy(j); // �л�������
						score += 10;	// ��Ϸ��������10
						// �˴������ҷɻ�buff
						switch (e.getType()) {
						case Enemys::BOSS:
							return 1;
						case Enemys::NORMAL_A:
							player.addBuff(Player::moveSpeedUp, 180);
							break;
						case Enemys::NORMAL_B:
							//�����˺�
							player.addBuff(Player::specialBullet, 150);
							break;
						case Enemys::E_GREEN:
							player.addBuff(Player::attackSpeedUp, 150);
							break;
						case Enemys::E_RED:
							player.addBuff(Player::unbreakable, 150);
							break;
						}
					}
				}
			}
		}
	}

	// ������ײ
	for (int i = 0; i < enemys.getNum(); i++) {
		Enemy& e = enemys.getEnemy(i);
		if (player.getBuffTime(Player::unbreakable) > 0) {
			continue; // �޵�ʱ�䣬��������ײ
		}
		int d = (e.getType() == Enemy::BOSS) ? (E_Wideh + B_Width) : (E_Wideh + B_Width) / 2;
		if (max(fabs(e.getPos().x - player.getPos().x), fabs(e.getPos().y - player.getPos().y)) < d) {
			// ��ѩ�ȷ����С��80��Ϊ��ײ
			if (e.getType() == Enemy::BOSS) {
				mciSendString("play ../�ɻ�����/battlemusic/kill3_1.mp3 from 0", NULL, 0, NULL);
				player.hurt(100); // ��Ѫ��Ϊ20��������
				e.hurt(20);
			}
			else {
				mciSendString("play ../�ɻ�����/battlemusic/kill3_1.mp3 from 0", NULL, 0, NULL);
				player.hurt(20);
				e.hurt(100);
			}
			if (player.getHp() <= 0) {
				return 2; // ʧ��
			}
			if (e.getHp() <= 0) {
				enemys.delEnemy(i); // �л�������
				score += 10;	// ��Ϸ��������10
				// �˴������ҷɻ�buff
				if (e.getType() == Enemys::BOSS) {
					return 1;
				}
			}
			player.addBuff(Player::unbreakable, 80); // ���120֡�޵�ʱ��
		}
	}
	return 0;
}

/*
	�����ˣ���ȫ��
	���ܣ�������⼰ƫ�����޸�
		1.���� w/W -> y��ƫ�Ƽ�С3
		2.���� s/S -> y��ƫ������3
		3.���� a/A -> x��ƫ�Ƽ�С2
		4.���� d/D -> x��ƫ������2

	������
		int &p_x ԭʼx����
		int &p_y ԭʼy����'
	����ֵ:
		0. ������Ϸ
		1. ��ͣ
*/
int Game::checkKeyDown()
{
	Point p = player.getPos();
	if (GetAsyncKeyState('W')) {
		p.y -= p_speed;
		p.y = max(p.y, E_Height/2);
	}
	if (GetAsyncKeyState('S')) {
		p.y += p_speed;
		p.y = min(p.y, Length - (E_Height / 2));
	}
	if (GetAsyncKeyState('A')) {
		p.x -= p_speed;
		p.x = max(p.x, E_Wideh/2);
	}
	if (GetAsyncKeyState('D')) {
		p.x += p_speed;
		p.x = min(p.x, Width - (E_Wideh / 2));
	}
	player.setPos(p);
	if (GetAsyncKeyState(VK_ESCAPE)) 
	{
		return 1;
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		playerAttack();
	}
	return 0;
}

void Game::loadScore()
{
	ifstream fs("scorelist.db", ios::in | ios::binary);
	if (!fs.is_open()) {
		// �ļ���ʧ��
		return;
	}
	while (!scoreList.empty()) {
		scoreList.pop();
	}
	ScoreData tmp = {};
	while (fs.read((char *) & tmp, sizeof(tmp))) {
		scoreList.push(tmp);
	}
	fs.close();
}

void Game::saveScore()
{
	ofstream fs("scorelist.db", ios::out | ios::binary);
	while (!scoreList.empty()) {
		fs.write((const char *)&scoreList.top(), sizeof(ScoreData));
		scoreList.pop();
	}
	fs.close();
}

/*
* �����ˣ��ؽ�÷
* ���ܣ�չʾ�˵�ҳ
*	- ��ʼ��Ϸ��return GAME
*	- ��Ϸ����return RULE����չ��
*	- ������Ա��return DEVELOPER����չ��
*	- �˳���Ϸ��ֱ�ӵ��� exit(0);
* ������void
* ����ֵ��GAME::Page����һ��ҳ���ö��ֵ
*/
Game::Page Game::showMenu()
{
	init();
	IMAGE image;
	//��ӡ����ͼ
	loadimage(&image, "../ԭ��ͼ/�˵�/menu.png", Width, Length);
	putimage(0, 0, &image);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x < 230 && m.x>70 && m.y < 450 && m.y>310) {//��ʼ��Ϸ
				return GAME;
				m.message = NULL;
			}
			if (m.x < 420 && m.x>300 && m.y < 450 && m.y>310) {//��Ϸ����
				return RULE1;
				m.message = NULL;
			}
			if (m.x < 670 && m.x>550 && m.y < 450 && m.y>310) {//������Ա����
				return DEVELOPER;
				m.message = NULL;
			}
			if (m.x < 920 && m.x>790 && m.y < 450 && m.y>310) {//�˳���Ϸ
				exit(0);
				m.message = NULL;
			}
		}

	}

	return MENU;
}


/*
* �����ˣ���ȫ��
* ���ܣ���ӡ��ǰBUFF
* ������void
* ����ֵ��void
*/

void Game::printCurrentBUFF()
{
	//��ʼ��vector
	vector<pair<Player::Buff, int>> ::iterator it = v.begin();
	for (int i = 0; i < player.buffCount; ++i) {
		int flag = 1;
		for (; it != v.end(); ++it) {
			if ((*it).first == Player::Buff(i)) {
				flag = 0;
				(*it).second = player.getBuffTime(i);
			}
			if ((*it).second != 0) 
				(*it).second--;
		}
		if (player.getBuffTime(i) != 0 && flag == 1)
			v.push_back(pair<Player::Buff, int>(Player::Buff(i), player.getBuffTime(i)));
		it = v.begin();
	}

	//��ʣ��ʱ������
	sort(v.begin(), v.end(), [=](pair<Player::Buff, int> p1, pair<Player::Buff, int> p2)->int {
			return p1.second > p2.second;
		}
	);


	for (int i = 0; it != v.end(); ++it,++i) {
		if ((*it).second != 0) {
			switch ((*it).first) {
			case Player::moveSpeedUp:
				outtextxy(0, 680 - i * 30, _T("��ǰBUFF��"));
				settextcolor(YELLOW);
				outtextxy(160, 680 - i * 30, _T("���ټӿ�"));
				break;
			case Player::attackSpeedUp:
				outtextxy(0, 680 - i * 30, _T("��ǰBUFF��"));
				settextcolor(BLUE);
				outtextxy(160, 680 - i * 30, _T("���ټӿ�"));
				break;
			case Player::specialBullet:
				outtextxy(0, 680 - i * 30, _T("��ǰBUFF��"));
				settextcolor(RED);
				outtextxy(160, 680 - i * 30, _T("�ӵ���������"));
				break;
			case Player::unbreakable:
				outtextxy(0, 680 - i * 30, _T("��ǰBUFF��"));
				settextcolor(BLACK);
				outtextxy(160, 680 - i * 30, _T("�޵�ʱ��"));
				break;
			}
		}
		settextcolor(WHITE);
	}
}


/*
* �����ˣ��׿���
* ���ܣ�չʾ��Ϸҳ�棬��Ϸ��������
*	- �ƶ������������ɵ��ˡ���ײ��⡢ʤ���жϡ������ж�
* ������void
* ����ֵ��GAME::Page����һ��ҳ���ö��ֵ
*/
Game::Page Game::showGame()
{
	// ��������Դ
	mciSendString("open ../�ɻ�����/battlemusic/boss_coming.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/zhandou_1.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/shoot_1.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/kill1_1.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/kill2_1.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/kill3_1.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/kill4_1.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/lose_1.mp3", NULL, 0, NULL);
	mciSendString("open ../�ɻ�����/battlemusic/win_1.mp3", NULL, 0, NULL);

	// �ظ����ű�������
	mciSendString("play ../�ɻ�����/battlemusic/zhandou_1.mp3 repeat", NULL, 0, NULL);

	// initgraph(Width, Length, EX_SHOWCONSOLE); // Debug���򿪿���̨����
	int bk_speed;//����ͼ���Ƶ��ٶ�
	bk_speed = 2;
	int bk_y = -2*Length;
	IMAGE bk;
	IMAGE p_img[2];
	loadimage(&bk, "../�ɻ�����/bk/OUT_2.png",Width,Length*4);
	loadimage(&p_img[0], "../�ɻ�����/player/At1.jpg", E_Wideh, E_Height);
	loadimage(&p_img[1], "../�ɻ�����/player/At2.jpg", E_Wideh, E_Height);

	setbkcolor(BLACK);
	setbkmode(TRANSPARENT);

	while (true) {
		BeginBatchDraw();

		bk_y += bk_speed;
		if (bk_y >= 0)
		{
			bk_y = -2*Length;
		}
		putimage(0, bk_y, &bk);
		attackCD--;
		enemyAttackCD--;
		if (checkKeyDown() == 1) {
			mciSendString("close all", NULL, 0, NULL);
			return PAUSE;
		}

		// circle(player.getPos().x, player.getPos().y, 50); // Debug

		if (player.getBuffTime(Player::unbreakable) > 0) {
			if (player.getBuffTime(Player::unbreakable) % 8 < 4) {
				putimage(player.getPos().x - E_Wideh/2, player.getPos().y - E_Height/2, &p_img[0], SRCAND);
				putimage(player.getPos().x - E_Wideh/2, player.getPos().y - E_Height/2, &p_img[1],SRCPAINT);
			}
		}
		else {
			putimage(player.getPos().x - E_Wideh / 2, player.getPos().y - E_Height / 2, &p_img[0], SRCAND);
			putimage(player.getPos().x - E_Wideh / 2, player.getPos().y - E_Height / 2, &p_img[1], SRCPAINT);
		}

		// ��ӵ���
		if (bossCD > 0)
		{
			addEnemy();
		}

		// �����ƶ�
		enemys.move();

		//���˹���
		if (enemyAttackCD <= 0) {
			enemyAttack();
		}

		// �ӵ��ƶ�
		bullets.move();

		// ��ײ���
		switch (checkCrash()) {
		case 0:
			break;
		case 1:
			mciSendString("close all", NULL, 0, NULL); // �˳�����ǰ�ر�����������Դ
			return WIN;
		case 2:
			mciSendString("close all", NULL, 0, NULL);
			EndBatchDraw();
			return LOSE;
		}

		player.checkBuff(); // ���buff����


		// ��Ⱦҳ�棺��ȡ��ҡ��л����ӵ��������Ϣ������ҳ��
		settextstyle(32, 0, _T("����"));
		outtextxy(788, 0, _T("��ǰ������"));
		char s[5];
		sprintf_s(s, "%d", score);
		outtextxy(950, 0, s);

		outtextxy(0, 720, _T("��ǰ������"));
		char t[5];
		sprintf_s(t, "%d", player.getHp());
		outtextxy(160, 720, t);
		outtextxy(200, 720, _T(" /100"));

		//��ǰBUFF
		printCurrentBUFF();
		
		// ��̬����
		Sleep(max(0, CLOCKS_PER_SEC/fps - (clock() - preTime)));
		preTime = clock();

		//if (bossCD > 0 && bossCD % fps == 0) {
		//	cout << "BOSS comming: " << bossCD / 60 << "s" << endl;
		//}

		EndBatchDraw();

	}
}

/*
* �����ˣ��ؽ�÷
* ���ܣ�չʾ��ͣҳ
*	- ������Ϸ��return GAME
*	- ���¿�ʼ���ȵ���init()��ʼ����Ϸ���ݣ�����return GAME
*	- ��Ϸ����return RULE����չ��
*	- ���ز˵���return MENU
* ������void
* ����ֵ��GAME::Page����һ��ҳ���ö��ֵ
*/
Game::Page Game::showPause()
{
	EndBatchDraw();//��ֹͣ������ͼ
	IMAGE image1;
	//��ӡ��ͣҳ��
	loadimage(&image1, "../ԭ��ͼ/game/��ͣ.png", Width, Length);
	putimage(0, 0, &image1);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.message == WM_LBUTTONDOWN) {
				if (m.x < 500 && m.x>365 && m.y < 335 && m.y>183) {//������Ϸ
					return GAME;
				}
				if (m.x < 765 && m.x>645 && m.y < 467 && m.y>330) {//���ز˵�
					return MENU;
				}

				if (m.x < 500 && m.x>365 && m.y < 615 && m.y>467) {//�˳���Ϸ
					exit(0);
				}
			}
		}
	}
	return MENU;
}

/*
* �����ˣ�
* ���ܣ�չʾ��Ϸʤ��ҳ
*	���ȳ�ʼ����Ϸ���ݣ�����init()
*	��¼��óɼ�
*	- ����һ�֣�return GAME
*	- ���ز˵���return MENU
* ������void
* ����ֵ��GAME::Page����һ��ҳ���ö��ֵ
*/
Game::Page Game::showWin()
{
	score += 400;
	mciSendString("play ../�ɻ�����/battlemusic/win_1.mp3", NULL, 0, NULL);
	EndBatchDraw();
	loadScore();
	if (scoreList.empty() || score > scoreList.top().score) // �����ǰ�ɼ�����߷֣���ӡ��߷ֽ���
	{
		// �������
		scoreList.push({score, "iKun", time(NULL)});
		saveScore();
		IMAGE bestwin;
		loadimage(&bestwin, "../ԭ��ͼ/game/win1.png", 1024, 768);
		putimage(0, 0, &bestwin);
		ExMessage m;
		while (1)
		{
			//��ʾ��ǰ����
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(40, 0, _T("����"));
			char s[5];
			sprintf_s(s, "%d", score);
			outtextxy(175, 205, s);

			m = getmessage(EX_MOUSE);
			if (m.message == WM_LBUTTONDOWN)
			{
				if (m.x < 140 && m.x>30 && m.y < 470 && m.y>400)//������Ϸ
				{
					init();
					return GAME;
				}
				if (m.x < 140 && m.x>30 && m.y < 590 && m.y>520)//���ز˵�
				{
					init();
					return MENU;
				}
				if (m.x < 140 && m.x>30 && m.y < 720 && m.y>640)//�˳���Ϸ
				{
					exit(0);
				}
			}
		}
	}
	else//�����ǰ�ɼ�������߷֣���ӡ��ͨ����
	{
		// �������
		int bestScore = scoreList.top().score;
		scoreList.push({score, "iKun", time(NULL)});
		saveScore();
		IMAGE bestwin;
		loadimage(&bestwin, "../ԭ��ͼ/game/win2.png", 1024, 768);
		putimage(0, 0, &bestwin);
		ExMessage m;
		while (1)
		{
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(45, 0, _T("����"));
			char s[5];
			sprintf_s(s, "%d", score);
			outtextxy(250, 215, s);

			sprintf_s(s, "%d", bestScore);
			outtextxy(330, 142, s);

			m = getmessage(EX_MOUSE);

			if (m.message == WM_LBUTTONDOWN)
			{
				if (m.x < 145 && m.x>35 && m.y < 420 && m.y>350)//������Ϸ
				{
					init();
					return GAME;
				}
				if (m.x < 145 && m.x>35 && m.y < 550 && m.y>480)//���ز˵�
				{
					init();
					return MENU;
				}
				if (m.x < 145 && m.x>35 && m.y < 680 && m.y>610)//�˳���Ϸ
				{
					exit(0);
				}
			}
		}
	}
	return MENU;
}

/*
* �����ˣ��ؽ�÷
* ���ܣ�չʾ��Ϸʧ��ҳ
*	���ȳ�ʼ����Ϸ���ݣ�����init()
*	- ����һ�֣�return GAME
*	- ���ز˵���return MENU
* ������void
* ����ֵ��GAME::Page����һ��ҳ���ö��ֵ
*/
Game::Page Game::showLose()
{
	// ����ʧ������
	mciSendString("play ../�ɻ�����/battlemusic/lose_1.mp3", NULL, 0, NULL);
	//��ӡʧ��ҳ��
	IMAGE image6;
	loadimage(&image6, "../ԭ��ͼ/game/��Ϸʧ��.png", 1024, 768);
	putimage(0, 0, &image6);
	ExMessage m;
	while (1) {
		//չʾ����
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(40, 0, _T("����"));
		char s[5];
		sprintf_s(s, "%d", score);
		outtextxy(157, 230, "��ǰ������");
		outtextxy(347, 232, s);

		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x < 270 && m.x>160 && m.y < 397 && m.y>343) {//������Ϸ
				init();
				return GAME;
			}
			if (m.x < 270 && m.x>160 && m.y < 487 && m.y>433) {//���ز˵�
				init();
				return MENU;
			}

			if (m.x < 270 && m.x>160 && m.y < 577 && m.y>523) {//�˳���Ϸ
				exit(0);
			}
		}

	}
}


/*
* ���ܣ�չʾ����1
* �����л�
*/
Game::Page Game::showRule1()
{
	IMAGE image3;
	//��ӡ�������ҳ��
	loadimage(&image3, "../ԭ��ͼ/�˵�/rule1.png", 1024, 768);
	putimage(0, 0, &image3);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 860 && m.x>785 && m.y < 522 && m.y>453) {//���ز˵�
				return MENU;
				m.message = NULL;
			}

			if (m.x < 988 && m.x>896 && m.y < 522 && m.y>453) {//��һҳ
				return RULE2;
				m.message = NULL;
			}
		}
	}
}

/*
* ���ܣ�չʾ����2
* �����л�
*/
Game::Page Game::showRule2()
{
	IMAGE image4;
	loadimage(&image4, "../ԭ��ͼ/�˵�/rule2.png", 1024, 768);
	putimage(0, 0, &image4);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 775 && m.x>698 && m.y < 580 && m.y>515) {//���ز˵�
				return MENU;
				m.message = NULL;
			}
			if (m.x < 940 && m.x>848 && m.y < 580 && m.y>515) {//������һҳ
				return RULE1;
				m.message = NULL;
			}
		}
	}
}

/*
* ���ܣ�չʾ������Ա����
*/
Game::Page Game::showDeveloper()
{
	char s[] = "�������˵�";
	IMAGE image5;
	loadimage(&image5, "../ԭ��ͼ/�˵�/developers.png", 1024, 768);
	putimage(0, 0, &image5);
	outtextxy(10, 35, s);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 90 && m.x>10 && m.y < 50 && m.y>35) {//���ز˵�
				return MENU;
				m.message = NULL;
			}
			if (m.x < 940 && m.x>848 && m.y < 580 && m.y>515) {//������һҳ
				return RULE1;
				m.message = NULL;
			}
		}
	}
	return MENU;
}