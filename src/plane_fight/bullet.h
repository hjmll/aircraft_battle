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

	Bullet(Point pos, double angle, double speed,Type type);

	Bullet();

	//展示子弹
	void showbullet();
	//Bullet(Belone belone, Type type);//构造函数
protected:
	Belone belone;	// 子弹归属
	Type type;		// 子弹类型
     IMAGE b_img[2];//子弹图片

};

// 子弹集合
class Bullets :public Bullet{
public:

	Bullets();
	// 添加一枚子弹
     void addBullet(Point pos, double angle, double speed, Bullet::Type type);

	//void addBullet(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type);

	// 返回子弹集总数量
	int getNum();

	// 所有子弹移动
	void move();

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
