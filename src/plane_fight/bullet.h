#ifndef __BULLET_H
#define __BULLET_H

#include "base.h"

// 子弹
class Bullet : public FlyingObject {
public:
	enum Belone { PLAYER, ENEMY };	// 枚举子类，子弹归属
	enum Type { Default, AAA, BBB }; // 枚举子类，子弹类型

private:
	Belone belone;	// 子弹归属
	Type type;		// 子弹类型

};

// 子弹集合
class Bullets {
public:
	// 添加一枚子弹
	void addBullet(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type);

	// 返回子弹集总数量
	void getNum();

	// 删除指定编号的子弹
	void del(int idx);

	// 清除所有子弹
	void clear() { num = 0; }

private:
	int num;
	Bullet s[205];
};

#endif
