#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Map
{
public:
	Map();
	~Map();

	sf::Texture mapBackgroundTexture;
	sf::Sprite mapBackground;

	// collison test object
	sf::Sprite object[53];
	sf::Texture tilesTexture;

	int mnoznik;

	void initMap();
	void renderMap(sf::RenderTarget* target);

	void initObjects();
	void renderObject(sf::RenderTarget* target);
};

