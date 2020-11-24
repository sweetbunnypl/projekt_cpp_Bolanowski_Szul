#include "player.h"

Player::Player()
{
    this->movementSpeed = 200.f;
    this->initTexture();
    this->initSprite();
}

Player::~Player()
{

}

void Player::initTexture()
{
    if (!this->playerTexture.loadFromFile("res/textures/playerTexture.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }
}

void Player::initSprite()
{
    this->playerSprite.setTexture(this->playerTexture);
    this->playerSprite.scale(3.f, 3.f);
}

void Player::updateMovement(const float& deltaTime, const float x, const float y)
{
    this->playerSprite.move(x * this->movementSpeed * deltaTime, y * this->movementSpeed * deltaTime);
}

void Player::update(const float& deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        // move up
        this->updateMovement(deltaTime, 0.f, -1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // move down
        this->updateMovement(deltaTime, 0.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        // move left
        this->updateMovement(deltaTime, -1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        // move right
        this->updateMovement(deltaTime, 1.f, 0.f);
    }

}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->playerSprite);
}
