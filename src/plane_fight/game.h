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

	void enemyAttack();

	// 碰撞检查
	int checkCrash();

	//发射子弹
	void playerAttack();

	//按键检测
	void checkKeyDown(int &p_x,int &p_y);

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
		RULE1,	// 5. 规则介绍界面，扩展，请自行补充函数
		/*
		* 技术官：
		* 这里是指规则有两页是吧，我觉得这可以在一个界面内完成，通过循环切换规则页
		* 但是即然写都写了，就这样吧（屎山代码的诞生）
		*/
		RULE2,  // 6 
		DEVELOPER, // 7. 开发者介绍界面，扩展，请自行补充函数
	};

	int bestScore;		// 最好成绩
	int fps;			// 游戏帧数
	int score;			// 当前成绩
	int enemyCD;		// 生成新敌机的剩余CD（单位fps)
	int bossCD;         //生成BOSS的剩余CD
	int attackCD;       //玩家发射子弹的cd
	int enemyAttackCD;	//敌人发送子弹的cd
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

	//规则一
	Page showRule1();

	//规则二
	Page showRule2();

	//开发者名单
	Page showDeveloper();
};

#endif
