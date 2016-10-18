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
		dy = speed * 5;
		break;
	}

}


void Enemy::Update(float time)
{
	if (life)
	{
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
	}
	else
	{
		if (currentFrame < 5)
		{
			currentFrame += 0.01 * time;
			sprite.setTextureRect(IntRect(152 * (int)currentFrame, h * 3 , 152, 150));
		}
		else
		{
			sprite.setTextureRect(IntRect(152 * 4, h * 3, 152, 150));
		}
		sprite.setPosition(x, y);
	}
	if (hurt)
	{
		if (hurt_time < 3)
		{
			hurt_time += time * 0.0015;
		}
		else
		{
			hurt = false;
			hurt_time = 0;
		}
	}
}

FloatRect Enemy::GetRect()
{
	return FloatRect(x, y, w, h);
}


void Enemy::Collision(float Dx, float Dy)//ф-ция взаимодействия с картой
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if ((obj[i].name == "solid") || (obj[i].name == "solid1"))//если встретили препятствие
			{
				if (Dy > 0) //если мы шли вниз,
				{
					y = obj[i].rect.top - h;//то стопорим координату игрек персонажа.
					dy = 0;
					onGround = true;
				}
				if (Dy < 0)
				{
					y = obj[i].rect.top + obj[i].rect.height;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх
					dy = 0;
				}
				if (Dx > 0)
				{
					x = obj[i].rect.left - w; // если идем вправо, то координата Х равна стена(символ 0) минус ширина персонажа
					state = LEFT;
				}
				if (Dx < 0)
				{
					x = obj[i].rect.left + obj[i].rect.width;//аналогично идем влево
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
