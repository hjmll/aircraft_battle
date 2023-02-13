#include "plane.h"
extern Bullets bullets;

/*
* �����ˣ���һ��
* ���ܣ����طɻ�Ѫ��
* ������void
* ����ֵ��int
*/
int Plane::getHp()
{
	return 0;
}

/*
* �����ˣ���һ��
* ���ܣ��ɻ����ˣ�����ֵ��damage
* ������
	int damage���ܵ����˺�
* ����ֵ��void
*/
void Plane::hurt(int damage)
{

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
}

/*
* �����ˣ�
* ���ܣ��������buff��������buffʱ�����㣬ע���޸Ļ�����ֵ
* ������void
* ����ֵ��void
*/
void Player::clearBuff()
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
Enemy :: Enemy(int hp, Point pos, double angle, double speed, Bullet::Type bulletType, int defualtCD, double attackSpeed)
	: Plane :: Plane(pos,angle,speed,hp,defualtCD,bulletType,attackSpeed)
{

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
	switch (type) {
	case Enemy::NORMAL_A:
		Enemy e(100, pos, angle, speed, Bullet::Default);
		s[num++] = e;
		break;
	case Enemy::NORMAL_B:
		Enemy e(60, pos, angle, speed, Bullet::Default);
		s[num++] = e;
		break;
	case Enemy::E_GREEN:
		Enemy e(60, pos, angle, speed, Bullet::Default);
		s[num++] = e;
		break;
	case Enemy::E_RED:
		Enemy e(60, pos, angle, speed, Bullet::Default);
		s[num++] = e;
		break;
	case Enemy::BOSS:
		Enemy e(400, pos, angle, speed, Bullet::Default);
		s[num++] = e;
		break;
	}
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
		bullets.addBullet(pos, angle, speed + 10, Bullet::ENEMY, Bullet::Default);
		break;
	case E_GREEN:
		bullets.addBullet(pos, angle, speed + 10, Bullet::ENEMY, Bullet::Default);
		break;
	case E_RED:
		bullets.addBullet(pos, angle, speed + 10, Bullet::ENEMY, Bullet::Default);
		break;
	case BOSS:
		bullets.addBullet(pos, angle, speed + 5, Bullet::ENEMY, Bullet::Default);
		break;
	}
}
