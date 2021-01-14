#include "player.h"

Player::Player()
{
    initTexture();
    initSprite();
}

void Player::initTexture()
{
    if (!playerTexture.loadFromFile("res/textures/spritesheet.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }
}

void Player::initSprite()
{
    // getting texture size and dividing it to separate parts
    textureSize = playerTexture.getSize();
    textureSize.x /= 8;

    sprite.setTexture(playerTexture);

    // setting scale, bc it's a little bit too small 
    //this->playerSprite.scale(2.f, 2.f);

    // setting starting position
    sprite.setPosition(500.f, 500.f);
}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}
