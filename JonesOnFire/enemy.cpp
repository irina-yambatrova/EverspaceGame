#include "enemy.h"

using namespace std;
using namespace sf;

Enemy::Enemy(Texture & texture, Level & lvl, float x, float y, float w, float h)
	: speed(0.07f)
	, currentFrame(0)
	, state(LEFT)
	, x(x)
	, y(y)
	, w(w)
	, h(h)
{
	rect = sf::FloatRect(0, 0, w, h);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));
	dx = speed;
	obj = lvl.GetAllObjects();
	sprite.setPosition(x, y);
	
	health = 60;
	life = true;
}


void Enemy::setTextureRectByState(float time)
{
	currentFrame += 0.005 * time;
	if (currentFrame > 6) currentFrame = 0;
	switch (state)
	{
	case (LEFT):
		dx = -speed;
		sprite.setTextureRect(IntRect(w * (int)currentFrame, 2 * h, w, h));
		break;
	case (RIGHT):
		dx = speed;
		sprite.setTextureRect(IntRect(w * int(currentFrame), h, w, h));
		break;
	case (DOWN):
		dy = speed * 4;
		break;
	}

}


void Enemy::Update(float time)
{
	if (health <= 0)
	{
		life = false;
	}

	setTextureRectByState(time);

	if (!onGround)
	{
		dy += time * 0.0015f;
	}
	x += dx * time;
	Collision(dx, 0);
	y += dy * time;
	Collision(0, dy);
	sprite.setPosition(x, y);
	dy += 0.0015 * time;
	dx = 0;

	sprite.setPosition(x, y);
}

FloatRect Enemy::GetRect()
{
	return FloatRect(x, y, w, h);
}


void Enemy::Collision(float Dx, float Dy)//�-��� �������������� � ������
{
	for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		if (GetRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			if (obj[i].name == "solid")//���� ��������� �����������
			{
				if (Dy > 0) //���� �� ��� ����,
				{
					y = obj[i].rect.top - h;//�� �������� ���������� ����� ���������.
					dy = 0;
					onGround = true;
				}
				if (Dy < 0)
				{
					y = obj[i].rect.top + obj[i].rect.height;//���������� � ������� �����. dy<0, ������ �� ���� �����
					dy = 0;
				}
				if (Dx > 0)
				{
					x = obj[i].rect.left - w; // ���� ���� ������, �� ���������� � ����� �����(������ 0) ����� ������ ���������
					state = LEFT;
				}
				if (Dx < 0)
				{
					x = obj[i].rect.left + obj[i].rect.width;//���������� ���� �����
					state = RIGHT;
				}
					
			}
			else if (obj[i].name == "bonus")
			{
			}
			else if (obj[i].name == "enemy")
			{

			}
			else { onGround = false; }
		}
}
