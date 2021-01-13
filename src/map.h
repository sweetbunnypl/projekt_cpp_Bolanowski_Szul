#pragma once
#include "libs.h"

class Map
{
public:
	Map();
	~Map();

	// background
	sf::Texture backgroundTexture;
	sf::Texture shopBackgroundTexture;
	sf::Texture shopTexture;
	sf::Sprite background;

	// collision object (borders..)
	sf::Sprite object[53];
	sf::Texture tilesTexture;

	int mnoznik;

	void initMap(sf::Texture& texture);
	void renderMap(sf::RenderTarget* target);

	void initObjects(sf::Texture& texture);
	void renderObject(sf::RenderTarget* target);

};

class Shop : public Map
{
public:
	Shop();

	sf::Font font;
	sf::Text text[10];

	void renderPrices(sf::RenderTarget* target);
};

class StartingRoom : public Map
{
public:
	StartingRoom();
};
