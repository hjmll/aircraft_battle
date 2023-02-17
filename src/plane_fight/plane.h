#ifndef __PLANE_H
#define __PLANE_H

#include "base.h"
#include "bullet.h"


// 飞机基类
class Plane : public FlyingObject {
public:

	// 返回飞机血量
	int getHp();

	// 飞机受到damage点伤害
	void hurt(int damage);

	// 恢复Num血量
	void setHp(int num);

	Plane(Point pos, double angle, double speed, int hp, int defualtCD, Bullet::Type bulletType, double attackSpeed = 1.0);

protected:
	int hp;						// 生命值
	double attackSpeedBouns;	// 攻速加成，默认为100%
	int attackCD;				// 剩余攻击CD，attackCD = defualtCD/attackSpeed
	int defualtAttackCD;		// 默认攻击CD
	Bullet::Type bulletType;	// 发射的子弹类型
};

// 玩家飞机类
class Player : public Plane {

public:
	/*
	* 枚举子类，玩家buff类型
	* 由于玩家飞机可能获得的buff数量不多，且每种buff只能获取一次
	* 我们定义一个buffTime数组，记录各buff剩余时长（单位：fps）
	* buffTime[0]表示移速buff剩余时长，buffTime[1]表示攻速buff剩余时长，以此类推
	* 下标用数字表示不方便阅读，因此这里定义了枚举类Buff
	* 于是我们可以这样访问buff剩余时长：buffTime[moveSpeedUp]、buffTime[attackSpeedUp]...
	* 最后的buffCount代表buff总数，用于定义数组
	*/
	enum Buff {
		moveSpeedUp,	// 移动速度增加xx%
		attackSpeedUp,	// 攻速提高xx%
		specialBullet,	// 特殊子弹，例如杀死某类敌人后会暂时获得某种特殊子弹
		unbreakable,	// 无敌
		buffCount		// buff类型总数
	};

	// 攻击
	void attack();

	// 添加指定类型的buff，时长为time
	void addBuff(Buff buff, int time);

	// 各buff倒计时自减
	void checkBuff();

	// 清空所有buff
	void clearBuff();

	int getBuffTime(Buff buff);

	void reset();

	Player();

	//玩家飞机类的构造函数
	Player(Point pos, double angle, double speed, int hp, int attackSpeed, int defaultCD, Bullet::Type bulletType);


protected:
	int buffTime[buffCount];	// 记录各buff剩余时间，单位：fps
};


/*
	Type:
		NORMAL_A 近战 100血
		NORMAL_B 远程 60血
		GREEN 回血 60血
		RED 扣血 60血
		BOSS BOSS 400血
	（基于飞机每发子弹20血）
*/

// 敌人飞机类
class Enemy : public Plane 
{
public:
	enum Type { NORMAL_A, NORMAL_B, E_GREEN, E_RED, BOSS}; // 枚举子类，敌人类型：普通、回血、加攻速、BOSS...

	// 展示图像
	void showenemy();

	// 会发射子弹飞机的特殊移动
	void specialmove();

	Enemy(Type type = Enemy::NORMAL_A, int hp = 5, Point pos = {0, 0}, double angle = 0, double speed = 1.0, Bullet::Type bulletType = Bullet::BULLET1, int defualtCD = 1, double attackSpeed = 1.0);

	Type getType();
protected:

	Type type;	// 敌人类型
	IMAGE e_img[2];
};

// 敌机集合
class Enemys :public Enemy 
{
public:

	// 添加一架敌机
	void addEnemy(Point pos, double angle, double speed, Enemy::Type type);

	// 返回敌机总数量
	int getNum();

	// 所有敌机移动
	void move();

	// 删除指定编号的敌机
	void delEnemy(int idx);

	//展示图像
	void showenemy();

	// 返回指定编号敌机的引用
	Enemy& getEnemy(int idx);

	// 清除所有敌机
	void clear() { num = 0; }

	Enemys();

protected:
	int num;
	Enemy s[205];
};

#endif
