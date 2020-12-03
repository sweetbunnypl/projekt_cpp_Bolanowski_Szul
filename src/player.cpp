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

    playerDown.addFrame(1.f, sf::IntRect(0, 0, 32, 32));
    playerDown.addFrame(1.f, sf::IntRect(32, 0, 32, 32));
    playerDown.addFrame(1.f, sf::IntRect(64, 0, 32, 32));

    playerLeft.addFrame(1.f, sf::IntRect(0, 32, 32, 32));
    playerLeft.addFrame(1.f, sf::IntRect(32, 32, 32, 32));
    playerLeft.addFrame(1.f, sf::IntRect(64, 32, 32, 32));

    playerRight.addFrame(1.f, sf::IntRect(0, 64, 32, 32));
    playerRight.addFrame(1.f, sf::IntRect(32, 64, 32, 32));
    playerRight.addFrame(1.f, sf::IntRect(64, 64, 32, 32));

    playerUp.addFrame(1.f, sf::IntRect(0, 96, 32, 32));
    playerUp.addFrame(1.f, sf::IntRect(32, 96, 32, 32));
    playerUp.addFrame(1.f, sf::IntRect(64, 96, 32, 32));

    playerAnimation.addAnimation("down", playerDown, sf::seconds(1.8f));
    playerAnimation.addAnimation("left", playerLeft, sf::seconds(1.8f));
    playerAnimation.addAnimation("right", playerRight, sf::seconds(1.8f));
    playerAnimation.addAnimation("up", playerUp, sf::seconds(1.8f));
}

void Player::initSprite()
{
    // getting texture size and dividing it to separate parts
    this->textureSize = playerTexture.getSize();
    textureSize.x /= 3;
    textureSize.y /= 4;
    this->playerSprite.setTexture(this->playerTexture);

    // applying first part of the texture to the sprite
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));

    // setting scale, bc it's a little bit too small 
    this->playerSprite.scale(3.f, 3.f);
}

// MOVEMENT SHOULD BE HANLED IN GAME
//void Player::updateMovement(const float& deltaTime, const float x, const float y)
//{
//    this->playerSprite.move(x * this->movementSpeed * deltaTime, y * this->movementSpeed * deltaTime);
//}

//void Player::update(const float& deltaTime)
//{
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
//    {
//        // move up
//        this->updateMovement(deltaTime, 0.f, -1.f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
//    {
//        // move down
//        this->updateMovement(deltaTime, 0.f, 1.f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
//    {
//        // move left
//        this->updateMovement(deltaTime, -1.f, 0.f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//    {
//        // move right
//        this->updateMovement(deltaTime, 1.f, 0.f);
//    }
//
//}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->playerSprite);
}
