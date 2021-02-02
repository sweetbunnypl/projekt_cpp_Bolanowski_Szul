#include "gui.h"

Gui::Gui()
{
	initGui();
}

void Gui::initGui()
{
	this->size = sf::Vector2f(354.f, 720.f);
	this->shape.setSize(size);
	this->shape.setFillColor(sf::Color(42, 30, 50));
	this->shape.setPosition(926.f, 0.f);

	if (!this->guiTexture.loadFromFile("res/textures/gui.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the gui sheet!" << "\n";
	}

	if (!this->font.loadFromFile("res/fonts/dogica.ttf"))
	{
		std::cout << "ERROR::PLAYER::Could not load the font file!" << "\n";
	}

	heart.setTexture(guiTexture);
	shard.setTexture(guiTexture);
	skull.setTexture(guiTexture);
	key.setTexture(guiTexture);
	coin.setTexture(guiTexture);
	healthBar.setTexture(guiTexture);
	xpBar.setTexture(guiTexture);
	drunkBar.setTexture(guiTexture);
	emptyBar.setTexture(guiTexture);

	heart.setTextureRect(sf::IntRect(0, 140, 60, 60));
	shard.setTextureRect(sf::IntRect(60, 140, 60, 60));
	skull.setTextureRect(sf::IntRect(120, 140, 60, 60));
	key.setTextureRect(sf::IntRect(180, 140, 60, 60));
	coin.setTextureRect(sf::IntRect(240, 140, 60, 60));
	healthBar.setTextureRect(sf::IntRect(242, 0, 242, 48));
	xpBar.setTextureRect(sf::IntRect(242, 48, 242, 48));
	drunkBar.setTextureRect(sf::IntRect(242, 96, 242, 48));
	emptyBar.setTextureRect(sf::IntRect(0, 0, 242, 48));

	heart.setPosition(940.f, 40.f);
	shard.setPosition(940.f, 100.f);
	skull.setPosition(940.f, 160.f);
	coin.setPosition(940.f, 260.f);
	key.setPosition(1090.f, 260.f);
	healthBar.setPosition(1000.f, 47.f);
	xpBar.setPosition(1000.f, 107.f);
	drunkBar.setPosition(1000.f, 167.f);

	for (int i = 0; i < 3; i++)
	{
		emptyBar.setPosition(1000.f, 47.f + i * 60);
		emptyBars.push_back(emptyBar);
	}

	text[0].setFont(font);
	text[0].setCharacterSize(26);
	text[0].setFillColor(sf::Color::White);
	text[0].setString("level");
	text[0].setPosition(950.f, 570.f);

	text[1].setFont(font);
	text[1].setCharacterSize(26);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("wave");
	text[1].setPosition(950.f, 620.f);

	text[2].setFont(font);
	text[2].setCharacterSize(26);
	text[2].setFillColor(sf::Color::White);
	text[2].setString("time");
	text[2].setPosition(950.f, 670.f);
}

void Gui::changeValues(int& coins, int& level, int& wave, float& time, float& hp, const float& fullHP, float& xp, float& xpRequired, float& poison)
{
	std::string cN = std::to_string(coins);
	number[0].setFont(font);
	number[0].setCharacterSize(30);
	number[0].setFillColor(sf::Color::White);
	number[0].setString(cN);
	number[0].setPosition(1020.f, 275.f);

	std::string lN = std::to_string(level);
	number[2].setFont(font);
	number[2].setCharacterSize(30);
	number[2].setFillColor(sf::Color::White);
	number[2].setString(lN);
	number[2].setPosition(1110.f, 570.f);

	std::string wN = std::to_string(wave);
	number[3].setFont(font);
	number[3].setCharacterSize(30);
	number[3].setFillColor(sf::Color::White);
	number[3].setString(wN);
	number[3].setPosition(1110.f, 620.f);

	std::string tN = std::to_string(time);
	number[4].setFont(font);
	number[4].setCharacterSize(30);
	number[4].setFillColor(sf::Color::White);
	number[4].setString(tN);
	number[4].setPosition(1110.f, 670.f);

	test.setSize(sf::Vector2f(60.f, 30.f));
	test.setFillColor(sf::Color(42, 30, 50));
	test.setPosition(1223.f, 670.f);

	healthBar.setTextureRect(sf::IntRect(242, 0, 11 + (hp / fullHP) * 221, 48));
	xpBar.setTextureRect(sf::IntRect(242, 48, 11 + (xp/xpRequired) * 221, 48));
	drunkBar.setTextureRect(sf::IntRect(242, 96, 11 + poison * 221, 48));
}

void Gui::render(sf::RenderTarget* target)
{
	target->draw(this->shape);

	target->draw(this->heart);
	target->draw(this->shard);
	target->draw(this->skull);
	target->draw(this->coin);

	target->draw(this->number[0]);
	target->draw(this->number[2]);
	target->draw(this->number[3]);
	target->draw(this->number[4]);

	target->draw(this->text[0]);
	target->draw(this->text[1]);
	target->draw(this->text[2]);

	target->draw(this->test);
	
	for (int i = 0; i < 3; i++)
	{
		target->draw(this->emptyBars[i]);
	}

	target->draw(this->healthBar);
	target->draw(this->xpBar);
	target->draw(this->drunkBar);
}
