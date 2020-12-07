#include "player.h"

Player::Player()
{
    this->playerHealth = 100.f;

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
    // getting texture size and dividing it to separate parts
    this->textureSize = playerTexture.getSize();
    textureSize.x /= 3;
    textureSize.y /= 4;
    this->playerSprite.setTexture(this->playerTexture);

    // setting scale, bc it's a little bit too small 
    this->playerSprite.scale(2.f, 2.f);

    // setting starting position
    this->playerSprite.setPosition(500.f, 500.f);
}

void Player::render(sf::RenderTarget* target)
{

    target->draw(this->playerSprite);
}
