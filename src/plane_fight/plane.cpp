#include "plane.h"

/*
* 负责人：
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

void Plane::setHp(int num)
{
	this->hp = num;
}

//参数分别为：坐标位置，角度，移动速度，生命值，默认CD，子弹类型，攻击速度(默认值为1.0)
Plane::Plane(Point pos, double angle, double speed, int hp, int defualtAttackCD, Bullet::Type bulletType, double attackSpeedBouns ) 
	: FlyingObject(pos, angle, speed),hp(hp),attackSpeedBouns(attackSpeedBouns),defualtAttackCD(defualtAttackCD),bulletType(bulletType) {
	attackCD = (int)(defualtAttackCD / attackSpeedBouns);
}




// 重置飞机状态
void Player::reset()
{
	hp = 100;
	setPos({ Width / 2 - E_Wideh / 2, Length - E_Height });
	memset(buffTime, 0, sizeof(buffTime));
}

/*
* 返回飞机子弹的坐标
*/
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
	if (buffTime[buff] == 0) {
		buffTime[buff] = time;
		switch (buff) {
		case moveSpeedUp:
			speed = 50; //初始设置加速后的速度为5，如果不合适再调整
			break;
		case attackSpeedUp: 
			attackSpeedBouns = 1.2; //初始设置加速后的攻速加成为原来的120%，不合适再改
			break;
		}
	}
	else {
		buffTime[buff] += time;
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

Player::Player(Point pos, double angle, double speed, int hp, int attackSpeed, int defaultAttackCD, Bullet::Type bulletType)
	:Plane(pos, angle, speed, hp, defaultAttackCD, bulletType) {

	// 初始化时所有buff的时间都设置为0
	memset(buffTime, 0, sizeof(buffTime));
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

int Player::getBuffTime(int BUFF)
{
	return buffTime[BUFF];
}

// 负责人：pnata
Player::Player() :Plane({ Width / 2 - E_Wideh / 2, Length - E_Height }, 0, 0, 100, 50, Bullet::BASKERBALL)
{
	memset(buffTime, 0, sizeof(buffTime));
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
Enemy::Enemy (Type enemyType, int hp, Point pos, double angle, double speed, Bullet::Type bulletType, int defualtCD, double attackSpeed)
	: type(type), Plane(pos,angle,speed,hp,defualtCD,bulletType,attackSpeed)
{
	type = enemyType;
	switch (type) {
	case Enemy::NORMAL_A:
		loadimage(&e_img[0], "../飞机资料/enemy/plane_enemy.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../飞机资料/enemy/plane_enemy2.jpg", E_Wideh, E_Height);
		break;
	case Enemy::NORMAL_B:
		loadimage(&e_img[0], "../飞机资料/enemy/img_plane_enemy10.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../飞机资料/enemy/img_plane_enemy11.jpg", E_Wideh, E_Height);
		break;
	case Enemy::E_GREEN:
		loadimage(&e_img[0], "../飞机资料/enemy/img_plane_enemy8.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../飞机资料/enemy/img_plane_enemy9.jpg", E_Wideh, E_Height);
		break;
	case Enemy::E_RED:
		loadimage(&e_img[0], "../飞机资料/enemy/img_plane_enemy1.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../飞机资料/enemy/img_plane_enemy2.jpg", E_Wideh, E_Height);
		break;
	case Enemy::BOSS:
		loadimage(&e_img[0], "../飞机资料/BOSS/boss1.jpg", E_Wideh*2, E_Height*2);
		loadimage(&e_img[1], "../飞机资料/BOSS/boss2.jpg", E_Wideh*2, E_Height*2);
		break;
	}
}

Enemy::Type Enemy::getType()
{
	return type;
}

Enemy& Enemys::getEnemy(int idx)
{
	return s[idx];
}

Enemys::Enemys()
{
	num = 0;
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
		s[num++] = Enemy(type, hp, pos, angle, speed, Bullet::NONE);
		break;
	case Enemy::NORMAL_B:
		hp = 60;
		s[num++] = Enemy(type, hp, pos, angle, speed, Bullet::BULLET1);
		break;
	case Enemy::E_GREEN:
		hp = 60;
		s[num++] = Enemy(type, hp, pos, angle, speed, Bullet::NONE);
		break;
	case Enemy::E_RED:
		hp = 60;
		s[num] = Enemy(type, hp, pos, angle, speed, Bullet::NONE);
		num++;
		break;
	case Enemy::BOSS:
		int hp = 1000;
		s[num++] = Enemy(type, hp, pos, angle, speed, Bullet::BOOS);
		break;
	}
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
	for (int i = 0; i < num; i++)
	{
		while (i < num)
		{
			Point p = s[i].getPos();
			if (p.y - E_Height < Width) break; // 删除超过屏幕范围的飞机
			delEnemy(i);
		}
		if (s[i].getType() == BOSS || s[i].getType() == NORMAL_B)
		{
			s[i].specialmove();
			s[i].showenemy();
		}
		else
		{
			s[i].move();
			s[i].showenemy();
		}
	}
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
	swap(s[idx], s[--num]);
}



/*
* 根据敌机类型展示敌机图片
*/
void Enemy::showenemy()
{
	// circle(pos.x, pos.y, 50); // Debug
	if (type == Type::BOSS) {
		putimage(pos.x - E_Wideh, pos.y - E_Height, 2*E_Wideh - 2, 2*E_Height - 2, &e_img[0], 0, 0, SRCAND);
		putimage(pos.x - E_Wideh, pos.y - E_Height, 2*E_Wideh - 2, 2*E_Height - 2, &e_img[1], 0, 0, SRCPAINT);
	}
	else {
		putimage(pos.x - E_Wideh / 2, pos.y - E_Height / 2, E_Wideh - 2, E_Height - 2, &e_img[0], 0, 0, SRCAND);
		putimage(pos.x - E_Wideh / 2, pos.y - E_Height / 2, E_Wideh - 2, E_Height - 2, &e_img[1], 0, 0, SRCPAINT);
	}
}



// 实现BOSS和特殊Enemy的特殊移动
void Enemy::specialmove()
{

	int L_Limit = E_Wideh + rand()%E_Wideh;
	int R_Limit = Width - E_Wideh - rand()%E_Wideh;
	int U_Limit = E_Height + rand()%(2*E_Height);
	int p = 10; // 每一帧以千分之 p 概率切换左右移动方向
	
	if (pos.y > U_Limit) {
		if (angle == 90) {
			angle = (rand() & 1) ? 0 : 180;
		}
		else {
			if (pos.x > R_Limit) {
				angle = 180;
			}
			else if (pos.x < L_Limit) {
				angle = 0;
			}
			else {
				if (rand() % 1000 < p) {
					angle = (angle == 0) ? 180 : 0;
				}
			}
		}
	}
	move();
}