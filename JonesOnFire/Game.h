#pragma once
#include "stdafx.h"
#include "Player.h"
#include "TinyXML/tinyxml.h"
#include "level.h"
#include "view.h"
#include "InitialData.h"
#include "weapons.h"

using namespace sf;
using namespace std;

void InitTextures(Textures & structure)
{
	Image hero_image;
	hero_image.loadFromFile("images/new hero.psd");
	structure.hero.loadFromImage(hero_image);

	Image bonus_image;
	bonus_image.loadFromFile("images/bonus.png");
	structure.bonus1.loadFromImage(bonus_image);

	Image enemy_image;
	enemy_image.loadFromFile("images/enemy.psd");
	structure.enemy.loadFromImage(enemy_image);

	Image weapon_image;
	weapon_image.loadFromFile("images/weapon.psd");
	structure.weapon.loadFromImage(weapon_image);

	Image bang_image;
	bang_image.loadFromFile("images/shooting.psd");
	structure.bang.loadFromImage(bang_image);

	Image star_image;
	star_image.loadFromFile("images/star.png");
	structure.star.loadFromImage(star_image);

	Image end_image;
	end_image.loadFromFile("images/GameOver.png");
	structure.endGame.loadFromImage(end_image);

	//Font font;//шрифт 
	structure.font.loadFromFile("CyrilicOld.ttf");
}


void PrintScorOnTheTable(RenderWindow & window, Textures & textures,  string const& name, int score, float x, float y)
{
	Text text("", textures.font, 50);
	if (name == "Bonus Life: " && score <= 80 || name == "Life: " && score <= 20)
	{
		text.setColor(Color::Red);
	}
	else if (name == "Bonus Life: " && score > 20 || name == "Life: " && score > 20)
	{
		text.setColor(Color::Green);
	}
	
	std::ostringstream playerScoreString;    // объявили переменную
	playerScoreString << score;	//занесли в нее число очков, то есть формируем строку
	text.setString(name  + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше ст

	text.setPosition(x, y);//задаем позицию текста, центр камеры
	window.draw(text);//рисую этот текст
}
void InitEnemiesList(Level & lvl, ObjectsOfTheWorld & obj, Textures & texture, std::vector<Enemy> & enemies)
{
	vector<Object> enemiesList = lvl.GetObjects("enemy");
	for (auto i : enemiesList)
	{
		enemies.push_back(Enemy(texture.enemy, lvl, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
	}
}

void EntitiesIntersection(ObjectsOfTheWorld &game, vector<Enemy> &enemies, vector<CWeapon> &weapons, Player & player, int score)
{
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
		if (enemy->GetRect().intersects(player.GetRect()) && (!enemy->hurt) && (enemy->life))
		{
			enemy->hurt = true;
			game.health -= 15;
			Clock clock;
			float time = clock.getElapsedTime().asMicroseconds();
			
			time = time / 800;
			
			player.sprite.setColor(Color::Red); //красный спрайт 0,1 секунда(появление), 0.2(красный), 0,1(исчезновение)
			time = 0;
			
		}
		for (auto weapon = weapons.begin(); weapon != weapons.end(); weapon++)
		{
			if (enemy->GetRect().intersects(weapon->GetRect()))
			{
				/////////// ПЕРЕСЕЧЕНИЕ ВРАГА С ПУЛЕЙ И УМЕНЬШЕНИЕ ЖИЗНИ /////////////////
				weapon->life = false;
				enemy->health -= 40;
				if (enemy->health <= 0)
				{
					enemy->life = false;
					enemy->currentFrame = 0;
				}
			}
		}
	}
}

void DrawListObjects(RenderWindow & window, float time, std::vector<Object> const& list, std::string const& name, Texture & texture, int left, int top, float & currentFrame)
{
	currentFrame += 0.01f * time;

	if (currentFrame > 6) currentFrame = 0;
	for (auto obj : list)
	{
		if (obj.name == name)
		{
			Sprite spr;
			spr.setTexture(texture);
			spr.setTextureRect(IntRect(left + (int)currentFrame * obj.rect.width, top, obj.rect.width, obj.rect.height));
			spr.setPosition(obj.rect.left, obj.rect.top);
			window.draw(spr);
		}
	}
}

void UpdateAndDrawEnemiesAndWeapons(RenderWindow & window, std::vector<Enemy> & enemies, std::vector<CWeapon> & weapons, float time)
{
	for (auto it = enemies.begin(); it != enemies.end(); it++)
	{
		it->Update(time);
	}
	for (auto it = weapons.begin(); it != weapons.end();)
	{
		it->Update(time);
		if (!it->life)
		{
			it = weapons.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (CWeapon &weapon : weapons)
	{
		if (weapon.born)
		{
			window.draw(weapon.bang);
		}
		else
		{
			window.draw(weapon.sprite);
		}
	}
	for (Enemy enemy : enemies)
	{
		window.draw(enemy.sprite);
	}
}

void DrawAllObjects(RenderWindow & window, Level & lvl,  Player & hero, ObjectsOfTheWorld & worldObj, Textures & textures, float time, std::vector<Enemy> & enemies, std::vector<CWeapon> & weapons)
{
	window.clear(Color::White);
	lvl.Draw(window);
	DrawListObjects(window, time, hero.obj, "bonus", textures.bonus1, 0, 0, worldObj.bonusCurrentFrame);
	DrawListObjects(window, time, hero.obj, "star", textures.star, 0, 0, worldObj.starCurrentFrame);
	UpdateAndDrawEnemiesAndWeapons(window, enemies, weapons, time);
	
	PrintScorOnTheTable(window, textures,  "Bonus Life: ",  worldObj.score, getCenterViewX(hero.getplayercoordinateX()) - 450, getCenterViewY(hero.getplayercoordinateY()) - 300);
	
	PrintScorOnTheTable(window, textures, "Life: ", worldObj.health, getCenterViewX(hero.getplayercoordinateX()) - 450, getCenterViewY(hero.getplayercoordinateY()) - 255);
	
	window.draw(hero.sprite);

	if (worldObj.health <= 0)
	{
		Texture endGame;
		endGame.loadFromFile("images/GameOver.png");
		Sprite Game_Over(endGame);
		Game_Over.setPosition(getCenterViewX(hero.getplayercoordinateX()) - 200, getCenterViewY(hero.getplayercoordinateY()) - 180);
		//window.clear();
		window.draw(Game_Over);

	}
	
	window.display();
}

string GetLevel(ObjectsOfTheWorld & oow)
{
	stringstream stream;
	stream << "level" << (oow.level) << ".tmx";
	string result;
	stream >> result;
	return result;
}


bool StartGame(RenderWindow & window, Textures & textures, ObjectsOfTheWorld & worldObj)
{
	std::vector<Enemy> enemies;
	std::vector<CWeapon> weapons;
	Level lvl;
	lvl.LoadFromFile(GetLevel(worldObj));
	Player player(textures.hero, lvl);


	InitEnemiesList(lvl, worldObj, textures, enemies);
	Clock clock;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Tab))
			{
				worldObj.bonusCurrentFrame = 0;
				 worldObj.starCurrentFrame = 0;
				 worldObj.level = 1;
				 worldObj.newLevel = false;
				 worldObj.score = 0;
				 worldObj.health = 100;
				return true;

			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
				return false;
			}
			if (player.isShoot == true)
			{
				weapons.push_back(CWeapon(textures.weapon, player, lvl, time, textures.bang));
				player.isShoot = false;
			}
			if ((event.type == event.KeyReleased) && (event.key.code == Keyboard::Z))
			{
				player.currentFrame = 0;
				player.readyToShoot = true;
			}
		}
		player.Player::Update(time, worldObj);

		if (player.isLevelUp())
		{
			worldObj.level += (worldObj.level >= 3 ? 0 : 1);
			return true;
		}
		SetCoordinateForView(player.getplayercoordinateX(), player.getplayercoordinateY());
		window.setView(view);
		EntitiesIntersection(worldObj, enemies, weapons, player, worldObj.score);
		DrawAllObjects(window, lvl, player, worldObj, textures, time, enemies, weapons);
	}
}

void GameRunning(RenderWindow & window, Textures & textures, ObjectsOfTheWorld & worldObj)
{
	if (StartGame(window, textures, worldObj))
	{
		GameRunning(window, textures, worldObj);
	}
}
