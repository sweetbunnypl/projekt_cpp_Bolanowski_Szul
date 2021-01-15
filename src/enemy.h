#pragma once
#include "libs.h"

class Enemy
{
public:
	sf::Font font;
	sf::Text txtHealth;

	Enemy();
	~Enemy();

	int frame;

	float speedAtack;
	sf::Vector2f speed;
	sf::Vector2f size;
	float health;
	float damage;
	int terrorRadius;
	int attackRadius;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2u textureSize;

	//sf::Sprite sprite;
	//sf::RectangleShape sprite;
	//sf::Texture texture;
	sf::CircleShape terror;
	sf::CircleShape attack;

	void create(sf::Vector2f position, sf::Vector2f scale, sf::Vector2f textureScale);
	void render(sf::RenderTarget* target);
	void renderRadius(sf::RenderTarget* target);
	void initTexture();
	void initSprite();
	void updateHealth(int hp);
};

class GreenFrog : public Enemy
{
	GreenFrog();

	// okej, robisz tak
	// klasa enemy jest klas¹ ABSTRAKCYJNA - nie ma wizualizacji w klasie game
	// wiêc musisz wszystkie enemy w game pozamieniac na red/green frog
	
	// tutaj sobie zmieniasz wartoœci np speed, dmg, speed attack itp
	// jak cos to pisz
	// ewentualnie odwoluj sie do tego jak napisana jest klasa obiekt (klasa abstrakcyjna)
	// ze nie masz nigdzie dzialania na obiekcie klasy obiekt
	// tylko sa dzialania na obiektach dziedziczacych z klasy obiekt takich jak coin/shard
};

class RedFrog : public Enemy
{
	RedFrog();
};