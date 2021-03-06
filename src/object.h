#pragma once
#include "libs.h"

class Object
{
public:
	Object();

	int mnoznik;
	int liczba;
	int spriteWidth;
	int frame;

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

class Bonfire : public Object
{
public:
	Bonfire();
};

class Portal : public Object
{
public:
	Portal();
};

class UNArmor : public Object
{
public:
	UNArmor();
};

class UNSword : public Object
{
public:
	UNSword();
};

class UNPotion : public Object
{
public:
	UNPotion();
};