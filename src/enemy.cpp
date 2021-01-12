#include "enemy.h"

Enemy::Enemy()
{
    health = 100;
    //TERROR
    terrorRadius = 200;
    terror.setRadius(terrorRadius);
    terror.setFillColor(sf::Color::Red);
    terror.setPosition(0, 0);
    //ATTACK
    attackRadius = 75;
    attack.setRadius(attackRadius);
    attack.setFillColor(sf::Color::Blue);
    attack.setPosition(0, 0);
    //SPRITE
    sprite.setPosition(0, 0);
    sprite.setFillColor(sf::Color::Green);
    size = sf::Vector2f(30.f, 30.f);
    sprite.setSize(size);
    speed = sf::Vector2f(2.f, 2.f);

    if (!this->font.loadFromFile("res/fonts/dogica.ttf"))
    {
        std::cout << "ERROR::PLAYER::Could not load the font file!" << "\n";
    }
    std::string strHealth = std::to_string(health);
    txtHealth.setFont(this->font);
    txtHealth.setCharacterSize(30);
    txtHealth.setFillColor(sf::Color::White);
    txtHealth.setString(strHealth);
}

Enemy::~Enemy()
{

}

void Enemy::create(sf::Vector2f position, sf::Vector2f scale, sf::Vector2f textureScale)
{
    //this->sprite.setTexture(&texture);
    this->initTexture();
    this->initSprite();
    enemySprite.setPosition(position);
    enemySprite.setScale(textureScale);
    enemySprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
    terror.setPosition(sf::Vector2f(position.x+(enemySprite.getGlobalBounds().width/2)-terrorRadius, position.y+(enemySprite.getGlobalBounds().height/2)-terrorRadius));
    terror.setScale(scale);
    attack.setPosition(sf::Vector2f(position.x+(enemySprite.getGlobalBounds().width/2)-attackRadius, position.y+(enemySprite.getGlobalBounds().height/2)-attackRadius));
    attack.setScale(scale);

    txtHealth.setPosition(position.x+(enemySprite.getGlobalBounds().width/2)-txtHealth.getGlobalBounds().width/2, position.y+(enemySprite.getGlobalBounds().width/2)-(txtHealth.getGlobalBounds().width/2)-40);
    //this->enemies[i].enemySprite.setTextureRect(sf::IntRect(0, enemies[i].textureSize.x, enemies[i].textureSize.x, enemies[i].textureSize.y));
}

void Enemy::render(sf::RenderTarget* target)
{
    target->draw(this->enemySprite);
    target->draw(this->txtHealth);
}

void Enemy::renderRadius(sf::RenderTarget* target)
{
    target->draw(this->terror);
    target->draw(this->attack);
}

void Enemy::initTexture()
{
    if (!this->enemyTexture.loadFromFile("res/textures/frog.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }
}

void Enemy::initSprite()
{
    // getting texture size and dividing it to separate parts
    this->textureSize = enemyTexture.getSize();
    textureSize.x /= 6;

    this->enemySprite.setTexture(this->enemyTexture);

    // setting scale, bc it's a little bit too small 
    //this->playerSprite.scale(2.f, 2.f);

    // setting starting position
    //this->enemySprite.setPosition(0.f, 0.f);
}

void Enemy::updateHealth(int hp)
{
    std::string strHealth = std::to_string(hp);
    txtHealth.setFont(this->font);
    txtHealth.setCharacterSize(30);
    txtHealth.setFillColor(sf::Color::White);
    txtHealth.setString(strHealth);
    //txtHealth.setPosition(position.x, position.y - 50);
}
