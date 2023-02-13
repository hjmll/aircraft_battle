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
	 pos.x= pos.x + cos(angle) * speed;
	 pos.y= pos.y + sin(angle) * speed;
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

// �޲ι��캯��
FlyingObject::FlyingObject()
{

}

// �вι��캯��
FlyingObject::FlyingObject(Point pos, double angle, double speed) :pos(pos), angle(angle), speed(speed)
{

}
