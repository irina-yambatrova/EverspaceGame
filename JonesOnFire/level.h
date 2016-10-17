#ifndef LEVEL_H
#define LEVEL_H


#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TinyXML/tinyxml.h"
#include <string>
#include <vector>
#include <list>

using namespace sf;

struct Object
{
	int GetPropertyInt(std::string name);//����� �������� ������� � ����� ������
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
	std::string name;//�������� ���������� name ���� string
	std::string type;//� ����� ���������� type ���� string
	sf::Rect<float> rect;//��� Rect � �������� ����������
	std::map<std::string, std::string> properties;//������ ������������ ������. ���� - ��������� ���, �������� - ���������
	sf::Sprite sprite;//�������� ������
	bool find = false;
};

struct Layer//����
{
	int opacity;//�������������� ����
	std::vector<sf::Sprite> tiles;//���������� � ������ �����
};

class Level//������� ����� - �������
{
public:
	bool LoadFromFile(std::string filename);//���������� false ���� �� ���������� ���������
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);
	std::vector<Object> GetAllObjects();//������ ��� ������� � ��� �������
	void Draw(sf::RenderWindow &window);//������ � ����
	sf::Vector2i GetTileSize();//�������� ������ �����
	void DrawDynamicObjects(std::vector<Object> &obj, sf::RenderWindow &window, std::string name, sf::Sprite &sprite, int left, int top, float time, float &current_frame);
	void DrawStaticObjects(std::vector<Object> &obj, sf::RenderWindow &window, std::string name, sf::Sprite &sprite, int left, int top);
	void DrawDynamicSprite(sf::RenderWindow &window, sf::Sprite &sprite, int left, int top, int w, int h, int x, int y);
	bool Level::�oincidenceNames(std::string name);
	bool Level::IsExist(std::string name);
private:
	int width, height, tileWidth, tileHeight;//� tmx ����� width height � ������,����� ������ �����
	int firstTileID;//�������� ���� ������� �����
	sf::Rect<float> drawingBounds;//������ ����� ����� ������� ������
	sf::Texture tilesetImage;//�������� �����
	std::vector<Object> objects;//������ ���� �������, ������� �� �������
	std::vector<Layer> layers;
};
#endif
