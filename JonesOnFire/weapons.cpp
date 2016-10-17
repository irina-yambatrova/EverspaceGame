#include "weapons.h"

void CWeapon::Update(float time)
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
	sprite.setPosition(x + heroRect.width / 2, y + 84);
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