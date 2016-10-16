#include "stdafx.h"
#include "Menu.h"
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>


using namespace sf;

void Menu::menu(RenderWindow & window)
{
	
	Music menuMusic;
	menuMusic.openFromFile("audio/menu1.ogg");
	menuMusic.play();

	Texture menuTextureStart,
		menuTextureExit,
		aboutTexture,

		menuBackground,
		startBackGround,
		name,
		character,
		enemy,
		play,
		instruction,
		back;
	name.loadFromFile("images/2.png");
	menuTextureStart.loadFromFile("images/menuStart.png");
	menuTextureExit.loadFromFile("images/menuExit.png");
	menuBackground.loadFromFile("images/background.png");
	//startBackGround.loadFromFile("images/1.jpg");
	startBackGround.loadFromFile("images/Back2.png");
	character.loadFromFile("images/menuCharacter.png");
	enemy.loadFromFile("images/menuEnemy.png");

	play.loadFromFile("images/menuPlay.png");
	back.loadFromFile("images/menuBack.png");

	instruction.loadFromFile("images/Rule.png");

	Sprite menuStart(menuTextureStart),
		menuExit(menuTextureExit),
		about(aboutTexture),
		menuName(name),
		menuBg(menuBackground),
		startBackG(startBackGround),
		menuCharacter(character),
		menuEnemy(enemy),
		menuPlay(play),
		menuBack(back),
		menuInstruction(instruction);

	bool isMenu = true;
	bool gameInstruction = false;
	int menuNum = 0;

	Clock clock;
	float currentFrame = 0;

	
	startBackG.setPosition(0, 0);

	while (isMenu || gameInstruction)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		if (isMenu)
		{
			menuBg.setPosition(0, 0);
			
			currentFrame += time * 0.004f;
			if (currentFrame > 6)
			{
				currentFrame = 0;
			}

			menuCharacter.setTextureRect(IntRect(0, 455 * (int)currentFrame, 560, 455)); // Ширина (int*высота ширина, высота).
			menuCharacter.setPosition(80, 90);
			menuEnemy.setTextureRect(IntRect(0, 455 * (int)currentFrame, 560, 455)); 
			menuEnemy.setPosition(400, 90);

			menuName.setPosition(300, 108); // Позиция имени меню.
			menuStart.setPosition(340, 280); // Позиция start   (x,y).
			menuExit.setPosition(340, 362); // Позиция exit 

			menuStart.setColor(Color::White);
			menuExit.setColor(Color::White);

			if (IntRect(360, 280, 300, 60).contains(Mouse::getPosition(window))) // Start.
			{
				menuStart.setColor(Color::Green);
				menuNum = 1;
			}
			if (IntRect(360, 362, 300, 60).contains(Mouse::getPosition(window))) // Exit.
			{
				menuExit.setColor(Color::Red);
				menuNum = 2;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1)
				{
					isMenu = false;
					gameInstruction = true;
					
				}
				if (menuNum == 2)
				{
					window.close();
					isMenu = false;
				}
			}
			window.clear();
			window.draw(menuBg);
			window.draw(menuName);
			window.draw(menuCharacter);
			window.draw(menuEnemy);
			window.draw(menuStart);
			window.draw(menuExit);
			window.display();
		}

		else if (gameInstruction)
		{

			currentFrame += time * 0.0035f;
			if (currentFrame > 4)
			{
				currentFrame = 0;
			}
			
			menuInstruction.setTextureRect(IntRect(0, 455 * (int)currentFrame, 500, 455));
			menuInstruction.setPosition(260, 80);

			menuPlay.setPosition(680, 515); // Позиция play (x,y).
			menuBack.setPosition(10, 515); // Позиция back.
			
			menuPlay.setColor(Color::White);
			menuBack.setColor(Color::White);

			if (IntRect(640, 499, 300, 60).contains(Mouse::getPosition(window))) // Play.
			{
				menuPlay.setColor(Color::Green);
				menuNum = 3;
			}
			if (IntRect(140, 499, 300, 60).contains(Mouse::getPosition(window))) // Back.
			{
				menuBack.setColor(Color::Red);
				menuNum = 4;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 3)
				{
					gameInstruction = false;
				}
				if (menuNum == 4)
				{
					gameInstruction = false;
					isMenu = true;
				}
			}
			window.clear();
			window.draw(startBackG);
			
			window.draw(menuPlay);
			window.draw(menuBack);

			window.draw(menuInstruction);
			window.display();
		}

	}	
	
}

