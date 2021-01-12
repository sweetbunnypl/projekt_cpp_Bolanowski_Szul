#pragma once
#include "libs.h"

class Enemy
{
public:
	sf::Font font;
	sf::Text txtHealth;

	Enemy();
	~Enemy();
	int speedAtack;
	sf::Vector2f speed;
	sf::Vector2f size;
	int health;
	int damage;
	int terrorRadius;
	int attackRadius;

	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	sf::Vector2u textureSize;

	//sf::Sprite sprite;
	sf::RectangleShape sprite;
	sf::Texture texture;
	sf::CircleShape terror;
	sf::CircleShape attack;

	void create(sf::Vector2f position, sf::Vector2f scale, sf::Vector2f textureScale);
	void render(sf::RenderTarget* target);
	void renderRadius(sf::RenderTarget* target);
	void initTexture();
	void initSprite();
	void updateHealth(int hp);
};
