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
	CWeapon(Texture & texture, Player & hero, Level &lvl, float time, Texture & bangT);
	bool life, born;
	float dx = 0;
	float dy = 0;
	int w, h;
	float speed;
	float currentFrame = 0;
	IntRect rect;
	FloatRect heroRect;
	Direction dir;
	Texture texture;
	Sprite sprite;
	Sprite bang;
	std::vector<Object> obj;
	
	void Update(float time);
	void interactionWithMap();
	FloatRect GetRect();
};

#endif
