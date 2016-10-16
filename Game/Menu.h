#include "stdafx.h"
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>

using namespace sf;

class Menu
{
	public:
		bool isMenu;
		int menuNum;
		Clock clock;
		float currentFrame = 0;
		static void menu(RenderWindow & window);
};
