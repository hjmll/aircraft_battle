#include "base.h"

/*
* �����ˣ�
* ���ܣ������ƶ�
*	�������嵱ǰ���ꡢ�ٶȡ��Ƕ��ƶ�����һ����
*	������ô�㣬���뷢����ѧ����
* ������void
* ����ֵ��void
*/
void FlyingObject::move()
{

}

/*
* �����ˣ�
* ���ܣ��������嵱ǰ����
* ������void
* ����ֵ��Point�ṹ���װ������
*/
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
