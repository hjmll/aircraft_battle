#include <algorithm>
#include "plane.h"

// extern Bullets bullets; //应当在game.cpp  init()函数中声明 Bullets bullets 此处直接引用

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
* 负责人：panta
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
Plane::Plane(Point pos, double angle, double speed, int hp, int defualtAttackCD, Bullet::Type bulletType, double attackSpeedBouns ) 
	: FlyingObject(pos, angle, speed),hp(hp),attackSpeedBouns(attackSpeedBouns),defualtAttackCD(defualtAttackCD),bulletType(bulletType) {
	attackCD = defualtAttackCD / attackSpeedBouns;
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
	if (attackCD==0) { // attackCD为0时才可以发射子弹
		if (hp > 5) {
			//当生命值大于5时，在飞机坐标位置生成一枚子弹，角度为90度(后期慢慢调)，速度为玩家飞机速度+10，子弹归属为玩家，发射默认子弹
			Bullets::addBullet(Player::getPos(), 90.0, Player::speed+10, Bullet::PLAYER, Bullet::Default); 
			attackCD = 50;//发射子弹后attackCD默认设置为50，不合适再改
		}
		else if (hp > 2) {
			//当生命值大于2时，在飞机坐标位置生成三枚子弹，角度为分别为45°(左)，90°(中)，135°(右)(后期慢慢调)，速度为玩家飞机速度+10，子弹归属为玩家，发射AAA型子弹
			Bullets::addBullet(Player::getPos(), 45.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			Bullets::addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			Bullets::addBullet(Player::getPos(), 135.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			attackCD = 50;//发射子弹后attackCD默认设置为50，不合适再改
		}
		else if (hp < 2) {
			//当生命值小于2时，在飞机坐标位置生成五枚子弹，角度为分别为30,60,90,120,150(后期慢慢调)，速度为玩家飞机速度+10，子弹归属为玩家，发射BBB型子弹
			Bullets::addBullet(Player::getPos(), 30.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 60.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 120.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 150.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			attackCD = 50;//发射子弹后attackCD默认设置为50，不合适再改
		}
	}
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
	buffTime[buff] += time; //我觉得buff时间应该可以叠加
	switch (buff) {
	case moveSpeedUp: {
		speed = 5; //初始设置加速后的速度为5，如果不合适再调整
		break;
	}
	case attackSpeedUp: {
		attackSpeedBouns = 1.2; //初始设置加速后的攻速加成为原来的120%，不合适再改
		break;
	}
	case specialBullet: {
		//处于换弹状态下，attack函数无法生效
		break;
	}
	case unbreakable: {
		//处于无敌状态下，damage函数无法生效
		break;
	}
	}
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
	if (buffTime[moveSpeedUp] > 0)
	{
		buffTime[moveSpeedUp]--;
		if (buffTime[moveSpeedUp == 0]) { 
			speed = 3;//buff效果结束后恢复初始速度，默认初始速度为3
		}
	}
	if (buffTime[attackSpeedUp] > 0) {
		buffTime[attackSpeedUp]--;
		if (buffTime[attackSpeedUp] == 0) {
			attackSpeedBouns = 1.0; //buff效果结束后恢复初始攻速加成 
		}
	}
	if (buffTime[specialBullet] > 0) {
		buffTime[specialBullet]--;
	}
	if (buffTime[unbreakable] > 0) {
		buffTime[unbreakable]--;
	}
}

Player::Player(Point pos, double angle, double speed, int hp, int attackSpeed, int defaultCD, Bullet::Type bulletType):Plane(pos, angle, speed, hp, defualtAttackCD, bulletType) {
	buffTime[moveSpeedUp] = 0;
	buffTime[attackSpeedUp] = 0;
	buffTime[specialBullet] = 0;
	buffTime[unbreakable] = 0; // 初始化时所有buff的时间都设置为0
}

/*
* 负责人：
* 功能：清空所有buff，即所有buff时长归零，注意修改回属性值
* 参数：void
* 返回值：void
*/
void Player::clearBuff() 
{
	buffTime[moveSpeedUp] = 0;
	buffTime[attackSpeedUp] = 0;
	buffTime[specialBullet] = 0;
	buffTime[unbreakable] = 0; //将所有buff的时间都清零
	attackSpeedBouns = 1.0; //速度恢复默认值1.0
	speed = 3; //移动速度恢复到默认值3
}

// 负责人：
Player::Player()
{

}


/*
* 负责人：傅全有
* 功能：Enemy 构造方法
* 参数：
*	int hp : 敌机血量
*	Point pos: 初始坐标
*	double angle: 初始角度
*	double speed: 初始速度
*	Bullet::Type bulletType : 子弹类型
*	int defualtCD : 默认攻击间隔
*	double attackSpeed ：攻速
* 返回值：void
*/
Enemy :: Enemy(Type enemyType, int hp, Point pos, double angle, double speed, Bullet::Type bulletType, int defualtCD, double attackSpeed)
	: type(type), Plane(pos,angle,speed,hp,defualtCD,bulletType,attackSpeed)
{
	type = enemyType;
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
	int hp = 0;
	switch (type) {
	case Enemy::NORMAL_A:
		hp = 100;
		break;
	case Enemy::NORMAL_B:
		hp = 60;
		break;
	case Enemy::E_GREEN:
		hp = 60;
		break;
	case Enemy::E_RED:
		hp = 60;
		break;
	case Enemy::BOSS:
		hp = 400;
		break;
	}
	s[num++] = Enemy(type, hp, pos, angle, speed, Bullet::Default);
}

/*
* 负责人：傅全有
* 功能：返回敌机数量
* 参数：void
* 返回值：int
*/
int Enemys::getNum()
{
	return num;
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
	for (int i = 0; i < num; ++i) 
		s[i].move();
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
	for (int i = 0; i < num; ++i)
		s[i].attack();
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
	if (idx < 0 && idx > num-1)return;
	//如果删除的为末尾的敌人，直接num--
	if (idx == num - 1) {
		num--;
		return;
	}
	s[idx] = s[num - 1];
	num--;
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
	Point pos = { getPos().x,getPos().y + 5 };
	switch (type) {
	case NORMAL_A:
		break;
	case NORMAL_B:
		Bullets::addBullet(pos, angle, speed + 10, Bullet::ENEMY, Bullet::Default);
		break;
	case E_GREEN:
		Bullets::addBullet(pos, angle, speed + 10, Bullet::ENEMY, Bullet::Default);
		break;
	case E_RED:
		Bullets::addBullet(pos, angle, speed + 10, Bullet::ENEMY, Bullet::Default);
		break;
	case BOSS:
		Bullets::addBullet(pos, angle, speed + 5, Bullet::ENEMY, Bullet::Default);
		break;
	}
}


