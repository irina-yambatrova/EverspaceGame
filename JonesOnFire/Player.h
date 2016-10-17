#pragma once
#include "stdafx.h"
#include "level.h"
#include "InitialData.h"

class Player
{
public:
	Player(sf::Texture & texture, Level & lvl);

	float dx, dy, speed;
	int score;
	bool onGround;
	bool isShoot;
	bool readyToShoot;
	float currentFrame;

	void Control();
	void Update(float time);
	float getplayercoordinateX() { return x; }
	float getplayercoordinateY() { return y; }
	sf::Sprite sprite;
	Direction state;
	FloatRect GetRect();
	std::vector<Object> obj;
private:
	float x, y;
	float currentFrameJump;
	float w = 75.f;
	float h = 152.f;
	sf::FloatRect rect;
	bool jump;

	void ShootAnimation();
	

	void setTextureRectByState(float time);
	void Collision(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void JumpAnimation(float time);
};