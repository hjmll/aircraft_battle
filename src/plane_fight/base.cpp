#include "base.h"
#include<cmath>


/*
* 负责人：易骏清
* 功能：物体移动
*	根据物体当前坐标、速度、角度移动到下一坐标
* 参数：void
* 返回值：void
*/
void FlyingObject::move()
{
	if (angle == 90 || angle == -90)
	{
		xita = angle * Pi / 180;
		pos.y += (int)(sin(xita) * speed);
	}
	else if (angle == 0 || angle == 180)
	{
		xita = angle * Pi / 180;
		pos.x += (int) (cos(xita) * 2);
	}
	else
	{
		xita = angle * Pi / 180;
		pos.y += (int)(sin(xita) * speed);
		pos.x += (int) (cos(xita) * speed);

	}
}

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
	xita = 0;
}
