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

	int frame;
	int attackFrame;

	int hp;				// jak duzo ma zdrowia
	float dmg;			// jak bardzo napierdala
	float def;			// mnoznik obrony
	float speed;		// jak bardzo zapierdala
	int level;			// jaki ma poziom
	float poisoning;	// jak bardzo sie uchalal miksturami

	int coins;			// ile zebral coinsow
	int keys;			// ile zebral kluczy
	float xp;			// ile zebral lvl shardsow

	bool drunk;			// czy sie uchlal miksturami

	void initTexture();
	void initSprite();
	void render(sf::RenderTarget* target);

};

