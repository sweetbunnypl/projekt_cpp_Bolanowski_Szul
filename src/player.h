#pragma once
#include "libs.h"

class Player
{
public:
	Player();
	~Player();

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Vector2u textureSize;

	thor::FrameAnimation playerDown;
	thor::FrameAnimation playerLeft;
	thor::FrameAnimation playerRight;
	thor::FrameAnimation playerUp;

	thor::Animator<sf::Sprite, std::string> playerAnimation;

	float movementSpeed;

	void initTexture();
	void initSprite();
	//void updateMovement(const float& deltaTime, const float x, const float y);

	//void update(const float& deltaTime);
	void render(sf::RenderTarget* target);

};

