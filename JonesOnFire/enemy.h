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

	void Update(float time);
	float getplayercoordinateX() { return x; }
	float getplayercoordinateY() { return y; }
	sf::Sprite sprite;
	enum { UP, LEFT, RIGHT, DOWN } state;
	FloatRect GetRect();
	std::vector<Object> obj;
	int health;
	bool life;
private:
	float x, y;
	float currentFrame, currentFrameJump;
	float w = 75.f;
	float h = 152.f;
	sf::FloatRect rect;
	int dir;

	void setTextureRectByState(float time);
	void Collision(float Dx, float Dy);

};