#ifndef __BASE_H
#define __BASE_H


#include <graphics.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <queue>

#define Width 1024
#define Length 768
#define E_Wideh 100
#define E_Height 60
#define B_Width  20
#define B_Height 20
#define p_speed 8
#define Pi 3.1415926

// 坐标结构体
struct Point {
	int x, y;
};


// 飞行物
class FlyingObject {
public:
	// 根据当前坐标、速度、角度移动到下一坐标
	void move();

	// 返回坐标
	Point getPos();

	// 重设坐标、角度
	void setPos(Point point);

	// 有参构造函数
	FlyingObject(Point pos = {0, 0}, double angle = 0, double speed = 0);

protected:
	Point pos;		// 坐标，取整得到实际坐标
	double angle;	// 角度
	double speed;	// 速度，单位：像素点/fps
	double xita;     //角度转为弧度后的数据
};

#endif
