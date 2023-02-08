#include "base.h"

void FlyingObject::move()
{

}

Point FlyingObject::getPos()
{
	return { 0, 0 };
}

// 无参构造函数
FlyingObject::FlyingObject()
{

}

// 有参构造函数
FlyingObject::FlyingObject(Point pos, double angle, double speed) :pos(pos), angle(angle), speed(speed)
{

}
