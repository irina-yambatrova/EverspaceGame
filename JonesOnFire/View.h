#include <SFML/Graphics.hpp>
#include "InitialData.h"

using namespace sf;

sf::View view;//объявили sfml объект "вид", который и является камерой

void SetCoordinateForView(float x, float y) //функция для считывания координат игрока
{
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < WINDOWS_WIDTH / 2.f) tempX = WINDOWS_WIDTH / 2.f;//убираем из вида левую сторону
	if (y > 450) tempY = 450;
	if (y < 450) tempY = 450;
	if (y < 150) tempY = 300;
	view.setCenter(tempX, tempY);
}

float getCenterViewX(float x)
{
	float tempX = x;

	if (x < WINDOWS_WIDTH / 2.f) tempX = WINDOWS_WIDTH / 2.f;//убираем из вида левую сторону

	return tempX;
}

float getCenterViewY(float y)
{
	float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (y > 450) tempY = 450;
	if (y < 450) tempY = 450;
	if (y < 150) tempY = 300;
	//view.setCenter(tempX, tempY);

	return tempY;
}