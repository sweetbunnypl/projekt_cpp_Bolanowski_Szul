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

	// test level shards
	sf::Sprite shard;
	sf::Texture shardTexture;

	sf::Sprite coin;
	sf::Texture coinTexture;

	sf::Sprite key;
	sf::Texture keyTexture;

	sf::Sprite heart;
	sf::Texture heartTexture;

	int mnoznik;
	int liczba;
	int spriteWidth;

	void initMap(sf::Texture& texture);
	void renderMap(sf::RenderTarget* target);

	void initObjects(sf::Texture& texture);
	void renderObject(sf::RenderTarget* target);

	void testShards();
	void renderShards(sf::RenderTarget* target);
};

class Shop : public Map
{
public:
	Shop();
	~Shop();
};

class StartingRoom : public Map
{
public:
	StartingRoom();
	~StartingRoom();
};
