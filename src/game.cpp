#include "game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// initialization of window
void Game::initWindow(){
    unsigned widthWindow = 1280;
    unsigned heightWindow = 720;

    std::string title = "CHAOS";

    sf::VideoMode windowBunds(widthWindow, heightWindow);

    int fps = 30;

    this->window = new sf::RenderWindow(windowBunds, title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(fps);
}

// handle SFML events -> all events like closing window etc.
void Game::updateSFMLevents(){
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }
    }
}

void::Game::updatePlayerMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // move bottom
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        // move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        // move right
    }
}

// update state of game
void Game::update(){
    this->updateSFMLevents();

    // mouse position
    // relative to the window
    std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
}

// render objects constantly on the screen
void Game::render(){
    this->window->clear(sf::Color::White);
    //code
    this->player.render((this->window));
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
