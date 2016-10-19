#include "Player.h"

using namespace std;
using namespace sf;

Player::Player(Texture & texture, Level & lvl)
	: speed(0.2f)
	, currentFrame(0)
	, currentFrameJump(0)
	, state(STAY)
	, dy(0)
	, onGround(true)
	, readyToShoot(false)
	, levelUp(false)
{
	Object p = lvl.GetObject("hero");
	x = (float)p.rect.left;
	y = (float)p.rect.top;
	rect = sf::FloatRect(0, 0, w, h);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));
	dx = speed;
	obj = lvl.GetAllObjects();
}

void Player::Control()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		state = LEFT;
		dir = isleft;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		state = RIGHT;
		dir = isright;
	}
	else if (state == SHOOT)
	{

	}
	else
	{
		state = STAY;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround))
	{
		state = JUMP;
	}

	if (Keyboard::isKeyPressed(Keyboard::X) && (state == SHOOT))
	{
		isShoot = true;
	}
}

void Player::ShootAnimation()
{
}

void Player::setTextureRectByState(float time)
{
	currentFrame += 0.005 * time;
	if (currentFrame > 6) currentFrame -= 6;
	switch (state)
	{
	case (LEFT):
		dx = -speed;
		sprite.setTextureRect(IntRect(w * int(currentFrame), 2 * h, w, h));
		break;
	case (RIGHT):
		dx = speed;
		sprite.setTextureRect(IntRect(w * int(currentFrame), h, w, h));
		break;
	case (STAY):
		//sprite.setTextureRect(IntRect(w * int(currentFrame / 2.f), 0, w, h));
		break;
	case (JUMP):
		dy = -1.f;
		dx = 0.6f;
		onGround = false;
		break;
	case (SHOOT):
		if (dir == isright)
		{
			sprite.setTextureRect(IntRect(95 * 5, 5 * h, 95, h));
		}
		else if (dir == isleft)
		{
			sprite.setTextureRect(IntRect(95 * 5, 6 * h, 95, h));
		}
		break;
	}
		
}

void Player::JumpAnimation(float time)
{
	if (!onGround)
	{
		currentFrameJump += 0.006 * time;
		if (currentFrameJump > 2) currentFrameJump = 0;
		if (dx >= 0)
		{
			sprite.setTextureRect(IntRect(86 * int(currentFrameJump), 3 * h, 86, h));
			
		}
		else if (dx < 0)
		{
			sprite.setTextureRect(IntRect(86 * int(currentFrameJump), 4 * h, 86, h));
		}
	}
}


void Player::Update(float time, ObjectsOfTheWorld & world)
{
	if ((world.health <= 20) && (world.score >= 100))
	{
		world.health = 100;
		world.score -= 100;
	}
	if (world.health <= 0)
	{
		world.health = 0;
		if (endFrame < 4)
		{
			endFrame += time * 0.001;
			sprite.setTextureRect(IntRect(152 * (int)endFrame, 153 * 7, 152, 150));
		}
		else
		{
			sprite.setTextureRect(IntRect(152 * 3, 153 * 7, 152, 150));
			//sprite.setTextureRect(IntRect(0, 1430, 480, 150));
		}
		sprite.setPosition(x , y);
	}
	else
	{
		if ((readyToShoot) && (currentFrame < 6))
		{
			currentFrame += 0.01 * time;
			if (dir == isright)
			{
				sprite.setTextureRect(IntRect(95 * int(currentFrame), 5 * h, 95, h));
			}
			else if (dir == isleft)
			{
				sprite.setTextureRect(IntRect(95 * int(currentFrame), 6 * h, 95, h));
			}
		}
		else if ((readyToShoot) && (!currentFrame < 6))
		{
			readyToShoot = false;
			state = SHOOT;
			currentFrame = 0;
			setTextureRectByState(time);
			JumpAnimation(time);
		}
		else if (!readyToShoot)
		{
			setTextureRectByState(time);
			JumpAnimation(time);
		}

		Control();
		if (!onGround)
		{
			dy += time * 0.0015f;
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0, world);
		y += dy * time;
		checkCollisionWithMap(0, dy, world);
		sprite.setPosition(x, y);
		dy += 0.0015 * time;
		dx = 0;
	}
}

FloatRect Player::GetRect()
{
	return FloatRect( x, y, w, h );
}

bool Player::isLevelUp()
{
	return levelUp;
}

void Player::checkCollisionWithMap(float Dx, float Dy, ObjectsOfTheWorld & world)//ф ция проверки столкновений с картой
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		if (GetRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{			
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy > 0) //если мы шли вниз,
				{
					y = obj[i].rect.top - h;//то стопорим координату игрек персонажа.
					dy = 0;
					onGround = true;
				}
				if (Dy < 0)
				{
					y = obj[i].rect.top + obj[i].rect.height;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх
					dy = 0;
				}
				if (Dx > 0)
					x = obj[i].rect.left - w; // если идем вправо, то координата Х равна стена(символ 0) минус ширина персонажа
				if (Dx < 0)
					x = obj[i].rect.left + obj[i].rect.width;//аналогично идем влево
			}
			else if (obj[i].name == "bonus")
			{
				obj.erase(obj.begin() + i);
				world.score += BONUS_SCORE;
				//health += BONUS_SCORE;
			}
			else if ((obj[i].name == "enemy") || (obj[i].name == "solid1") || (obj[i].name == "star"))
			{

			}
			else if (obj[i].name == "door")
			{
				levelUp = true;
			}
			else { onGround = false; }
		}
}

