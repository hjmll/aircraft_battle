#include "base.h"

void FlyingObject::move()
{

}

Point FlyingObject::getPos()
{
	return { 0, 0 };
}

// �޲ι��캯��
FlyingObject::FlyingObject()
{

}

// �вι��캯��
FlyingObject::FlyingObject(Point pos, double angle, double speed) :pos(pos), angle(angle), speed(speed)
{

}
