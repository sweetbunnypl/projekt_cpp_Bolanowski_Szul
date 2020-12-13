#pragma once
#include "libs.h"

class Enemy
{
public:
	Enemy();
	~Enemy();
	int speed_atack;
	sf::Vector2f speed;
	int health;
	int damage;
	int terror_r;

	//sf::Sprite sprite;
	sf::RectangleShape sprite;
	sf::Texture texture;
	sf::CircleShape terror;

	void create(sf::Vector2f position, sf::Vector2f scale);
	void render(sf::RenderTarget* target);
};

