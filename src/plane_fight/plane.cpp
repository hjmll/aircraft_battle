#include "plane.h"

/*
* 负责人：覃一诚
* 功能：返回飞机血量
* 参数：void
* 返回值：int
*/
int Plane::getHp()
{
	return this->hp;
}

/*
* 负责人：覃一诚
* 功能：飞机受伤，生命值减damage
* 参数：
	int damage：受到的伤害
* 返回值：void
*/
void Plane::hurt(int damage)
{
	this->hp -= damage;
}

//参数分别为：坐标位置，角度，移动速度，生命值，默认CD，子弹类型，攻击速度(默认值为1.0)
Plane::Plane(Point pos, double angle, double speed, int hp, int defualtCD, Bullet::Type bulletType, double attackSpeed ) : FlyingObject(pos, angle, speed){
	hp = hp;
	attackSpeed = attackSpeed;
	defualtCD = defualtCD;
	attackCD = defualtCD / attackSpeed;
	bulletType = bulletType;
}

/*
* 负责人：覃一诚
* 功能：玩家飞机攻击
*	根据玩家飞机血量，在飞机坐标（getPos()函数）附近生成子弹
*	散射也在此处实现，例如5发散射，则同时生成5个不同位置不同方向的子弹
* 参数：void
* 返回值：void
*/
void Player::attack()
{
	
}

/*
* 负责人：
* 功能：玩家飞机添加指定时长的指定buff
*	如果指定buff剩余时长为0，则改为指定时长，同时对应属性增加
*	如移动速度+20%
*	如果指定buff剩余时长不为0，则刷新时长，不改动属性
* 参数：
*	Buff buff：buff类型
*	int time: buff时长（单位：fps）
* 返回值：void
*/
void Player::addBuff(Buff buff, int time)
{

}

/*
* 负责人：
* 功能：buff检查
*	枚举每个buff，如果剩余时长为0，则跳过
*	如果剩余时长不为零，则时长减1
*	如果减完后时长归零，对应属性值减少，如移动速度-20%
* 参数：void
* 返回值：void
*/
void Player::checkBuff()
{
}

/*
* 负责人：
* 功能：清空所有buff，即所有buff时长归零，注意修改回属性值
* 参数：void
* 返回值：void
*/
void Player::clearBuff()
{

}

/*
* 负责人：傅全有
* 功能：在敌机集合最后一位添加一个新的敌机，敌机数量+1
* 参数：
*	Point pos: 初始坐标
*	double angle: 初始角度
*	double speed: 初始速度
*	Enemy::Type type：敌机类型
* 返回值：void
*/
void Enemys::addEnemy(Point pos, double angle, double speed, Enemy::Type type)
{

}

/*
* 负责人：傅全有
* 功能：返回敌机数量
* 参数：void
* 返回值：int
*/
int Enemys::getNum()
{

}


/*
* 负责人：傅全有
* 功能：所有敌机移动
*	枚举所有敌机，依次调用各敌机的move()函数
* 参数：void
* 返回值：void
*/
void Enemys::move()
{

}

/*
* 负责人：傅全有
* 功能：所有敌机攻击
*	枚举所有敌机，依次调用各敌机的attack()函数
* 参数：void
* 返回值：void
*/
void Enemys::attack()
{
	
}

/*
* 负责人：傅全有
* 功能：删除指定编号的敌人
*	将数组末尾的敌人复制到idx处，敌人总数-1
* 参数：
*	int idx: 删除的敌人编号，编号从0开始
* 返回值：void
*/
void Enemys::delEnemy(int idx)
{

}

/*
* 负责人：傅全有
* 功能：敌机攻击
*	根据敌机类型，在敌机坐标（getPos()函数）附近生成子弹
*	散射也在此处实现，例如5发散射，则同时生成5个不同位置不同方向的子弹
* 参数：void
* 返回值：void
*/
void Enemy::attack()
{

}
