#include <SFML/Graphics.hpp>
#include "InitialData.h"

using namespace sf;

sf::View view;//�������� sfml ������ "���", ������� � �������� �������

void SetCoordinateForView(float x, float y) //������� ��� ���������� ��������� ������
{
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < WINDOWS_WIDTH / 2.f) tempX = WINDOWS_WIDTH / 2.f;//������� �� ���� ����� �������
	if (y > 450) tempY = 450;
	if (y < 450) tempY = 450;
	if (y < 150) tempY = 300;
	view.setCenter(tempX, tempY);
}

float getCenterViewX(float x)
{
	float tempX = x;

	if (x < WINDOWS_WIDTH / 2.f) tempX = WINDOWS_WIDTH / 2.f;//������� �� ���� ����� �������

	return tempX;
}

float getCenterViewY(float y)
{
	float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (y > 450) tempY = 450;
	if (y < 450) tempY = 450;
	if (y < 150) tempY = 300;
	//view.setCenter(tempX, tempY);

	return tempY;
}