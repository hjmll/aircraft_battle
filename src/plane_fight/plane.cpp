#include "plane.h"

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
			speed = 50; //��ʼ���ü��ٺ���ٶ�Ϊ5������������ٵ���
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

int Player::getBuffTime(int BUFF)
{
	return buffTime[BUFF];
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
		loadimage(&e_img[0], "../�ɻ�����/BOSS/boss1.jpg", E_Wideh*2, E_Height*2);
		loadimage(&e_img[1], "../�ɻ�����/BOSS/boss2.jpg", E_Wideh*2, E_Height*2);
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
		int hp = 1000;
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



// ʵ��BOSS������Enemy�������ƶ�
void Enemy::specialmove()
{

	int L_Limit = E_Wideh + rand()%E_Wideh;
	int R_Limit = Width - E_Wideh - rand()%E_Wideh;
	int U_Limit = E_Height + rand()%(2*E_Height);
	int p = 10; // ÿһ֡��ǧ��֮ p �����л������ƶ�����
	
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