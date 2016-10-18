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
	int health;
	bool gameOver = false;
	void Control();

	bool EndGame();
	void Update(float time);
	float getplayercoordinateX() { return x; }
	float getplayercoordinateY() { return y; }
	sf::Sprite sprite;
	Direction state;
	FloatRect GetRect();
	std::vector<Object> obj;
	direct dir;
	bool isLevelUp();
private:
	float endFrame = 0;
	float x, y;
	float currentFrameJump;
	float w = 75.f;
	float h = 153.f;
	sf::FloatRect rect;
	bool jump;
	bool levelUp;

	void ShootAnimation();
	
	void setTextureRectByState(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void JumpAnimation(float time);
};