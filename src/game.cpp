#include "game.h"

Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	// all variables associated with window
	std::string title = "game project";
	unsigned windowWidth = 1280;
	unsigned windowHeight = 720;
	sf::VideoMode windowBunds(windowWidth, windowHeight);
	this->window = new sf::RenderWindow(windowBunds, title, sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(30);
}

void Game::updateDeltaTime()
{
	// this->elapsedTime = this->dtClock.getElapsedTime().asSeconds();

	// updates the delta time variable with the time it takes to update and render one frame;
	this->deltaTime = this->dtClock.restart().asSeconds();

	// clears the console
	system("cls");
	std::cout << this->deltaTime << '\n';
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	// update classes below

	this->player.update(deltaTime);
	this->borders();
	this->collision();
}

void Game::render()
{
	this->window->clear();

	// render (draw) objects here
	this->map.renderMap(this->window);
	this->map.renderObject(this->window);
	this->player.render(this->window);

	// 

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}

void Game::borders()
{
	std::cout << "X: " << player.playerSprite.getPosition().x << '\n';
	std::cout << "Y: " << player.playerSprite.getPosition().y << '\n';

	if (player.playerSprite.getPosition().x <= 0)
	{
		std::cout << "jeblo z lewej" << '\n';
		player.playerSprite.setPosition(0.f, player.playerSprite.getPosition().y);
	}

	if (player.playerSprite.getPosition().y <= 0)
	{
		std::cout << "jeblo z gory" << '\n';
		player.playerSprite.setPosition(player.playerSprite.getPosition().x, 0);
	}

	if (player.playerSprite.getPosition().x + player.playerSprite.getGlobalBounds().width >= window->getSize().x)
	{
		std::cout << "jeblo z prawej" << '\n';
		player.playerSprite.setPosition(window->getSize().x - player.playerSprite.getGlobalBounds().width, player.playerSprite.getPosition().y);
	}

	if (player.playerSprite.getPosition().y + player.playerSprite.getGlobalBounds().height >= window->getSize().y)
	{
		std::cout << "jeblo z dolu" << '\n';
		player.playerSprite.setPosition(player.playerSprite.getPosition().x, window->getSize().y - player.playerSprite.getGlobalBounds().height);
	}
}

void Game::collision()
{
	if (this->map.object.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()))
	{
		std::cout << "MPK znowu jeblo" << '\n';
	}
}



