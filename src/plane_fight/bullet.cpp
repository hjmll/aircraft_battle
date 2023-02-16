#include "bullet.h"
#include<algorithm>

Bullet::Bullet()
{

}

Bullet::Bullet(Point pos, double angle, double speed, Type type, Belone belone):FlyingObject(pos,angle,speed),type(type),belone(belone)
{
	switch (type)
	{
	case Bullet::BASKERBALL:
		loadimage(&b_img[0], "../飞机资料/playerbullet/basketball1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../飞机资料/playerbullet/basketball2.jpg", B_Width, B_Height);
		break;
	case Bullet::BULLET1:
		loadimage(&b_img[0], "../飞机资料/enemybullet/bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../飞机资料/enemybullet/bullet2.jpg", B_Width, B_Height);
		break;
	case Bullet::BOOS:
		loadimage(&b_img[0], "../飞机资料/playerbullet/boss_bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../飞机资料/playerbullet/boss_bullet2.jpg", B_Width, B_Height);
		break;
	case Bullet::NONE:
		break;
	}
}

Bullets::Bullets()
{
	num = 0;
}
/*
* 负责人：
* 功能：在子弹集合最后一位添加一枚新的子弹，子弹数量+1
* 参数：
*	Point pos: 初始坐标
*	double angle: 初始角度
*	double speed: 初始速度
*	Belone belone: 子弹归属（玩家 or 敌人）
*	Type type：子弹类型
* 返回值：void
*/
void Bullets::addBullet(Point pos, double angle, double speed, Bullet::Type type, Bullet::Belone belone)
{
	s[num++] = Bullet(pos, angle, speed, type, belone);
}

/*
* 负责人：
* 功能：返回子弹数量
* 参数：void
* 返回值：int
*/
int Bullets::getNum()
{
	return num;
}

/*
* 负责人：
* 功能：所有子弹移动
*	枚举所有子弹，依次调用各子弹的move()函数
* 参数：void
* 返回值：void
*/
void Bullets::move()
{

	for (int i = 0; i < num; i++)
	{
		while (i < num) // 删除超过屏幕范围的子弹
		{
			Point p = s[i].getPos();
			if (p.x + B_Width > 0 && p.x - B_Width < Width
				&& p.y + B_Height > 0 && p.y - B_Height < Length) {
				break;
			}
			delBullet(i);
		}
		s[i].move();
		s[i].showbullet();
	}
}

Bullet& Bullets::getBullet(int idx)
{
	return s[idx];
}


/*
* 负责人：
* 功能：删除指定编号的子弹
*	将数组末尾的子弹复制到idx处，子弹数-1
* 参数：
*	int idx: 删除的子弹编号，编号从0开始
* 返回值：void
*/
void Bullets::delBullet(int idx)
{
	//swap(s[idx], s[--num]);//将向量末尾处子弹和idx处交换
	if (idx < 0 || idx > num - 1 || num <= 0)
		return;
	s[idx] = s[num - 1];
	num--;
}


/*
* 展示子弹图片
*/
void Bullet::showbullet()
{
	putimage(pos.x, pos.y, &b_img[0], SRCAND);
	putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
}

Bullet::Type Bullet::getType()
{
	return type;
}

Bullet::Belone Bullet::getBelone()
{
	return belone;
}
