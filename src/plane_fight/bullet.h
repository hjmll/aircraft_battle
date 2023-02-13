#ifndef __BULLET_H
#define __BULLET_H

#include "base.h"
#include <vector>
using namespace std;
// �ӵ�
class Bullet : public FlyingObject {
public:
	enum Belone { PLAYER, ENEMY };	// ö�����࣬�ӵ�����
	enum Type { Default, AAA, BBB }; // ö�����࣬�ӵ�����
	//Bullet(Belone belone, Type type);//���캯��
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
	int getNum();

	// �����ӵ��ƶ�
	void move();

	// ɾ��ָ����ŵ��ӵ�
	void delBullet(int idx);

	// ��������ӵ�
	void clear() { num = 0; }

private:
	int num;
	vector<Bullet> s;//�ӵ���������
};

#endif
