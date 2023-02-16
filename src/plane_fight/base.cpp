#include "base.h"
#include<cmath>
/*
* �����ˣ��׿���
* ���ܣ������ƶ�
*	�������嵱ǰ���ꡢ�ٶȡ��Ƕ��ƶ�����һ����
*	������ô�㣬���뷢����ѧ����
* ������void
* ����ֵ��void
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
		pos.x += cos(xita) * 2;
	}
	else
	{
		xita = angle * Pi / 180;
		pos.y += (int)(sin(xita) * speed);
		pos.x += (int) (cos(xita) * speed);

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
* �����ˣ��׿���
* ���ܣ��������嵱ǰ����
* ������void
* ����ֵ��Point�ṹ���װ������
*/
Point FlyingObject::getPos()
{
	return { pos.x, pos.y };
}

void FlyingObject::setPos(Point point)
{
	pos = point;
}

// �вι��캯��
FlyingObject::FlyingObject(Point pos, double angle, double speed) :pos(pos), angle(angle), speed(speed)
{

}
