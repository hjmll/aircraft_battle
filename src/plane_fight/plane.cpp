#include "plane.h"
bool isUnbreakable = false;
bool isChangeBullet = false;
bool isMoveSpeedUp = false;//����������ûɶ�ã���д��д��...
bool isAttackSpeedUp = false;//����������ûɶ�ã���д��д��...

extern Bullets bullets; //Ӧ����game.cpp  init()���������� Bullets bullets �˴�ֱ������

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
* �����ˣ���һ��
* ���ܣ��ɻ����ˣ�����ֵ��damage
* ������
	int damage���ܵ����˺�
* ����ֵ��void
*/
void Plane::hurt(int damage)
{
	if (isUnbreakable == false) { this->hp -= damage; } //��������޵�״̬���ú���������Ч
}

//�����ֱ�Ϊ������λ�ã��Ƕȣ��ƶ��ٶȣ�����ֵ��Ĭ��CD���ӵ����ͣ������ٶ�(Ĭ��ֵΪ1.0)
Plane::Plane(Point pos, double angle, double speed, int hp, int defualtCD, Bullet::Type bulletType, double attackSpeed ) 
	: FlyingObject(pos, angle, speed),hp(hp),attackSpeed(attackSpeed),defualtCD(defualtCD),bulletType(bulletType){
	attackCD = defualtCD / attackSpeed;
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
	if (isChangeBullet==false&&attackCD==0) { //�����ڻ���״̬��attackCDΪ0ʱ�ſ��Է����ӵ�
		if (hp > 5) {
			//������ֵ����5ʱ���ڷɻ�����λ������һö�ӵ����Ƕ�Ϊ-180��(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����Ĭ���ӵ�
			bullets.addBullet(Player::getPos(), -180.0, Player::speed+10, Bullet::PLAYER, Bullet::Default); 
			attackCD = 50;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		}
		else if (hp > 2) {
			//������ֵ����2ʱ���ڷɻ�����λ��������ö�ӵ����Ƕ�Ϊ�ֱ�Ϊ45��(��)��90��(��)��135��(��)(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����AAA���ӵ�
			bullets.addBullet(Player::getPos(), 45.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			bullets.addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			bullets.addBullet(Player::getPos(), 135.0, Player::speed + 10, Bullet::PLAYER, Bullet::AAA);
			attackCD = 50;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		}
		else if (hp < 2) {
			//������ֵС��2ʱ���ڷɻ�����λ��������ö�ӵ����Ƕ�Ϊ�ֱ�Ϊ30,60,90,120,150(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����BBB���ӵ�
			bullets.addBullet(Player::getPos(), 30.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			bullets.addBullet(Player::getPos(), 60.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			bullets.addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			bullets.addBullet(Player::getPos(), 120.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
			bullets.addBullet(Player::getPos(), 150.0, Player::speed + 10, Bullet::PLAYER, Bullet::BBB);
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
	buffTime[buff] +=time; //�Ҿ���buffʱ��Ӧ�ÿ��Ե���
	switch (buff) {
	case moveSpeedUp: {
		isMoveSpeedUp = true;
		speed = 5; //��ʼ���ü��ٺ���ٶ�Ϊ5������������ٵ���
		break;
	}
	case attackSpeedUp: {
		isAttackSpeedUp = true;
		attackSpeed = 1.2;//��ʼ���ü��ٺ�Ĺ���Ϊԭ����120%���������ٸ�
		break;
	}
	case changeBullet: {
		isChangeBullet = true; //���ڻ���״̬�£�attack�����޷���Ч
		break;
	}
	case unbreakable: {
		isUnbreakable = true; //�����޵�״̬�£�damage�����޷���Ч
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
		if (buffTime[moveSpeedUp == 0]) { isMoveSpeedUp = false; speed = 3;//buffЧ��������ָ���ʼ�ٶȣ�Ĭ�ϳ�ʼ�ٶ�Ϊ3
		}
	}
	if (buffTime[attackSpeedUp] > 0) {
		buffTime[attackSpeedUp]--;
		if (buffTime[attackSpeedUp] == 0) {
			isAttackSpeedUp = false; attackSpeed = 1.0; //buffЧ��������ָ���ʼ���� 
		}
		if (buffTime[changeBullet] > 0) {
			buffTime[changeBullet]--;
			if (buffTime[changeBullet] == 0) { isChangeBullet = false; }
		}
		if (buffTime[unbreakable] > 0) {
			buffTime[unbreakable]--;
			if (buffTime[unbreakable] == 0) { isUnbreakable = false; }
		}
	}
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
	buffTime[changeBullet] = 0;
	buffTime[unbreakable] = 0; //������buff��ʱ�䶼����
	isAttackSpeedUp = false;
	isChangeBullet = false;
	isMoveSpeedUp = false;
	isUnbreakable = false; //������buff״̬����
	attackSpeed = 1.0; //�ٶȻָ�Ĭ��ֵ1.0
	speed = 3; //�ƶ��ٶȻָ���Ĭ��ֵ3
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

}

/*
* �����ˣ���ȫ��
* ���ܣ����صл�����
* ������void
* ����ֵ��int
*/
int Enemys::getNum()
{

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

}
