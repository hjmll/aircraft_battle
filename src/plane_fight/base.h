#ifndef __BASE_H
#define __BASE_H


#include<graphics.h>
#include<iostream>
#include <fstream>
#include <algorithm>
#include<ctime>
#define Width 1024
#define Length 768
#define E_Wideh 100
#define E_Height 60
#define B_Width  20
#define B_Height 20
#define p_speed 8
#define Pi 3.1415926

// ����ṹ��
struct Point {
	int x, y;
};


// ������
class FlyingObject {
public:
	// ���ݵ�ǰ���ꡢ�ٶȡ��Ƕ��ƶ�����һ����
	void move();

	// ��������
	Point getPos();

	// �������ꡢ�Ƕ�
	void setPos(Point point);

	// �вι��캯��
	FlyingObject(Point pos = {0, 0}, double angle = 0, double speed = 0);

protected:
	Point pos;		// ���꣬ȡ���õ�ʵ������
	double angle;	// �Ƕ�
	double speed;	// �ٶȣ���λ�����ص�/fps
	double xita;     //�Ƕ�תΪ���Ⱥ������
};

#endif
