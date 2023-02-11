#include "game.h"
#include "iostream"

Game::Game()
{

}

Game::Game(int fps)
{

}

void Game::run()
{
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
		}
	}
}


/*
* �����ˣ��ֳ���
* ���ܣ���ʼ����Ϸ����
*	����ˡ��ӵ��������㣬buff���㣬Ѫ������Ϊ3��...
* ������void
* ����ֵ��void
*/
void Game::init()
{

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

}

/*
* �����ˣ��ֳ���
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
	while (true) {
		// ��ҡ����ˡ��ӵ��ƶ�
		player.move();
		enemys.move();
		bullets.move();

		// ��ҡ����˹���
		player.attack();
		enemys.attack();

		// �����µл�
		addEnemy();
		
		// ��ײ���
		checkCrash();

		// ��Ⱦҳ�棺��ȡ��ҡ��л����ӵ��������Ϣ������ҳ��

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
	return MENU;
}