#include "plane.h"

// extern Bullets bullets; //Ӧ����game.cpp  init()���������� Bullets bullets �˴�ֱ������

/*
* �����ˣ�
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

void Plane::setHp(int num)
{
	this->hp = num;
}

//�����ֱ�Ϊ������λ�ã��Ƕȣ��ƶ��ٶȣ�����ֵ��Ĭ��CD���ӵ����ͣ������ٶ�(Ĭ��ֵΪ1.0)
Plane::Plane(Point pos, double angle, double speed, int hp, int defualtAttackCD, Bullet::Type bulletType, double attackSpeedBouns ) 
	: FlyingObject(pos, angle, speed),hp(hp),attackSpeedBouns(attackSpeedBouns),defualtAttackCD(defualtAttackCD),bulletType(bulletType) {
	attackCD = (int)(defualtAttackCD / attackSpeedBouns);
}




// ���÷ɻ�״̬
void Player::reset()
{
	hp = 100;
	setPos({ Width / 2 - E_Wideh / 2, Length - E_Height });
	memset(buffTime, 0, sizeof(buffTime));
}


/*
* �����ˣ�
* ���ܣ���ҷɻ�����
*	������ҷɻ�Ѫ�����ڷɻ����꣨getPos()���������������ӵ�
*	ɢ��Ҳ�ڴ˴�ʵ�֣�����5��ɢ�䣬��ͬʱ����5����ͬλ�ò�ͬ������ӵ�
* ������void
* ����ֵ��void
*/
void Player::attack()
{
	//attackCD--;
	//int b_num = 0;
	//Point m_pos = { Player::getPos().x+E_Wideh/2-B_Width,Player::getPos().y - B_Height };
	//if (attackCD==0) { // attackCDΪ0ʱ�ſ��Է����ӵ�
		//if (hp > 5) {
		//	//������ֵ����5ʱ���ڷɻ�����λ������һö�ӵ����Ƕ�Ϊ90��(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����Ĭ���ӵ�
		//	//b_num = 1;
		//	//for (int i = 0; i < b_num; i++)
		//	//{
		//	//	p = new Bullet;
		//	//	p->addbullet(m_pos, 90, Player::speed + 10, Bullet::BASKERBALL);
		//	//}
		//	//attackCD = 10;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		//}
		//else if (hp > 2) {
		//	//������ֵ����2ʱ���ڷɻ�����λ��������ö�ӵ����Ƕ�Ϊ�ֱ�Ϊ45��(��)��90��(��)��135��(��)(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����AAA���ӵ�
		//	//b_num = 3;
		//	//for (int i = 0; i < b_num; i++)
		//	//{
		//	//	p = new Bullet;
		//	//	p->addbullet(m_pos, 90, Player::speed + 10, Bullet::BASKERBALL);
		//	//}
		//	//addBullet(Player::getPos(), 45.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	//addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	//addBullet(Player::getPos(), 135.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	attackCD = 10;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		//}
		//else if (hp < 2) {
		//	//������ֵС��2ʱ���ڷɻ�����λ��������ö�ӵ����Ƕ�Ϊ�ֱ�Ϊ30,60,90,120,150(����������)���ٶ�Ϊ��ҷɻ��ٶ�+10���ӵ�����Ϊ��ң�����BBB���ӵ�
		//	//addBullet(Player::getPos(), 30.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	//addBullet(Player::getPos(), 60.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	//addBullet(Player::getPos(), 90.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	//addBullet(Player::getPos(), 120.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	//addBullet(Player::getPos(), 150.0, Player::speed + 10, Bullet::PLAYER, Bullet::BASKERBALL);
		//	attackCD = 10;//�����ӵ���attackCDĬ������Ϊ50���������ٸ�
		//}
	//}
}

/*
* ���طɻ��ӵ�������
*/
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
	if (buffTime[buff] == 0) {
		buffTime[buff] = time;
		switch (buff) {
		case moveSpeedUp:
			speed = 5; //��ʼ���ü��ٺ���ٶ�Ϊ5������������ٵ���
			break;
		case attackSpeedUp: 
			attackSpeedBouns = 1.2; //��ʼ���ü��ٺ�Ĺ��ټӳ�Ϊԭ����120%���������ٸ�
			break;
		}
	}
	else {
		buffTime[buff] += time;
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

Player::Player(Point pos, double angle, double speed, int hp, int attackSpeed, int defaultAttackCD, Bullet::Type bulletType)
	:Plane(pos, angle, speed, hp, defaultAttackCD, bulletType) {

	// ��ʼ��ʱ����buff��ʱ�䶼����Ϊ0
	memset(buffTime, 0, sizeof(buffTime));
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

int Player::getBuffTime(Buff buff)
{
	return buffTime[buff];
}

// �����ˣ�pnata
Player::Player() :Plane({ Width / 2 - E_Wideh / 2, Length - E_Height }, 0, 0, 100, 50, Bullet::BASKERBALL)
{
	memset(buffTime, 0, sizeof(buffTime));
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
Enemy::Enemy (Type enemyType, int hp, Point pos, double angle, double speed, Bullet::Type bulletType, int defualtCD, double attackSpeed)
	: type(type), Plane(pos,angle,speed,hp,defualtCD,bulletType,attackSpeed)
{
	type = enemyType;
	switch (type) {
	case Enemy::NORMAL_A:
		loadimage(&e_img[0], "../�ɻ�����/enemy/plane_enemy.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../�ɻ�����/enemy/plane_enemy2.jpg", E_Wideh, E_Height);
		break;
	case Enemy::NORMAL_B:
		loadimage(&e_img[0], "../�ɻ�����/enemy/img_plane_enemy10.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../�ɻ�����/enemy/img_plane_enemy11.jpg", E_Wideh, E_Height);
		break;
	case Enemy::E_GREEN:
		loadimage(&e_img[0], "../�ɻ�����/enemy/img_plane_enemy8.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../�ɻ�����/enemy/img_plane_enemy9.jpg", E_Wideh, E_Height);
		break;
	case Enemy::E_RED:
		loadimage(&e_img[0], "../�ɻ�����/enemy/img_plane_enemy1.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../�ɻ�����/enemy/img_plane_enemy2.jpg", E_Wideh, E_Height);
		break;
	case Enemy::BOSS:
		loadimage(&e_img[0], "../�ɻ�����/BOSS/boss1.jpg", E_Wideh, E_Height);
		loadimage(&e_img[1], "../�ɻ�����/BOSS/boss2.jpg", E_Wideh, E_Height);
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
		int hp = 400;
		s[num++] = Enemy(type, hp, pos, angle, speed, Bullet::BOOS);
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
	for (int i = 0; i < num; i++)
	{
		while (i < num)
		{
			Point p = s[i].getPos();
			if (p.y - E_Height < Width) break; // ɾ��������Ļ��Χ�ķɻ�
			delEnemy(i);
		}
	}

	for (int i = 0; i < num; ++i)
	{
		s[i].move();
		s[i].showenemy();
	}
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
	swap(s[idx], s[--num]);
}



/*
* ���ݵл�����չʾ�л�ͼƬ
*/
void Enemy::showenemy()
{
	putimage(pos.x - E_Wideh / 2, pos.y - E_Height / 2, &e_img[0], SRCAND);
	putimage(pos.x - E_Wideh / 2, pos.y - E_Height / 2, &e_img[1], SRCPAINT);
}