#ifndef __PLANE_H
#define __PLANE_H

#include "base.h"
#include "bullet.h"

// �ɻ�����
class Plane : FlyingObject {
public:
	// ����
	void attack();

	// �ɻ��ܵ�damage���˺�
	void hurt(int damage);

private:
	int hp;					// ����ֵ
	double attackSpeed;		// ����
	int attackFPS;			// �����´ι���ʣ��fps
	Bullet::Type bulletType;	// ������ӵ�����
};

// ��ҷɻ���
class Player : FlyingObject {

public:
	// ö�����࣬���buff����
	enum Buff {
		moveSpeedUp,	// �ƶ��ٶ�����20%
		attackSpeedUp,	// �������30%
		changeBullet,	// ����״̬
		unbreakable,	// �޵�
		buffCount		// buff��������
	};

	// ���ָ�����͵�buff��ʱ��Ϊtime
	void addBuff(Buff buff, int time);

	// ����ָ������buffʣ��fps
	int getBuff(Buff buff);

private:
	int buffFPS[buffCount];		// ��buffʣ��fps
};


// ���˷ɻ���
class Enemy : Plane {
public:
	enum Type { NOMAL, AAA, BBB, BOSS }; // ö�����࣬�������ͣ���ͨ����Ѫ���ӹ��١�BOSS...

private:
	Type type;	// �������ͣ�������ͬ���ͺ�õ���ͬbuff
};

// �л�����
class Enemys {
public:
	// ���һ�ܵл�
	void addEnemy(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type);

	// ���صл�������
	void getNum();

	// ɾ��ָ����ŵĵл�
	void del(int idx);

	// ������ел�
	void clear() { num = 0; }

private:
	int num;
	Enemy s[205];
};

#endif
