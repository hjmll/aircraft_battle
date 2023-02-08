#ifndef __BASE_H
#define __BASE_H

// 坐标结构体
struct Point {
	double x, y;
};

// 飞行物
class FlyingObject {
public:
	// 根据当前坐标、速度、角度以及帧率移动到下一坐标
	void move();

	// 获取坐标
	Point getPos();

	FlyingObject();
	FlyingObject(Point pos, double angle, double speed);

private:
	Point pos;		// 坐标
	double angle;	// 角度
	double speed;	// 速度
};

#endif
