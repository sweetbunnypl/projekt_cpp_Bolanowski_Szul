#pragma once
#include "libs.h"

class Gui
{
public:
	Gui();

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text number[5];
	sf::Text text[3];
	sf::RectangleShape test;

	sf::Vector2f size;

	sf::Sprite heart;
	sf::Sprite shard;
	sf::Sprite skull;
	sf::Sprite coin;
	sf::Sprite key;

	sf::Texture guiTexture;

	void initGui();
	void changeValues(int& coins, int& keys, int& level, int& wave, float& time);
	void render(sf::RenderTarget* target);
};
