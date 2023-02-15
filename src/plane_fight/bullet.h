#ifndef __BULLET_H
#define __BULLET_H

#include "base.h"
#include <vector>
using namespace std;
// 子弹
class Bullet : public FlyingObject {
public:
	enum Belone { PLAYER, ENEMY };	// 枚举子类，子弹归属
	enum Type { BASKERBALL, BULLET1,BULLET2,BOOS ,NONE }; // 枚举子类，子弹类型

	Bullet(Point pos, double angle, double speed, Type type, Belone belone);

	Bullet();

	// 展示子弹
	void showbullet();

	// 返回子弹类型
	Type getType();

	// 返回子弹归属
	Belone getBelone();

protected:
	Belone belone;	// 子弹归属
	Type type;		// 子弹类型
    IMAGE b_img[2]; // 子弹图片

};

// 子弹集合
class Bullets :public Bullet{
public:

	Bullets();
	// 添加一枚子弹
	void addBullet(Point pos, double angle, double speed, Bullet::Type type, Bullet::Belone belone);

	 // 返回子弹集总数量
	int getNum();

	// 所有子弹移动
	void move();

	// 返回指定编号的子弹的引用
	Bullet& getBullet(int idx);

	// 删除指定编号的子弹
	void delBullet(int idx);

	// 清除所有子弹
	void clear() { num = 0; }

private:
       int num;
	//vector<Bullet> s;//子弹类型向量
       Bullet s[200];
};

#endif
