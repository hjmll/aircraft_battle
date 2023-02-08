#ifndef __GAME_H
#define __GAME_H

#include "plane.h"
#include "bullet.h"

class Game {
public:
	// 游戏主流程，控制界面跳转
	void run();
	
	Game();
	Game(int fps);

private:
	// 页面编号
	enum Page {
		MENU,	// 0. 菜单界面
		GAME,	// 1. 游戏界面
		PAUSE,	// 2. 暂停界面
		WIN,	// 3. 胜利界面
		LOSE,	// 4. 失败界面
	};
	int bestScore;	// 最好成绩
	int fps;		// 游戏帧数
	Player player;	// 玩家飞机
	Enemys enemys;	// 敌机



	// 各界面展示函数，返回值为下次需要展示的界面

	// 菜单界面
	Page showMenu();

	// 游戏界面
	Page showGame();

	// 暂停界面
	Page showPause();

	// 胜利界面
	Page showWin();

	// 失败界面
	Page showLose();

	// 退出游戏
	void exit();
};

#endif
