#include "bullet.h"
#include<algorithm>

Bullet::Bullet()
{

}

Bullet::Bullet(Point pos,double angle,double speed,Type type):FlyingObject(pos,angle,speed),type(type)
{

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
void Bullets::addBullet(Point pos, double angle, double speed, Bullet::Type type)
{
	switch (type)
	{
	case Bullet::BASKERBALL:
		loadimage(&b_img[0], "../飞机资料/playerbullet/basketball1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../飞机资料/playerbullet/basketball2.jpg", B_Width, B_Height);
		s[num++] = Bullet(pos, angle, speed, type);
		break;
	case Bullet::BULLET1:
		break;
	case Bullet::BOOS:
		break;
	case Bullet::NONE:
		break;
	default:
		break;
	}

	//s.push_back(bullet); //向子弹向量中添加新建对象b

}

/*
* 负责人：
* 功能：返回子弹数量
* 参数：void
* 返回值：int
*/
int Bullets::getNum()
{
	//return (int)s.size();
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
	//vector<Bullet>::iterator b = s.begin();
	//while (b != s.end())
	//{
	//	b->playermove();
	//	b->showbullet();
	//}

	for (int i = 0; i < num; i++)
	{
		while (i < num)
		{
			Point p = s[i].getPos();
			if (p.x > -50 && p.x < 810 && p.y > -50 && p.y < 1074) break;
			delBullet(i);
		}
	}

	for (int i = 0; i < num; ++i)
	{
		s[i].playermove();
		s[i].showbullet();
	}
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
	swap(s[idx], s[--num]);//将向量末尾处子弹和idx处交换
}


/*
* 展示子弹图片
*/
void Bullet::showbullet()
{
	switch (type)
	{
	case BASKERBALL:
		loadimage(&b_img[0], "../飞机资料/playerbullet/basketball1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../飞机资料/playerbullet/basketball2.jpg", B_Width, B_Height);
		putimage(pos.x, pos.y, &b_img[0], SRCAND);
		putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
		break;
	case BULLET1:
		loadimage(&b_img[0], "../飞机资料/enemybullet/bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../飞机资料/enemybullet/bullet2.jpg", B_Width, B_Height);
		putimage(pos.x, pos.y, &b_img[0], SRCAND);
		putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
		break;
	//case BULLET2:
	//	loadimage(&b_img[0], "../飞机资料/enemy/plane_enemy.jpg", B_Width, B_Height);
	//	loadimage(&b_img[1], "../飞机资料/enemy/plane_enemy2.jpg", B_Width, B_Height);
	//	putimage(pos.x, pos.y, &b_img[0], SRCAND);
	//	putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
	//	break;
	case BOOS:
		loadimage(&b_img[0], "../飞机资料/enemybullet/boss_bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../飞机资料/enemybullet/boss_bullet2.jpg", B_Width, B_Height);
		putimage(pos.x, pos.y, &b_img[0], SRCAND);
		putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
		break;
	default:
		break;
	}
}