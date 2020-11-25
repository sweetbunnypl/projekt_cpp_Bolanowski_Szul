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
	sf::RectangleShape object;

	void initMap();
	void initTestObject();
	void renderMap(sf::RenderTarget* target);
	void renderObject(sf::RenderTarget* target);
};

