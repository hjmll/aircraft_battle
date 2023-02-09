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

protected:
	int hp;					// 生命值
	double attackSpeed;		// 攻速，默认为100%
	int attackCD;			// 剩余攻击CD，attackCD = defualtCD/attackSpeed
	int defualtCD;			// 默认CD
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
		moveSpeedUp,	// 移动速度增加20%
		attackSpeedUp,	// 攻速提高30%
		changeBullet,	// 换弹状态
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

private:
	int buffTime[buffCount];		// 记录各buff剩余时间
};


// 敌人飞机类
class Enemy : public Plane {
public:
	enum Type { NOMAL, AAA, BBB, BOSS }; // 枚举子类，敌人类型：普通、回血、加攻速、BOSS...
	// 攻击
	void attack();

private:
	Type type;	// 敌人类型
};

// 敌机集合
class Enemys {
public:
	// 添加一架敌机
	void addEnemy(Point pos, double angle, double speed, Enemy::Type type);

	// 返回敌机总数量
	int getNum();

	// 所有敌机移动
	void move();

	// 所有敌机攻击
	void attack();

	// 删除指定编号的敌机
	void delEnemy(int idx);

	// 清除所有敌机
	void clear() { num = 0; }

private:
	int num;
	Enemy s[205];
};

#endif
