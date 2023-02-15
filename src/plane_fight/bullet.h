#ifndef __BULLET_H
#define __BULLET_H

#include "base.h"
#include <vector>
using namespace std;
// �ӵ�
class Bullet : public FlyingObject {
public:
	enum Belone { PLAYER, ENEMY };	// ö�����࣬�ӵ�����
	enum Type { BASKERBALL, BULLET1,BULLET2,BOOS ,NONE }; // ö�����࣬�ӵ�����

	Bullet(Point pos, double angle, double speed,Type type);

	Bullet();

	//չʾ�ӵ�
	void showbullet();
	//Bullet(Belone belone, Type type);//���캯��
protected:
	Belone belone;	// �ӵ�����
	Type type;		// �ӵ�����
     IMAGE b_img[2];//�ӵ�ͼƬ

};

// �ӵ�����
class Bullets :public Bullet{
public:

	Bullets();
	// ���һö�ӵ�
     void addBullet(Point pos, double angle, double speed, Bullet::Type type);

	//void addBullet(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type);

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
	//vector<Bullet> s;//�ӵ���������
       Bullet s[200];
};

#endif
