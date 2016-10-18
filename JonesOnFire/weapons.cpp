#include "weapons.h"

CWeapon::CWeapon(Texture & texture, Player & hero, Level &lvl, float time, Texture & bangT)
	:w(20)
	, h(10)
	, born(true)
{
	rect = { 0, 0, w , h };
	heroRect = hero.GetRect();
	sprite.setOrigin((float)w / 2.0f, (float)h / 2.0f);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	x = hero.getplayercoordinateX();
	y = hero.getplayercoordinateY();
	dir = (hero.dir == isright ? RIGHT : LEFT);
	speed = 0.8f;
	life = true;
	obj = lvl.GetObjects("solid");

	bang.setOrigin(50.f / 2.0f, 40.f/ 2.0f);
	bang.setTexture(bangT);
}

void CWeapon::Update(float time)
{
	if (born)
	{
		currentFrame += 0.01 * time;
		if (currentFrame > 3) born = false;
		bang.setTextureRect(IntRect(0, 40 * (int)currentFrame, 50, 40));
		if (dir == RIGHT) bang.setPosition(x + heroRect.width + 45, y + 84);
		else if (dir == LEFT)
		{
			bang.setScale(-1,1);
			bang.setPosition(x - 25, y + 84);
		}
	}
	else
	{
		interactionWithMap();
		switch (dir)
		{
		case RIGHT:
			dx = speed;
			dy = 0;
			break;
		case LEFT:
			dx = -speed;
			dy = 0;
			break;
		}

		x += dx * time;
		y += dy * time;
		if (dir == RIGHT) sprite.setPosition(x + heroRect.width + 70, y + 84);
		if (dir == LEFT)
		{
			sprite.setScale(-1, 1);
			sprite.setPosition(x - 25, y + 84);
		}
	}
}

void CWeapon::interactionWithMap()//ф-ция взаимодействия с картой
{
	for (auto i = obj.begin(); i < obj.end(); i++)//проходимся по объектам
	{
		if (GetRect().intersects(i->rect))//проверяем пересечение игрока с объектом
		{
			life = false;
		}
	}
}

sf::FloatRect CWeapon::GetRect()
{
	return sf::FloatRect(x, y, w, h);
}