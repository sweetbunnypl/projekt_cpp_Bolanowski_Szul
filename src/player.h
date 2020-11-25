#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Player
{
public:

	Player();
	~Player();

	sf::Texture playerTexture;
	sf::Sprite playerSprite;

	float movementSpeed;

	void initTexture();
	void initSprite();
	void updateMovement(const float& deltaTime, const float x, const float y);

	void update(const float& deltaTime);
	void render(sf::RenderTarget* target);

};

