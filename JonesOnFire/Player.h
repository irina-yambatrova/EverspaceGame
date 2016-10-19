#pragma once
#include "stdafx.h"
#include "level.h"
#include "InitialData.h"

class Player
{
public:
	Player(sf::Texture & texture, Level & lvl);

	float dx, dy, speed;
	bool onGround;
	bool isShoot;
	bool readyToShoot;
	float currentFrame;
	bool gameOver = false;
	void Control();

	//bool EndGame();
	void Update(float time, ObjectsOfTheWorld & world);
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
	void checkCollisionWithMap(float Dx, float Dy, ObjectsOfTheWorld & world);
	void JumpAnimation(float time);
};