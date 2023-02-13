#include "game.h"
#include "iostream"
#include<graphics.h>
#include<ctime>
#define Width 1024
#define Length 768

Game::Game()
{

}

Game::Game(int fps)
{

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
	enemyCD = 30;//��һ����ͨ����30���������

	bossCD = 24000;//boss���ķ��Ӻ����
	R_CD = 500, G_CD = 800;//��ɫ�ɻ�5��һ������ɫ�ɻ�8��һ��
	shoot_CD = 600;//�����ӵ��ķɻ�6��һ��
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
	srand((unsigned)time(0));
	Point e_pos;
	Enemy t_enemy;
	while (true)
	{
		enemyCD--;
		bossCD--;
		R_CD--;
		G_CD--;
		Sleep(10);//ÿʮ����CD��һ��
		if (R_CD<=0)
		{
			e_pos.x = rand() % Width;
			e_pos.y = 0;
			enemys.addEnemy(e_pos, 90, 0.1, t_enemy.E_RED);
			enemyCD = 150;
			R_CD = 500;
			break;
		}
		if (G_CD<=0)
		{
			e_pos.x = rand() % Width;
			e_pos.y = 0;
			enemys.addEnemy(e_pos, 90, 0.1, t_enemy.E_GREEN);
			enemyCD = 150;
			G_CD = 800;
			break;
		}
		if (shoot_CD<=0)
		{
			e_pos.x = rand() % Width;
			e_pos.y = 0;
			enemys.addEnemy(e_pos, 90, 0.15, t_enemy.NOMAL_B);
			shoot_CD = 600;
			break;
		}
		if (enemyCD<=0)
		{
			e_pos.x = rand() % Width;
			e_pos.y = 0;
			enemys.addEnemy(e_pos, 90, 0.15, t_enemy.NOMAL_A);
			enemyCD = 150;
			break;
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
* ����ֵ��void
*/
void Game::checkCrash()
{

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
	cleardevice();
	init();
	IMAGE image;
	//��ӡ����ͼ
	loadimage(&image, "../ԭ��ͼ/�˵�/menu.png", Width, Length);
	putimage(0, 0, &image);
	//solidrectangle(790, 310, 920, 450);
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
			if (m.x < 670 && m.x>530 && m.y < 450 && m.y>310) {//������Ա����
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
* �����ˣ��ؽ�÷
* ���ܣ�չʾ��Ϸҳ�棬��Ϸ��������
*	- �ƶ������������ɵ��ˡ���ײ��⡢ʤ���жϡ������ж�
* ������void
* ����ֵ��GAME::Page����һ��ҳ���ö��ֵ
*/
Game::Page Game::showGame()
{
	closegraph();
	initgraph(Width / 2, Length);
	int bk_y = -Length;
	IMAGE bk;
	loadimage(&bk, "../�ɻ�����/bk/tbk.png",Width/2,Length*2);
	while (true) {
		//BeginBatchDraw();

		bk_y += 3;
		if (bk_y == 0)
		{
			bk_y = -Length;
		}
		putimage(0, bk_y, &bk);

		Sleep(32);

		// ��ҡ����ˡ��ӵ��ƶ�
		//player.move();
		//enemys.move();
		//bullets.move();

		//// ��ҡ����˹���
		//player.attack();
		//enemys.attack();

		//// �����µл�
		//addEnemy();
		//
		//// ��ײ���
		//checkCrash();

		// ��Ⱦҳ�棺��ȡ��ҡ��л����ӵ��������Ϣ������ҳ��
		//EndBatchDraw();

	}
	return MENU;
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
	cleardevice();
	IMAGE image1;
	//��ӡ��ͣҳ��
	loadimage(&image1, "../ԭ��ͼ/game/��ͣ.png", 1024, 768);
	putimage(0, 0, &image1);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x < 500 && m.x>370 && m.y < 350 && m.y>230) {//������Ϸ
				return GAME;
				m.message = NULL;
			}
			if (m.x < 770 && m.x>660 && m.y < 450 && m.y>340) {//���ز˵�
				return MENU;
				m.message = NULL;
			}

			if (m.x < 550 && m.x>370 && m.y < 550 && m.y>440) {//�˳���Ϸ
				exit(0);
				m.message = NULL;
			}
		}

	}
	return MENU;
}

/*
* �����ˣ��ؽ�÷
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
	init();
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
	init();
	cleardevice();
	IMAGE image6;
	//��ӡʧ��ҳ��
	loadimage(&image6, "../ԭ��ͼ/game/��Ϸʧ��.png", 1024, 768);
	putimage(0, 0, &image6);
	//solidrectangle(160, 343, 270, 397);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x < 270 && m.x>160 && m.y < 397 && m.y>343) {//������Ϸ
				return GAME;
				m.message = NULL;
			}
			if (m.x < 270 && m.x>160 && m.y < 487 && m.y>433) {//���ز˵�
				return MENU;
				m.message = NULL;
			}

			if (m.x < 270 && m.x>160 && m.y < 577 && m.y>523) {//�˳���Ϸ
				exit(0);
				m.message = NULL;
			}
		}
		return MENU;
	}
}


/*
* ���ܣ�չʾ����1,2
* �����л�
*/
Game::Page Game::showRule1()
{
	cleardevice();
	IMAGE image3;
	//��ӡ�������ҳ��
	loadimage(&image3, "../ԭ��ͼ/�˵�/rule1.png", 1024, 768);
	putimage(0, 0, &image3);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 854 && m.x>780 && m.y < 488 && m.y>435) {//���ز˵�
				return MENU;
				m.message = NULL;
			}

			if (m.x < 972 && m.x>890 && m.y < 487 && m.y>435) {//��һҳ
				return RULE2;
				m.message = NULL;
			}


		}
	}
}
Game::Page Game::showRule2()
{
	cleardevice();
	IMAGE image4;
	loadimage(&image4, "../ԭ��ͼ/�˵�/rule2.png", 1024, 768);
	putimage(0, 0, &image4);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {

			if (m.x < 775 && m.x>695 && m.y < 530 && m.y>481) {//���ز˵�
				return MENU;
				m.message = NULL;
			}
			if (m.x < 939 && m.x>852 && m.y < 527 && m.y>480) {//������һҳ
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
	return MENU;
}