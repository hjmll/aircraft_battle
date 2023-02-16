#include "base.h"
#include<cmath>
/*
* 负责人：易骏清
* 功能：物体移动
*	根据物体当前坐标、速度、角度移动到下一坐标
*	具体怎么算，还请发挥数学功底
* 参数：void
* 返回值：void
*/
void FlyingObject::move()
{
	if (angle == 90||angle==-90)
	{
		xita = angle * Pi / 180;
		pos.y += sin(xita) * speed;
	}
	else
	{
		xita = angle * Pi / 180;
		pos.y += sin(xita) * speed;
		pos.x += cos(xita) * speed;

	}
}

//void FlyingObject::playermove()
//{
//	if (angle == 90)
//	{
//		xita = angle * Pi / 180;
//		pos.y -= sin(xita) * speed;
//	}
//	else
//	{
//		xita = angle * Pi / 180;
//		pos.y -= sin(xita) * speed;
//		pos.x -= cos(xita) * speed;
//
//	}
//}

/*
* 负责人：易骏清
* 功能：返回物体当前坐标
* 参数：void
* 返回值：Point结构体封装的坐标
*/
Point FlyingObject::getPos()
{
	return { pos.x, pos.y };
}

void FlyingObject::setPos(Point point)
{
	pos = point;
}

// 有参构造函数
FlyingObject::FlyingObject(Point pos, double angle, double speed) :pos(pos), angle(angle), speed(speed)
{

}
