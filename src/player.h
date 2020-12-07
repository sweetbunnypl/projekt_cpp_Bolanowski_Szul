#pragma once
#include "libs.h"

class Player
{
public:
	// constructor and destructor
	Player();
	~Player();

	// SFML objects
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Vector2u textureSize;

	float playerHealth;
	int liczba;

	void initTexture();
	void initSprite();
	//void updateMovement(const float& deltaTime, const float x, const float y);

	//void update(const float& deltaTime);
	void render(sf::RenderTarget* target);

};

