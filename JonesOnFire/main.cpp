#include "stdafx.h"
#include "Menu.h"
#include "Game.h"


int main()
{
	RenderWindow window(sf::VideoMode(WINDOWS_WIDTH, WINDOWS_HEIGHT), "EVERSPACE");
	view.reset(sf::FloatRect(0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT));

	Menu::menu(window);


	
	Textures textures;
	InitTextures(textures);
	ObjectsOfTheWorld worldObj;

	Music menuMusic;
	menuMusic.openFromFile("audio/main.wav");
	menuMusic.play();
	GameRunning(window, textures, worldObj);
	
	return 0;
}