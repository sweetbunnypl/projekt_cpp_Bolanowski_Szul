#include "object.h"

Object::Object()
{
    if (!this->texture.loadFromFile("res/textures/gui.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the gui sheet!" << "\n";
    }
}

void Object::create(sf::Vector2f position, sf::Vector2f scale)
{
    sprite.setPosition(position);
    sprite.setScale(scale);
}

void Object::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}

Heart::Heart()
{
    sprite.setTextureRect(sf::IntRect(0, 140, 60, 60));
    sprite.setTexture(texture);
}

Key::Key()
{
    sprite.setTextureRect(sf::IntRect(180, 140, 60, 60));
    sprite.setTexture(texture);
}

Shard::Shard()
{
    sprite.setTextureRect(sf::IntRect(60, 140, 60, 60));
    sprite.setTexture(texture);
}

Coin::Coin()
{
    sprite.setTextureRect(sf::IntRect(240, 140, 60, 60));
    sprite.setTexture(texture);
}

Armorer::Armorer()
{
    sprite.setTexture(texture);
}

Bonfire::Bonfire()
{
    if (!texture.loadFromFile("res/textures/objects.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTexture(texture);
}
