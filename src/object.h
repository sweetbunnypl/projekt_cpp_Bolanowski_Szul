#pragma once
#include "libs.h"

class Object
{
public:
	int mnoznik;
	int liczba;
	int spriteWidth;

	sf::Sprite sprite;
	sf::Texture texture;
	void create(sf::Vector2f position, sf::Vector2f scale);
	void render(sf::RenderTarget* target);
};

class Heart : public Object
{
public:
	Heart();
};

class Key : public Object
{
public:
	Key();
};

class Shard : public Object
{
public:
	Shard();
};

class Coin : public Object
{
public:
	Coin();
};

class Seller : public Object
{
public:
	void shop();
};

class Armorer : public Seller
{
public:
	Armorer();
};
