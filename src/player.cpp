#include "player.h"

void::Player::initTexture()
{
    if (!this->playerTexture.loadFromFile("res/textures/playertexture.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }
}

void::Player::initSprite()
{
    this->playerSprite.setTexture(this->playerTexture);
}


Player::Player()
{

//    this->playerShape.setFillColor(sf::Color::Blue);
//    this->playerShape.setSize(sf::Vector2f(100.f, 100.f));
//    this->playerTexture.loadFromFile("res/textures/kotek.png");
//    this->playerSprite.setTexture(playerTexture);
//    this->playerSprite.setScale(0.15, 0.15);

    this->initTexture();
    this->initSprite();
    this->textureSize = playerTexture.getSize();
    textureSize.x /= 3;
    textureSize.y /= 4;

    // 1.1
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
    // 1.2
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 0, textureSize.x, textureSize.y));
    // 1.3
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 0, textureSize.x, textureSize.y));
    // 2.
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
    // 2.2
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
    // 2.3
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 1, textureSize.x, textureSize.y));
    // 3.1
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 2, textureSize.x, textureSize.y));
    // 3.2
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 2, textureSize.x, textureSize.y));
    // 3.3
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 2, textureSize.x, textureSize.y));
    // 4.1
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 3, textureSize.x, textureSize.y));
    // 4.2
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 3, textureSize.x, textureSize.y));
    // 4.3
    this->playerSprite.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 3, textureSize.x, textureSize.y));
}

Player::~Player()
{

}

void::Player::updateMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        // move top
        this->playerSprite.move(0.f,-5.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // move bottom
        this->playerSprite.move(0.f,5.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        // move left
        this->playerSprite.move(-5.f,0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        // move right
        this->playerSprite.move(5.f,0.f);
    }
}

void::Player::update()
{
    this->updateMovement();
}

void::Player::render(sf::RenderTarget * target)
{
    target->draw(this->playerSprite);
}




//Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float playerSpeed)
//{
//    this->playerSpeed = playerSpeed;
//    row = 0;
//    faceRight = true;

//    body.setSize(sf::Vector2f(100.0f, 100.0f));
//    body.setPosition(206.0f, 206.0f);
//    body.setTexture(texture);

//}

//Player::~Player()
//{

//}

//void Player::Update(float deltaTime)
//{
//    sf::Vector2f movement(0.0f, 0.0f);

//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//    {
//        movement.x -= playerSpeed * deltaTime;
//    }

//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//    {
//        movement.x += playerSpeed * deltaTime;
//    }

//    if (movement.x == 0.0f)
//    {
//        row = 0;
//    }

//    else
//    {
//        row =1;

//        if (movement.x > 0.0f)
//        {
//            faceRight = true;
//        }

//        else
//        {
//            faceRight = false;
//        }
//    }

//}

//void Player::Draw(sf::RenderWindow &window)
//{
//    window.draw(body);
//}

