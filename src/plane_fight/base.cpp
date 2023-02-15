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
	 if (angle != 0)
	 {
		 pos.y += sin(angle) * speed;
	 }
	 if (angle != 90) // ������
	 {
		 pos.x += cos(angle) * speed;
	 }
}

void FlyingObject::playermove()
{
	if (angle != 0)
	{
		pos.y -= sin(angle) * speed;
	}
	if (angle != 90)
	{
		pos.x -= cos(angle) * speed;
	}
}

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

void FlyingObject::reset(double angle, double speed)
{
}

// �вι��캯��
FlyingObject::FlyingObject(Point pos, double angle, double speed) :pos(pos), angle(angle), speed(speed)
{

}
