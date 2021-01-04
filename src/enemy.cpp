#include "enemy.h"

Enemy::Enemy()
{
    terrorRadius = 250;
    sprite.setPosition(0, 0);
    sprite.setFillColor(sf::Color::Green);
    size = sf::Vector2f(30.f, 30s.f);
    sprite.setSize(size);
    terror.setRadius(terrorRadius);
    terror.setFillColor(sf::Color::Red);
    terror.setPosition(0, 0);
    speed = sf::Vector2f(2.f, 2.f);
}

Enemy::~Enemy()
{

}

void Enemy::create(sf::Vector2f position, sf::Vector2f scale)
{
    this->sprite.setTexture(&texture);
    sprite.setPosition(position);
    terror.setPosition(sf::Vector2f(position.x+(sprite.getSize().x/2)-terrorRadius, position.y+(sprite.getSize().y/2)-terrorRadius));
    terror.setScale(scale);
}

void Enemy::render(sf::RenderTarget* target)
{
    //target->draw(this->terror);
    target->draw(this->sprite);
}
