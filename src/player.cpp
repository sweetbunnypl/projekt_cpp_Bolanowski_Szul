#include "player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float playerSpeed)
{
    this->playerSpeed = playerSpeed;
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(100.0f, 100.0f));
    body.setPosition(206.0f, 206.0f);
    body.setTexture(texture);

}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movement.x -= playerSpeed * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movement.x += playerSpeed * deltaTime;
    }

    if (movement.x == 0.0f)
    {
        row = 0;
    }

    else
    {
        row =1;

        if (movement.x > 0.0f)
        {
            faceRight = true;
        }

        else
        {
            faceRight = false;
        }
    }

}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}
