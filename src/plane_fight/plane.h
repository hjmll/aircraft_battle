#ifndef __PLANE_H
#define __PLANE_H

#include "base.h"
#include "bullet.h"

// 飞机基类
class Plane : FlyingObject {
public:
	// 攻击
	void attack();

	// 飞机受到damage点伤害
	void hurt(int damage);

private:
	int hp;					// 生命值
	double attackSpeed;		// 攻速
	int attackFPS;			// 距离下次攻击剩余fps
	Bullet::Type bulletType;	// 发射的子弹类型
};

// 玩家飞机类
class Player : FlyingObject {

public:
	// 枚举子类，玩家buff类型
	enum Buff {
		moveSpeedUp,	// 移动速度增加20%
		attackSpeedUp,	// 攻速提高30%
		changeBullet,	// 换弹状态
		unbreakable,	// 无敌
		buffCount		// buff类型总数
	};

	// 添加指定类型的buff，时长为time
	void addBuff(Buff buff, int time);

	// 返回指定类型buff剩余fps
	int getBuff(Buff buff);

private:
	int buffFPS[buffCount];		// 各buff剩余fps
};


// 敌人飞机类
class Enemy : Plane {
public:
	enum Type { NOMAL, AAA, BBB, BOSS }; // 枚举子类，敌人类型：普通、回血、加攻速、BOSS...

private:
	Type type;	// 敌人类型，攻击不同类型后得到不同buff
};

// 敌机集合
class Enemys {
public:
	// 添加一架敌机
	void addEnemy(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type);

	// 返回敌机总数量
	void getNum();

	// 删除指定编号的敌机
	void del(int idx);

	// 清除所有敌机
	void clear() { num = 0; }

private:
	int num;
	Enemy s[205];
};

#endif
