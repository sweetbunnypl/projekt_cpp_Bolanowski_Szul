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

	this->heart.setTexture(this->guiTexture);
	this->shard.setTexture(this->guiTexture);
	this->skull.setTexture(this->guiTexture);
	this->key.setTexture(this->guiTexture);
	this->coin.setTexture(this->guiTexture);

	this->heart.setTextureRect(sf::IntRect(0, 140, 60, 60));
	this->shard.setTextureRect(sf::IntRect(60, 140, 60, 60));
	this->skull.setTextureRect(sf::IntRect(120, 140, 60, 60));
	this->key.setTextureRect(sf::IntRect(180, 140, 60, 60));
	this->coin.setTextureRect(sf::IntRect(240, 140, 60, 60));

	this->heart.setPosition(940.f, 40.f);
	this->shard.setPosition(940.f, 100.f);
	this->skull.setPosition(940.f, 160.f);
	this->coin.setPosition(940.f, 260.f);
	this->key.setPosition(1090.f, 260.f);

	this->text[0].setFont(this->font);
	this->text[0].setCharacterSize(26);
	this->text[0].setFillColor(sf::Color::White);
	this->text[0].setString("level");
	this->text[0].setPosition(950.f, 570.f);

	this->text[1].setFont(this->font);
	this->text[1].setCharacterSize(26);
	this->text[1].setFillColor(sf::Color::White);
	this->text[1].setString("wave");
	this->text[1].setPosition(950.f, 620.f);

	this->text[2].setFont(this->font);
	this->text[2].setCharacterSize(26);
	this->text[2].setFillColor(sf::Color::White);
	this->text[2].setString("time");
	this->text[2].setPosition(950.f, 670.f);

}

void Gui::changeValues(int& coins, int& keys, int& level, int& wave, float& time)
{
	std::string cN = std::to_string(coins);
	this->number[0].setFont(this->font);
	this->number[0].setCharacterSize(30);
	this->number[0].setFillColor(sf::Color::White);
	this->number[0].setString(cN);
	this->number[0].setPosition(1020.f, 275.f);

	std::string kN = std::to_string(keys);
	this->number[1].setFont(this->font);
	this->number[1].setCharacterSize(30);
	this->number[1].setFillColor(sf::Color::White);
	this->number[1].setString(kN);
	this->number[1].setPosition(1170.f, 275.f);

	std::string lN = std::to_string(level);
	this->number[2].setFont(this->font);
	this->number[2].setCharacterSize(30);
	this->number[2].setFillColor(sf::Color::White);
	this->number[2].setString(lN);
	this->number[2].setPosition(1110.f, 570.f);

	std::string wN = std::to_string(wave);
	this->number[3].setFont(this->font);
	this->number[3].setCharacterSize(30);
	this->number[3].setFillColor(sf::Color::White);
	this->number[3].setString(wN);
	this->number[3].setPosition(1110.f, 620.f);

	std::string tN = std::to_string(time);
	this->number[4].setFont(this->font);
	this->number[4].setCharacterSize(30);
	this->number[4].setFillColor(sf::Color::White);
	this->number[4].setString(tN);
	this->number[4].setPosition(1110.f, 670.f);

	test.setSize(sf::Vector2f(60.f, 30.f));
	test.setFillColor(sf::Color(42, 30, 50));
	test.setPosition(1223.f, 670.f);
}

void Gui::render(sf::RenderTarget* target)
{
	target->draw(this->shape);

	target->draw(this->heart);
	target->draw(this->shard);
	target->draw(this->skull);
	target->draw(this->coin);
	target->draw(this->key);

	target->draw(this->number[0]);
	target->draw(this->number[1]);
	target->draw(this->number[2]);
	target->draw(this->number[3]);
	target->draw(this->number[4]);

	target->draw(this->text[0]);
	target->draw(this->text[1]);
	target->draw(this->text[2]);

	target->draw(this->test);
}
