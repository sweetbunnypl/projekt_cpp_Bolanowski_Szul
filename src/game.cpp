#include "game.h"

// initialization of window
void Game::initWindow(){

    std::string title = "GAME";

    sf::VideoMode window_bunds(width_window, height_window);

    int fps = 60;

    this->window = new sf::RenderWindow(window_bunds, title);
    this->window->setFramerateLimit(fps);
}
void Game::initMenu() {
	this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);
}

// SFMLevents -> all events like closing window etc.
void Game::updateSFMLevents(){
    while ( this->window->pollEvent(this->event))
    {
        if ( this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
        
    }
}

// update state of game
void Game::update(){
    this->updateSFMLevents();
}

// render objects constantly on the screen
void Game::render(){
    this->window->clear();
    //code
    this->window->display();
}

// update + render
void Game::run(){
    while ( this->window->isOpen())
    {
        this->update();
        this->render();
    }
}

// constructor
Game::Game(){
    this->initWindow();
	this->initMenu();
}

// destructor
Game::~Game(){
    delete this->window;
}

void Game::updateSFMLeventsMenu() {
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
			// key pressed
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				menu->MoveUp();
				printf("m_u");
				break;

			case sf::Keyboard::Down:
				menu->MoveDown();
				printf("m_d");
				break;

			case sf::Keyboard::Return:
				switch (menu->GetPressedItem())
				{
				case 0:
					printf("Ktos nacisnal Play");
					break;
				case 1:
					printf("Ktos nacisnal Options");
					break;
				case 2:
					printf("Ktos nacisnal Creators");
					break;
				case 3:
					this->window->close();
				default:
					break;
				}
			}
			break;
			// window closed
		case sf::Event::Closed:
			this->window->close();
			break;
			// we don't process other types of events
		default:
			break;
		}
	}
}

void Game::renderMenu() {
	this->window->clear();
	//this->window->draw(this->menu);
	this->menu->drawMenu(this->window);
	this->window->display();
}

void Game::runMenu() {
	while (this->window->isOpen()) {
		this->updateSFMLeventsMenu();
		this->renderMenu();
	}
}
