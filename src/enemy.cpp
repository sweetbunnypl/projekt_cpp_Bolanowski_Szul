#include "enemy.h"

Enemy::Enemy()
{
    terror_r = 250;
    sprite.setSize(sf::Vector2f(50, 50));
    sprite.setFillColor(sf::Color::Black);
    sprite.setPosition(0, 0);

    terror.setRadius(terror_r);
    terror.setFillColor(sf::Color::Red);
    terror.setPosition(0, 0);
    speed = sf::Vector2f(2.f, 2.f);
}

Enemy::~Enemy()
{

}

void Enemy::create(sf::Vector2f position, sf::Vector2f scale)
{
    sprite.setPosition(position);
    sprite.setScale(scale);
    terror.setPosition(sf::Vector2f(position.x+(sprite.getSize().x/2)-terror_r, position.y+(sprite.getSize().y/2)-terror_r));
    terror.setScale(scale);
}

void Enemy::render(sf::RenderTarget* target)
{
    //target->draw(this->terror);
    target->draw(this->sprite);
}