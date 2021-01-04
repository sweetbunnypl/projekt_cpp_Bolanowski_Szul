#pragma once
#include "libs.h"

class Enemy
{
public:
	Enemy();
	~Enemy();
	int speedAtack;
	sf::Vector2f speed;
	sf::Vector2f size;
	int health;
	int damage;
	int terrorRadius;

	//sf::Sprite sprite;
	sf::RectangleShape sprite;
	sf::Texture texture;
	sf::CircleShape terror;

	void create(sf::Vector2f position, sf::Vector2f scale);
	void render(sf::RenderTarget* target);
};
