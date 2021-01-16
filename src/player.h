#pragma once
#include "libs.h"

class Player
{
public:
	// constructor and destructor
	Player();

	// SFML objects
	sf::Texture playerTexture;
	sf::Sprite sprite;
	sf::Vector2u textureSize;

	sf::Texture goldenRed;
	sf::Texture goldenBlue;
	sf::Texture goldenCyan;

	sf::Texture silverRed;
	sf::Texture silverBlue;
	sf::Texture silverCyan;

	sf::Texture copperRed;
	sf::Texture copperBlue;
	sf::Texture copperCyan;

	sf::Texture copperArmor;
	sf::Texture silverArmor;
	sf::Texture goldenArmor;

	sf::Texture redSword;
	sf::Texture blueSword;
	sf::Texture cyanSword;

	sf::Vector2f size;
	sf::Vector2f position;

	int frame;
	int attackFrame;

	const float fullHP = 100.f;
	float hp;				// jak duzo ma zdrowia
	float dmg;				// jak bardzo napierdala
	float def;				// mnoznik obrony
	float speed;			// jak bardzo zapierdala
	int level;				// jaki ma poziom
	float poisoning;		// jak bardzo sie uchalal miksturami

	int coins;			// ile zebral coinsow
	int keys;			// ile zebral kluczy
	float xp;			// ile zebral lvl shardsow

	bool drunk;			// czy sie uchlal miksturami

	void initTexture();
	void initSprite();
	void changePlayerEQ(bool& red, bool& blue, bool& cyan, bool& copper, bool& silver, bool& golden);
	void render(sf::RenderTarget* target);

};

