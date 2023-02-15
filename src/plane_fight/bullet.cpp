#include "bullet.h"
#include<algorithm>

Bullet::Bullet()
{

}

Bullet::Bullet(Point pos,double angle,double speed,Type type):FlyingObject(pos,angle,speed),type(type)
{

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
void Bullets::addBullet(Point pos, double angle, double speed, Bullet::Type type)
{
	switch (type)
	{
	case Bullet::BASKERBALL:
		loadimage(&b_img[0], "../�ɻ�����/playerbullet/basketball1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../�ɻ�����/playerbullet/basketball2.jpg", B_Width, B_Height);
		s[num++] = Bullet(pos, angle, speed, type);
		break;
	case Bullet::BULLET1:
		break;
	case Bullet::BOOS:
		break;
	case Bullet::NONE:
		break;
	default:
		break;
	}

	//s.push_back(bullet); //���ӵ�����������½�����b

}

/*
* �����ˣ�
* ���ܣ������ӵ�����
* ������void
* ����ֵ��int
*/
int Bullets::getNum()
{
	//return (int)s.size();
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
	//vector<Bullet>::iterator b = s.begin();
	//while (b != s.end())
	//{
	//	b->playermove();
	//	b->showbullet();
	//}


	for (int i = 0; i < num; ++i)
	{
		s[i].playermove();
		s[i].showbullet();
	}
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
 //   swap(s[idx], s[num - 1]);//������ĩβ���ӵ���idx������
	//s.pop_back();//ɾ��ĩβ�ӵ�


	for (int i = 0; i < num; i++)
	{
		if (s[i].getPos().x > Width / 2 || s[i].getPos().x<0 || s[i].getPos().y>Length || s[i].getPos().y < 0)
		{

		}
	}
}


/*
* չʾ�ӵ�ͼƬ
*/
void Bullet::showbullet()
{
	switch (type)
	{
	case BASKERBALL:
		loadimage(&b_img[0], "../�ɻ�����/playerbullet/basketball1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../�ɻ�����/playerbullet/basketball2.jpg", B_Width, B_Height);
		putimage(pos.x, pos.y, &b_img[0], SRCAND);
		putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
		break;
	case BULLET1:
		loadimage(&b_img[0], "../�ɻ�����/enemybullet/bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../�ɻ�����/enemybullet/bullet2.jpg", B_Width, B_Height);
		putimage(pos.x, pos.y, &b_img[0], SRCAND);
		putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
		break;
	//case BULLET2:
	//	loadimage(&b_img[0], "../�ɻ�����/enemy/plane_enemy.jpg", B_Width, B_Height);
	//	loadimage(&b_img[1], "../�ɻ�����/enemy/plane_enemy2.jpg", B_Width, B_Height);
	//	putimage(pos.x, pos.y, &b_img[0], SRCAND);
	//	putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
	//	break;
	case BOOS:
		loadimage(&b_img[0], "../�ɻ�����/enemybullet/boss_bullet1.jpg", B_Width, B_Height);
		loadimage(&b_img[1], "../�ɻ�����/enemybullet/boss_bullet2.jpg", B_Width, B_Height);
		putimage(pos.x, pos.y, &b_img[0], SRCAND);
		putimage(pos.x, pos.y, &b_img[1], SRCPAINT);
		break;
	default:
		break;
	}
}