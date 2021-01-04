#include "object.h"

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
    if (!texture.loadFromFile("res/textures/heart.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTexture(texture);
}



Key::Key()
{
    if (!texture.loadFromFile("res/textures/key.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTexture(texture);
}

Shard::Shard()
{
    if (!texture.loadFromFile("res/textures/levelshards.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTexture(texture);
}

Coin::Coin()
{
    if (!texture.loadFromFile("res/textures/coin.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTexture(texture);
}

Armorer::Armorer()
{
    if (!texture.loadFromFile("res/textures/armorer.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTexture(texture);
}
