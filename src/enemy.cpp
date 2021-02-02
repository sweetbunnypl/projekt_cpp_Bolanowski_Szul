#include "enemy.h"

Enemy::Enemy()
{
    health = 1;
    //TERROR
    terrorRadius = 300;
    terror.setRadius(terrorRadius);
    terror.setFillColor(sf::Color::Red);
    terror.setPosition(0, 0);
    //ATTACK
    attackRadius = 100;
    attack.setRadius(attackRadius);
    attack.setFillColor(sf::Color::Blue);
    attack.setPosition(0, 0);
    //SPRITE
    sprite.setPosition(0, 0);
    //sprite.setFillColor(sf::Color::Green);
    //size = sf::Vector2f(30.f, 30.f);
    //sprite.setSize(size);
    speed = sf::Vector2f(2.f, 2.f);

    if (!font.loadFromFile("res/fonts/dogica.ttf"))
    {
        std::cout << "ERROR::PLAYER::Could not load the font file!" << "\n";
    }
}

Enemy::~Enemy()
{
}

void Enemy::create(sf::Vector2f position, sf::Vector2f scale, sf::Vector2f textureScale, int enemyHealth)
{
    this->initTexture();
    this->initSprite();
    sprite.setPosition(position);
    sprite.setScale(textureScale);
    sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
    terror.setPosition(sf::Vector2f(position.x+(sprite.getGlobalBounds().width/2)-terrorRadius, position.y+(sprite.getGlobalBounds().height/2)-terrorRadius));
    terror.setScale(scale);
    attack.setPosition(sf::Vector2f(position.x+(sprite.getGlobalBounds().width/2)-attackRadius, position.y+(sprite.getGlobalBounds().height/2)-attackRadius));
    attack.setScale(scale);
    health = enemyHealth;
    updateHealth(health);
    txtHealth.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - txtHealth.getGlobalBounds().width / 2, sprite.getPosition().y + (sprite.getGlobalBounds().height / 2) - (txtHealth.getGlobalBounds().height / 2) - 50);
}

void Enemy::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
    target->draw(this->txtHealth);
}

void Enemy::renderRadius(sf::RenderTarget* target)
{
    target->draw(this->terror);
    target->draw(this->attack);
}

void Enemy::initTexture()
{
    // tu musisz zmienic nazwe png'a

    if (!texture.loadFromFile("res/textures/frogs.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }
}

void Enemy::initSprite()
{
    // getting texture size and dividing it to separate parts
    sprite.setTextureRect(sf::IntRect(0, 0, 96, 64));
    //textureSize = texture.getSize();
    //textureSize.x /= 14;

    sprite.setTexture(texture);

    // setting scale, bc it's a little bit too small 
    //this->playerSprite.scale(2.f, 2.f);

    // setting starting position
    //this->enemySprite.setPosition(0.f, 0.f);
}

void Enemy::updateHealth(int hp)
{
    std::string strHealth = std::to_string(hp);
    txtHealth.setFont(font);
    txtHealth.setCharacterSize(30);
    txtHealth.setFillColor(sf::Color::White);
    txtHealth.setString(strHealth);
}
