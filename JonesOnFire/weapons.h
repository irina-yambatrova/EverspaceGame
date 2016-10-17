#ifndef weap_h
#define weap_h
#include <SFML/Graphics.hpp>
#include "level.h"
#include "InitialData.h"
#include "Player.h"
#include "stdafx.h"

using namespace sf;

class CWeapon {
private:
	float x, y;
public:
	bool life;
	float dx = 0;
	float dy = 0;
	int w, h;
	float speed = 0.2f;
	IntRect rect;
	FloatRect heroRect;
	Direction dir;
	Texture texture;
	Sprite sprite;
	std::vector<Object> obj;
	CWeapon(Texture & texture, Player & hero, Level &lvl, float time)
		:w(20)
		,h(10)
	{
		rect = { 0, 0, w , h };
		heroRect = hero.GetRect();
		sprite.setOrigin((float)w / 2.0f, (float)h / 2.0f);
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		x = hero.getplayercoordinateX();
		y = hero.getplayercoordinateY();
		if (hero.dx >= 0) dir = RIGHT;
		if (hero.dx < 0) dir = LEFT;
		speed = 0.4f;
		life = true;
		obj = lvl.GetObjects("solid");
	}
	void Update(float time);
	void interactionWithMap();
	FloatRect GetRect();
};

#endif
