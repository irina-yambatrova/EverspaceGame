#pragma once
#include "stdafx.h"
#include "level.h"
#include "InitialData.h"

class Enemy
{
public:
	Enemy(sf::Texture & texture, Level & lvl, float x, float y, float w, float h);

	float dx, dy, speed;
	int score;
	bool onGround;
	bool hurt = false;
	void Update(float time);
	float getplayercoordinateX() { return x; }
	float getplayercoordinateY() { return y; }
	sf::Sprite sprite;
	enum { UP, LEFT, RIGHT, DOWN } state;
	FloatRect GetRect();
	std::vector<Object> obj;
	int health;
	bool life;
	float currentFrame;
private:
	float hurt_time = 0;
	float x, y;
	float w = 75.f;
	float h = 152.f;
	sf::FloatRect rect;
	int dir;

	void setTextureRectByState(float time);
	void Collision(float Dx, float Dy);

};