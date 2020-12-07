#pragma once
#include "libs.h"

class Map
{
public:
	Map();
	~Map();

	// background
	sf::Texture mapBackgroundTexture;
	sf::Sprite mapBackground;

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

	void initMap();
	void renderMap(sf::RenderTarget* target);

	void initObjects();
	void renderObject(sf::RenderTarget* target);

	void testShards();
	void renderShards(sf::RenderTarget* target);
};

