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
    if (!texture.loadFromFile("res/textures/key.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTexture(texture);
}

Shard::Shard()
{
    //sprite.setTextureRect(sf::IntRect(60, 140, 60, 60));

    if (!texture.loadFromFile("res/textures/levelshards.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTextureRect(sf::IntRect(0, 0, 12, 30));
    sprite.setTexture(texture);
}

Coin::Coin()
{
    if (!texture.loadFromFile("res/textures/coin.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sprite.setTextureRect(sf::IntRect(0, 0, 12, 17));
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
