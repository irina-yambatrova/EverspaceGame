#include "stdafx.h"
#include "Player.h"

using namespace std;
using namespace sf;

Player::Player(Texture & texture)
	: dx(0.01f)
	, dy(0.01f)
	, playerScore(0)
	, currentFrame(0)
{
	rect = sf::FloatRect(0, 0, w, h);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Player::Control()
{
	if ((Keyboard::isKeyPressed(Keyboard::Left)))
	{
		dx = -0.1;
	}

	if ((Keyboard::isKeyPressed(Keyboard::Right)))
	{
		dx = 0.1;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)))
	{
		jump = true;
	}
}

void Player::Update(float time)
{
	currentFrame += 0.005 * time;
	if (currentFrame > 6) currentFrame -= 6;
	if (dx > 0)
	{
		sprite.setTextureRect(IntRect(w * int(currentFrame), h, w, h));
		sprite.setScale(1, 1);
	}
	if (dx < 0)
	{
		sprite.setTextureRect(IntRect(w * int(currentFrame), h, w, h));
		sprite.setScale(-1, 1);
	}
	if (jump)
	{

	}
	x += dx * time;
	sprite.setPosition(x, 200);
	dx = 0;
}