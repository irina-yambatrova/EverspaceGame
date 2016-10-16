#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>

const int ground = 420;


class Player
{
public:
	Player(sf::Texture & texture);

	float dx, dy, speed;
	int dir, playerScore;//новая переменная, хранящая очки игрока
	bool onGround;

	void Control();
	void Update(float time);
	float getplayercoordinateX() { return x; }
	float getplayercoordinateY() { return y; }
	sf::Sprite sprite;
private:
	float x = 0;
	float y = 0;
	float currentFrame;
	float w = 75.f;
	float h = 152.f;
	sf::FloatRect rect;
	bool jump;
};