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
	int hp;					// ����ֵ
	double attackSpeed;		// ���٣�Ĭ��Ϊ100%
	int attackCD;			// ʣ�๥��CD��attackCD = defualtCD/attackSpeed
	int defualtCD;			// Ĭ��CD
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
		moveSpeedUp,	// �ƶ��ٶ�����20%
		attackSpeedUp,	// �������30%
		changeBullet,	// ����״̬
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

private:
	int buffTime[buffCount];		// ��¼��buffʣ��ʱ��
};


// ���˷ɻ���
class Enemy : public Plane {
public:
	enum Type { NOMAL, AAA, BBB, BOSS }; // ö�����࣬�������ͣ���ͨ����Ѫ���ӹ��١�BOSS...
	// ����
	void attack();

private:
	Type type;	// ��������
};

// �л�����
class Enemys {
public:
	// ���һ�ܵл�
	void addEnemy(Point pos, double angle, double speed, Enemy::Type type);

	// ���صл�������
	int getNum();

	// ���ел��ƶ�
	void move();

	// ���ел�����
	void attack();

	// ɾ��ָ����ŵĵл�
	void delEnemy(int idx);

	// ������ел�
	void clear() { num = 0; }

private:
	int num;
	Enemy s[205];
};

#endif
