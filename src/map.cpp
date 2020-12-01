#include "map.h"

Map::Map()
{
    this->initMap();
    this->initTestObject();
}

Map::~Map()
{
}

void Map::initMap()
{
    if (!this->mapBackgroundTexture.loadFromFile("res/textures/mapBackground.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    this->mapBackground.setTexture(this->mapBackgroundTexture);
}

void Map::initTestObject()
{
    sf::Vector2f objectSize = sf::Vector2f(100.f, 100.f);
    sf::Vector2f objectPosition = sf::Vector2f(500.f, 500.f);

    this->object.setFillColor(sf::Color::Black);
    this->object.setSize(objectSize);
    this->object.setPosition(objectPosition);
}

void Map::renderMap(sf::RenderTarget* target)
{
    target->draw(this->mapBackground);
}

void Map::renderObject(sf::RenderTarget* target)
{
    target->draw(this->object);
}
