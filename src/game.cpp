#include "game.h"

// initialization of window
void Game::initWindow(){
    unsigned width_window = 1280;
    unsigned height_window = 720;

    std::string title = "GAME";

    sf::VideoMode window_bunds(width_window, height_window);

    int fps = 60;

    this->window = new sf::RenderWindow(window_bunds, title);
    this->window->setFramerateLimit(fps);
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
}

// destructor
Game::~Game(){
    delete this->window;
}
