#include "bullet.h"
#include<algorithm>
using namespace std;

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
void Bullets::addBullet(Point pos, double angle, double speed, Bullet::Belone belone, Bullet::Type type)
{
	//s.push_back(Bullet()); //���ӵ�����������½�����b
}

/*
* �����ˣ�
* ���ܣ������ӵ�����
* ������void
* ����ֵ��int
*/
int Bullets::getNum()
{
	return (int)s.size();
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
	vector<Bullet>::iterator b = s.begin();
	while (b != s.end())
	{
		b->move();
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
	swap(s[idx], s[num - 1]);//������ĩβ���ӵ���idx������
	s.pop_back();//ɾ��ĩβ�ӵ�
}