#include "bullet.h"

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
void Bullets::addBullet(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type)
{

}

/*
* 负责人：
* 功能：返回子弹数量
* 参数：void
* 返回值：int
*/
int Bullets::getNum()
{

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

}