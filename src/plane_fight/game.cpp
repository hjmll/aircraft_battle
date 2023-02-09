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

}

/*
* 负责人：
* 功能：尝试生成新敌机
*	如果enemyCD不为零，则CD值-1
*	如果enemyCD为零，则enemyCD = defualtCD，在随机x处生成敌机
* 参数：void
* 返回值：void
*/
void Game::addEnemy()
{

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
* 负责人：
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

	return MENU;
}

/*
* 负责人：
* 功能：展示游戏页面，游戏核心流程
*	- 移动、攻击、生成敌人、碰撞检测、胜利判断、死亡判断
* 参数：void
* 返回值：GAME::Page，下一个页面的枚举值
*/
Game::Page Game::showGame()
{
	while (true) {
		// 玩家、敌人、子弹移动
		player.move();
		enemys.move();
		bullets.move();

		// 玩家、敌人攻击
		player.attack();
		enemys.attack();

		// 生成新敌机
		addEnemy();
		
		// 碰撞检测
		checkCrash();

		// 渲染页面：获取玩家、敌机、子弹坐标等信息，绘制页面

	}
	return MENU;
}

/*
* 负责人：
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
* 负责人：
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
	return MENU;
}