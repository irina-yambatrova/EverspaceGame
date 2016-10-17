#include <SFML/Graphics.hpp>
#include "InitialData.h"

using namespace sf;

sf::View view;//объ€вили sfml объект "вид", который и €вл€етс€ камерой

void SetCoordinateForView(float x, float y) //функци€ дл€ считывани€ координат игрока
{
	float tempX = x; float tempY = y;//считываем коорд игрока и провер€ем их, чтобы убрать кра€

	if (x < WINDOWS_WIDTH / 2.f) tempX = WINDOWS_WIDTH / 2.f;//убираем из вида левую сторону
	if (y > 450) tempY = 450;
	if (y < 450) tempY = 450;
	if (y < 150) tempY = 300;
	view.setCenter(tempX, tempY);
}