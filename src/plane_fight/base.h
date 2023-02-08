#ifndef __BASE_H
#define __BASE_H

// ����ṹ��
struct Point {
	double x, y;
};

// ������
class FlyingObject {
public:
	// ���ݵ�ǰ���ꡢ�ٶȡ��Ƕ��Լ�֡���ƶ�����һ����
	void move();

	// ��ȡ����
	Point getPos();

	FlyingObject();
	FlyingObject(Point pos, double angle, double speed);

private:
	Point pos;		// ����
	double angle;	// �Ƕ�
	double speed;	// �ٶ�
};

#endif
