#ifndef __BASE_H
#define __BASE_H

// ����ṹ��
struct Point {
	double x, y;
};


// ������
class FlyingObject {
public:
	// ���ݵ�ǰ���ꡢ�ٶȡ��Ƕ��ƶ�����һ����
	void move();

	// ��������
	Point getPos();

	void reset(double angle, double speed);

	FlyingObject() {}

	// �вι��캯��
	FlyingObject(Point pos, double angle, double speed);

protected:
	Point pos;		// ���꣬ȡ���õ�ʵ������
	double angle;	// �Ƕ�
	double speed;	// �ٶȣ���λ�����ص�/fps
};

#endif
