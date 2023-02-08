#ifndef __BULLET_H
#define __BULLET_H

#include "base.h"

// �ӵ�
class Bullet : public FlyingObject {
public:
	enum Belone { PLAYER, ENEMY };	// ö�����࣬�ӵ�����
	enum Type { Default, AAA, BBB }; // ö�����࣬�ӵ�����

private:
	Belone belone;	// �ӵ�����
	Type type;		// �ӵ�����

};

// �ӵ�����
class Bullets {
public:
	// ���һö�ӵ�
	void addBullet(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type);

	// �����ӵ���������
	void getNum();

	// ɾ��ָ����ŵ��ӵ�
	void del(int idx);

	// ��������ӵ�
	void clear() { num = 0; }

private:
	int num;
	Bullet s[205];
};

#endif
