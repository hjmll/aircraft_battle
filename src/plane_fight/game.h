#ifndef __GAME_H
#define __GAME_H

#include "plane.h"
#include "bullet.h"

class Game {
public:
	// 游戏主流程，控制界面跳转
	void run();
	
	// 初始化游戏数据
	void init();

	// 生成新敌人
	void addEnemy();

	// 碰撞检查
	void checkCrash();

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
		// RULE,	// 5. 规则介绍界面，扩展，请自行补充函数
		// DEVELOPER, // 6. 开发者介绍界面，扩展，请自行补充函数
	};

	int bestScore;		// 最好成绩
	int fps;			// 游戏帧数
	int score;			// 当前成绩
	int enemyCD;		// 生成新敌机的剩余CD（单位fps）
	int defualtCD;		// 生成新敌机的默认CD
	Player player;		// 玩家飞机
	Enemys enemys;		// 敌机集合
	Bullets bullets;	// 子弹集合


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
};

#endif
