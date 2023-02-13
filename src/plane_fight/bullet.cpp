#include "bullet.h"
#include<algorithm>
using namespace std;
/*
* 负责人：
* 功能：在子弹集合最后一位添加一枚新的子弹，子弹数量+1
* 参数：
*	Point pos: 初始坐标
*	double angle: 初始角度
*	double speed: 初始速度
*	Belone belone: 子弹归属（玩家 or 敌人）
*	Type type：子弹类型
* 返回值：void
*/

void Bullets::addBullet(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type)
{
	Bullet b;//创建子弹对象
	s.push_back(b);//向子弹向量中添加新建对象b
}

/*
* 负责人：
* 功能：返回子弹数量
* 参数：void
* 返回值：int
*/
int Bullets::getNum()
{
	num = s.size();
	return num;
}

/*
* 负责人：
* 功能：所有子弹移动
*	枚举所有子弹，依次调用各子弹的move()函数
* 参数：void
* 返回值：void
*/
void Bullets::move()
{
	vector<Bullet>::iterator b = s.begin();
	while (b != s.end())
	{
		b->move();
	}
}

/*
* 负责人：
* 功能：删除指定编号的子弹
*	将数组末尾的子弹复制到idx处，子弹数-1
* 参数：
*	int idx: 删除的子弹编号，编号从0开始
* 返回值：void
*/
void Bullets::delBullet(int idx)
{
	swap(s[idx], s[num - 1]);//将向量末尾处子弹和idx处交换
	s.pop_back();//删除末尾子弹
}