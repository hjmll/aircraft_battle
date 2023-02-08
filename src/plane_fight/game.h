#ifndef __GAME_H
#define __GAME_H

#include "plane.h"
#include "bullet.h"

class Game {
public:
	// ��Ϸ�����̣����ƽ�����ת
	void run();
	
	Game();
	Game(int fps);

private:
	// ҳ����
	enum Page {
		MENU,	// 0. �˵�����
		GAME,	// 1. ��Ϸ����
		PAUSE,	// 2. ��ͣ����
		WIN,	// 3. ʤ������
		LOSE,	// 4. ʧ�ܽ���
	};
	int bestScore;	// ��óɼ�
	int fps;		// ��Ϸ֡��
	Player player;	// ��ҷɻ�
	Enemys enemys;	// �л�



	// ������չʾ����������ֵΪ�´���Ҫչʾ�Ľ���

	// �˵�����
	Page showMenu();

	// ��Ϸ����
	Page showGame();

	// ��ͣ����
	Page showPause();

	// ʤ������
	Page showWin();

	// ʧ�ܽ���
	Page showLose();

	// �˳���Ϸ
	void exit();
};

#endif
