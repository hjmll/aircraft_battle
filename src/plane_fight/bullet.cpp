#include "bullet.h"
#include<algorithm>

Bullet::Bullet()
{

}

Bullet::Bullet(Point pos, double angle, double speed, Type type, Belone belone):FlyingObject(pos,angle,speed),type(type),belone(belone)
{
	switch (type)
	{
	case Bullet::BASKERBALL:
		loadimage(&b_img[0], "../�ɻ�����/playerbullet/basketball1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../�ɻ�����/playerbullet/basketball2.jpg", B_Width, B_Height);
		break;
	case Bullet::BULLET1:
		loadimage(&b_img[0], "../�ɻ�����/enemybullet/bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../�ɻ�����/enemybullet/bullet2.jpg", B_Width, B_Height);
		break;
	case Bullet::BOOS:
		loadimage(&b_img[0], "../�ɻ�����/playerbullet/boss_bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../�ɻ�����/playerbullet/boss_bullet2.jpg", B_Width, B_Height);
		break;
	case Bullet::NONE:
		break;
	}
}

Bullets::Bullets()
{
	num = 0;
}
/*
* �����ˣ�
* ���ܣ����ӵ��������һλ���һö�µ��ӵ����ӵ�����+1
* ������
*	Point pos: ��ʼ����
*	double angle: ��ʼ�Ƕ�
*	double speed: ��ʼ�ٶ�
*	Belone belone: �ӵ���������� or ���ˣ�
*	Type type���ӵ�����
* ����ֵ��void
*/
void Bullets::addBullet(Point pos, double angle, double speed, Bullet::Type type, Bullet::Belone belone)
{
	s[num++] = Bullet(pos, angle, speed, type, belone);
}

/*
* �����ˣ�
* ���ܣ������ӵ�����
* ������void
* ����ֵ��int
*/
int Bullets::getNum()
{
	return num;
}

/*
* �����ˣ�
* ���ܣ������ӵ��ƶ�
*	ö�������ӵ������ε��ø��ӵ���move()����
* ������void
* ����ֵ��void
*/
void Bullets::move()
{

	for (int i = 0; i < num; i++)
	{
		while (i < num) // ɾ��������Ļ��Χ���ӵ�
		{
			Point p = s[i].getPos();
			if (p.x > -50 && p.x < 810 && p.y > -50 && p.y < 1074) break;
			delBullet(i);
		}
		s[i].move();
		s[i].showbullet();
	}
}

Bullet& Bullets::getBullet(int idx)
{
	return s[idx];
}


/*
* �����ˣ�
* ���ܣ�ɾ��ָ����ŵ��ӵ�
*	������ĩβ���ӵ����Ƶ�idx�����ӵ���-1
* ������
*	int idx: ɾ�����ӵ���ţ���Ŵ�0��ʼ
* ����ֵ��void
*/
void Bullets::delBullet(int idx)
{
	//swap(s[idx], s[--num]);//������ĩβ���ӵ���idx������
	if (idx < 0 || idx > num - 1 || num <= 0)
		return;
	s[idx] = s[num - 1];
	num--;
}


/*
* չʾ�ӵ�ͼƬ
*/
void Bullet::showbullet()
{
	putimage(pos.x, pos.y, &b_img[0], SRCAND);
	putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
}

Bullet::Type Bullet::getType()
{
	return type;
}

Bullet::Belone Bullet::getBelone()
{
	return belone;
}
