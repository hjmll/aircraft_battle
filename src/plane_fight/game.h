#ifndef __GAME_H
#define __GAME_H

#include "plane.h"
#include "bullet.h"

class Game {
public:
	// ��Ϸ�����̣����ƽ�����ת
	void run();
	
	// ��ʼ����Ϸ����
	void init();

	// �����µ���
	void addEnemy();

	void enemyAttack();

	// ��ײ���
	int checkCrash();

	//�����ӵ�
	void playerAttack();

	//�������
	void checkKeyDown();

	Game(int fps = 60);

private:
	// ҳ����
	enum Page {
		MENU,	// 0. �˵�����
		GAME,	// 1. ��Ϸ����
		PAUSE,	// 2. ��ͣ����
		WIN,	// 3. ʤ������
		LOSE,	// 4. ʧ�ܽ���
		RULE1,	// 5. ������ܽ��棬��չ�������в��亯��
		RULE2,  // 6 
		DEVELOPER, // 7. �����߽��ܽ��棬��չ�������в��亯��
	};

	int bestScore;		// ��óɼ�
	int fps;			// ��Ϸ֡��
	int score;			// ��ǰ�ɼ�
	int enemyCD;		// �����µл���ʣ��CD����λfps)
	int bossCD;         //����BOSS��ʣ��CD
	int attackCD;       //��ҷ����ӵ���cd
	int enemyAttackCD;	//���˷����ӵ���cd
	int defualtCD;		// �����µл���Ĭ��CD
	Player player;		// ��ҷɻ�
	Enemys enemys;		// �л�����
	Bullets bullets;	// �ӵ�����


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

	//����һ
	Page showRule1();

	//�����
	Page showRule2();

	//����������
	Page showDeveloper();
};

#endif
