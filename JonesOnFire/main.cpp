#include "stdafx.h"
#include "Menu.h"
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
}

void InitEnemiesList(Level & lvl, ObjectsOfTheWorld & obj, Textures & texture, std::vector<Enemy> & enemies)
{
	vector<Object> enemiesList = lvl.GetObjects("enemy");
	for (auto i : enemiesList)
	{
		enemies.push_back(Enemy(texture.enemy, lvl, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
	}
}

void EntitiesIntersection(ObjectsOfTheWorld &game, vector<Enemy> &enemies, vector<CWeapon> &weapons)
{
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
		for (auto weapon = weapons.begin(); weapon != weapons.end(); weapon++)
		{
			if (enemy->GetRect().intersects(weapon->GetRect()))
			{
				/////////// ÏÅÐÅÑÅ×ÅÍÈÅ ÂÐÀÃÀ Ñ ÏÓËÅÉ È ÓÌÅÍÜØÅÍÈÅ ÆÈÇÍÈ /////////////////
				weapon->life = false;
				enemy->health -= 40;
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
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		it->Update(time);

		if (!it->life)
		{
			it = enemies.erase(it);
		}
		else
		{
			it++;
		}
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
		window.draw(weapon.sprite);
	}
	for (Enemy enemy : enemies)
	{
		window.draw(enemy.sprite);
	}
}

void DrawAllObjects(RenderWindow & window, Level & lvl, Player & hero, ObjectsOfTheWorld & worldObj, Textures & textures, float time, std::vector<Enemy> & enemies, std::vector<CWeapon> & weapons)
{
	window.clear(Color::White);
	lvl.Draw(window);
	DrawListObjects(window, time, hero.obj, "bonus", textures.bonus1, 0, 0, worldObj.bonusCurrentFrame);
	UpdateAndDrawEnemiesAndWeapons(window, enemies, weapons, time);
	window.draw(hero.sprite);
	window.display();
}

void StartGame(RenderWindow & window, Textures & textures)
{
	std::vector<Enemy> enemies;
	std::vector<CWeapon> weapons;
	Level lvl;
	lvl.LoadFromFile("level1.tmx");
	Player player(textures.hero, lvl);
	ObjectsOfTheWorld worldObj;
	
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
				window.close();
			if (player.isShoot == true)
			{
				weapons.push_back(CWeapon(textures.weapon, player, lvl, time));
				player.isShoot = false;
			}
			if ((event.type == event.KeyReleased) && (event.key.code == Keyboard::Z))
			{
				player.state = ((player.state != SHOOT) ? SHOOT : player.state);
				player.currentFrame = 0;
				player.readyToShoot = true;
			}
		}
		
		player.Player::Update(time);

		for (CWeapon &weapon : weapons)
		{
			weapon.Update(time);
		}

		SetCoordinateForView(player.getplayercoordinateX(), player.getplayercoordinateY());
		window.setView(view);
		EntitiesIntersection(worldObj, enemies, weapons);
		DrawAllObjects(window, lvl, player, worldObj, textures, time, enemies, weapons);
	}
}

int main()
{
	RenderWindow window(sf::VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), "EVERSPACE");
	view.reset(sf::FloatRect(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT));
	
	Menu::menu(window);

	Textures textures;
	InitTextures(textures);

	StartGame(window, textures);
	return 0;
}