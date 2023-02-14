#include <algorithm>
#include "plane.h"

// extern Bullets bullets; //Ӧ����game.cpp  init()���������� Bullets bullets �˴�ֱ������

/*
* �����ˣ���һ��
* ���ܣ����طɻ�Ѫ��
* ������void
* ����ֵ��int
*/
int Plane::getHp()
{
	return this->hp;
}

/*
* �����ˣ�panta
* ���ܣ��ɻ����ˣ�����ֵ��damage
* ������
	int damage���ܵ����˺�
* ����ֵ��void
*/
void Plane::hurt(int damage)
{
	this->hp -= damage;
}

//�����ֱ�Ϊ������λ�ã��Ƕȣ��ƶ��ٶȣ�����ֵ��Ĭ��CD���ӵ����ͣ������ٶ�(Ĭ��ֵΪ1.0)
Plane::Plane(Point pos, double angle, double speed, int hp, int defualtAttackCD, Bullet::Type bulletType, double attackSpeedBouns ) 
	: FlyingObject(pos, angle, speed),hp(hp),attackSpeedBouns(attackSpeedBouns),defualtAttackCD(defualtAttackCD),bulletType(bulletType) {
	attackCD = defualtAttackCD / attackSpeedBouns;
}

/*
* �����ˣ���һ��
* ���ܣ���ҷɻ�����
*	������ҷɻ�Ѫ�����ڷɻ����꣨getPos()���������������ӵ�
*	ɢ��Ҳ�ڴ˴�ʵ�֣�����5��ɢ�䣬��ͬʱ����5����ͬλ�ò�ͬ������ӵ�
* ������void
* ����ֵ��void
*/
void Player::attack()
{
	if (attackCD==0) { // attackCDΪ0ʱ�ſ��Է����ӵ�
		if (hp > 5) {
			//������ֵ����5ʱ���ڷɻ�����λ������һö�ӵ����Ƕ�Ϊ90��(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����Ĭ���ӵ�
			Bullets::addBullet(Player::getPos(), 90.0, Player::speed+10, Bullet::PLAYER, Bullet::Default); 
			attackCD = 50;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		}
		else if (hp > 2) {
			//������ֵ����2ʱ���ڷɻ�����λ��������ö�ӵ����Ƕ�Ϊ�ֱ�Ϊ45��(��)��90��(��)��135��(��)(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����AAA���ӵ�
			Bullets::addBullet(Player::getPos(), 45.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			Bullets::addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			Bullets::addBullet(Player::getPos(), 135.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			attackCD = 50;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		}
		else if (hp < 2) {
			//������ֵС��2ʱ���ڷɻ�����λ��������ö�ӵ����Ƕ�Ϊ�ֱ�Ϊ30,60,90,120,150(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����BBB���ӵ�
			Bullets::addBullet(Player::getPos(), 30.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 60.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 120.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			Bullets::addBullet(Player::getPos(), 150.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			attackCD = 50;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		}
	}
}

/*
* �����ˣ�
* ���ܣ���ҷɻ����ָ��ʱ����ָ��buff
*	���ָ��buffʣ��ʱ��Ϊ0�����Ϊָ��ʱ����ͬʱ��Ӧ��������
*	���ƶ��ٶ�+20%
*	���ָ��buffʣ��ʱ����Ϊ0����ˢ��ʱ�������Ķ�����
* ������
*	Buff buff��buff����
*	int time: buffʱ������λ��fps��
* ����ֵ��void
*/
void Player::addBuff(Buff buff, int time)
{
	buffTime[buff] += time; //�Ҿ���buffʱ��Ӧ�ÿ��Ե���
	switch (buff) {
	case moveSpeedUp: {
		speed = 5; //��ʼ���ü��ٺ���ٶ�Ϊ5������������ٵ���
		break;
	}
	case attackSpeedUp: {
		attackSpeedBouns = 1.2; //��ʼ���ü��ٺ�Ĺ��ټӳ�Ϊԭ����120%���������ٸ�
		break;
	}
	case specialBullet: {
		//���ڻ���״̬�£�attack�����޷���Ч
		break;
	}
	case unbreakable: {
		//�����޵�״̬�£�damage�����޷���Ч
		break;
	}
	}
}

/*
* �����ˣ�
* ���ܣ�buff���
*	ö��ÿ��buff�����ʣ��ʱ��Ϊ0��������
*	���ʣ��ʱ����Ϊ�㣬��ʱ����1
*	��������ʱ�����㣬��Ӧ����ֵ���٣����ƶ��ٶ�-20%
* ������void
* ����ֵ��void
*/
void Player::checkBuff()
{
	if (buffTime[moveSpeedUp] > 0)
	{
		buffTime[moveSpeedUp]--;
		if (buffTime[moveSpeedUp == 0]) { 
			speed = 3;//buffЧ��������ָ���ʼ�ٶȣ�Ĭ�ϳ�ʼ�ٶ�Ϊ3
		}
	}
	if (buffTime[attackSpeedUp] > 0) {
		buffTime[attackSpeedUp]--;
		if (buffTime[attackSpeedUp] == 0) {
			attackSpeedBouns = 1.0; //buffЧ��������ָ���ʼ���ټӳ� 
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
	buffTime[unbreakable] = 0; // ��ʼ��ʱ����buff��ʱ�䶼����Ϊ0
}

/*
* �����ˣ�
* ���ܣ��������buff��������buffʱ�����㣬ע���޸Ļ�����ֵ
* ������void
* ����ֵ��void
*/
void Player::clearBuff() 
{
	buffTime[moveSpeedUp] = 0;
	buffTime[attackSpeedUp] = 0;
	buffTime[specialBullet] = 0;
	buffTime[unbreakable] = 0; //������buff��ʱ�䶼����
	attackSpeedBouns = 1.0; //�ٶȻָ�Ĭ��ֵ1.0
	speed = 3; //�ƶ��ٶȻָ���Ĭ��ֵ3
}

// �����ˣ�
Player::Player()
{

}


/*
* �����ˣ���ȫ��
* ���ܣ�Enemy ���췽��
* ������
*	int hp : �л�Ѫ��
*	Point pos: ��ʼ����
*	double angle: ��ʼ�Ƕ�
*	double speed: ��ʼ�ٶ�
*	Bullet::Type bulletType : �ӵ�����
*	int defualtCD : Ĭ�Ϲ������
*	double attackSpeed ������
* ����ֵ��void
*/
Enemy :: Enemy(Type enemyType, int hp, Point pos, double angle, double speed, Bullet::Type bulletType, int defualtCD, double attackSpeed)
	: type(type), Plane(pos,angle,speed,hp,defualtCD,bulletType,attackSpeed)
{
	type = enemyType;
}

/*
* �����ˣ���ȫ��
* ���ܣ��ڵл��������һλ���һ���µĵл����л�����+1
* ������
*	Point pos: ��ʼ����
*	double angle: ��ʼ�Ƕ�
*	double speed: ��ʼ�ٶ�
*	Enemy::Type type���л�����
* ����ֵ��void
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
* �����ˣ���ȫ��
* ���ܣ����صл�����
* ������void
* ����ֵ��int
*/
int Enemys::getNum()
{
	return num;
}


/*
* �����ˣ���ȫ��
* ���ܣ����ел��ƶ�
*	ö�����ел������ε��ø��л���move()����
* ������void
* ����ֵ��void
*/
void Enemys::move()
{
	for (int i = 0; i < num; ++i) 
		s[i].move();
}

/*
* �����ˣ���ȫ��
* ���ܣ����ел�����
*	ö�����ел������ε��ø��л���attack()����
* ������void
* ����ֵ��void
*/
void Enemys::attack()
{
	for (int i = 0; i < num; ++i)
		s[i].attack();
}

/*
* �����ˣ���ȫ��
* ���ܣ�ɾ��ָ����ŵĵ���
*	������ĩβ�ĵ��˸��Ƶ�idx������������-1
* ������
*	int idx: ɾ���ĵ��˱�ţ���Ŵ�0��ʼ
* ����ֵ��void
*/
void Enemys::delEnemy(int idx)
{
	if (idx < 0 && idx > num-1)return;
	//���ɾ����Ϊĩβ�ĵ��ˣ�ֱ��num--
	if (idx == num - 1) {
		num--;
		return;
	}
	s[idx] = s[num - 1];
	num--;
}


/*
* �����ˣ���ȫ��
* ���ܣ��л�����
*	���ݵл����ͣ��ڵл����꣨getPos()���������������ӵ�
*	ɢ��Ҳ�ڴ˴�ʵ�֣�����5��ɢ�䣬��ͬʱ����5����ͬλ�ò�ͬ������ӵ�
* ������void
* ����ֵ��void
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


