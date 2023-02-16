#ifndef __PLANE_H
#define __PLANE_H

#include "base.h"
#include "bullet.h"


// �ɻ�����
class Plane : public FlyingObject {
public:

	// ���طɻ�Ѫ��
	int getHp();

	// �ɻ��ܵ�damage���˺�
	void hurt(int damage);

	Plane(Point pos, double angle, double speed, int hp, int defualtCD, Bullet::Type bulletType, double attackSpeed = 1.0);

protected:
	int hp;						// ����ֵ
	double attackSpeedBouns;	// ���ټӳɣ�Ĭ��Ϊ100%
	int attackCD;				// ʣ�๥��CD��attackCD = defualtCD/attackSpeed
	int defualtAttackCD;		// Ĭ�Ϲ���CD
	Bullet::Type bulletType;	// ������ӵ�����
};

// ��ҷɻ���
class Player : public Plane {

public:
	/*
	* ö�����࣬���buff����
	* ������ҷɻ����ܻ�õ�buff�������࣬��ÿ��buffֻ�ܻ�ȡһ��
	* ���Ƕ���һ��buffTime���飬��¼��buffʣ��ʱ������λ��fps��
	* buffTime[0]��ʾ����buffʣ��ʱ����buffTime[1]��ʾ����buffʣ��ʱ�����Դ�����
	* �±������ֱ�ʾ�������Ķ���������ﶨ����ö����Buff
	* �������ǿ�����������buffʣ��ʱ����buffTime[moveSpeedUp]��buffTime[attackSpeedUp]...
	* ����buffCount����buff���������ڶ�������
	*/
	enum Buff {
		moveSpeedUp,	// �ƶ��ٶ�����xx%
		attackSpeedUp,	// �������xx%
		specialBullet,	// �����ӵ�������ɱ��ĳ����˺����ʱ���ĳ�������ӵ�
		unbreakable,	// �޵�
		buffCount		// buff��������
	};

	// ����
	void attack();

	// ���ָ�����͵�buff��ʱ��Ϊtime
	void addBuff(Buff buff, int time);

	// ��buff����ʱ�Լ�
	void checkBuff();

	// �������buff
	void clearBuff();

	int getBuffTime(Buff buff);

	void reset();

	Player();

	//��ҷɻ���Ĺ��캯��
	Player(Point pos, double angle, double speed, int hp, int attackSpeed, int defaultCD, Bullet::Type bulletType);


protected:
	int buffTime[buffCount];	// ��¼��buffʣ��ʱ�䣬��λ��fps
};


/*
	Type:
		NORMAL_A ��ս 100Ѫ
		NORMAL_B Զ�� 60Ѫ
		GREEN ��Ѫ 60Ѫ
		RED ��Ѫ 60Ѫ
		BOSS BOSS 400Ѫ
	�����ڷɻ�ÿ���ӵ�20Ѫ��
*/

// ���˷ɻ���
class Enemy : public Plane 
{
public:
	enum Type { NORMAL_A, NORMAL_B, E_GREEN, E_RED, BOSS}; // ö�����࣬�������ͣ���ͨ����Ѫ���ӹ��١�BOSS...

	//չʾͼ��
	void showenemy();
	//�ᷢ���ӵ��ɻ��������ƶ�
	void specialmove();

	Enemy(Type type = Enemy::NORMAL_A, int hp = 5, Point pos = {0, 0}, double angle = 0, double speed = 1.0, Bullet::Type bulletType = Bullet::BULLET1, int defualtCD = 1, double attackSpeed = 1.0);

	Type getType();
protected:
	Type type;	// ��������
	IMAGE e_img[2];
};

// �л�����
class Enemys :public Enemy 
{
public:

	// ���һ�ܵл�
	void addEnemy(Point pos, double angle, double speed, Enemy::Type type);

	// ���صл�������
	int getNum();

	// ���ел��ƶ�
	void move();

	// ɾ��ָ����ŵĵл�
	void delEnemy(int idx);

	//չʾͼ��
	void showenemy();

	// ����ָ����ŵл�������
	Enemy& getEnemy(int idx);

	// ������ел�
	void clear() { num = 0; }

	Enemys();

protected:
	int num;
	Enemy s[205];
};

#endif
