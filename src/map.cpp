#include "map.h"

Map::Map()
{
    //this->initMap();
    this->initObjects();
}

Map::~Map()
{
}

//void Map::initMap()
//{
//    if (!this->mapBackgroundTexture.loadFromFile("res/textures/mapBackground.png"))
//    {
//        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
//    }
//
//    this->mapBackground.setTexture(this->mapBackgroundTexture);
//}

void Map::initObjects()
{
    if (!this->tilesTexture.loadFromFile("res/textures/tiles.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    sf::Vector2f objectPosition = sf::Vector2f(500.f, 500.f);

    // getting texture size and dividing it to separate parts
    sf::Vector2u textureSize = tilesTexture.getSize();
    textureSize.x /= 3;
    textureSize.y /= 3;

    for (int i = 0; i <= 62; i++)
    {
        this->object[i].setTexture(this->tilesTexture);
    }

    // TOP MAIN
    mnoznik = 0;
    for (int i = 0; i <= 17; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
        this->object[i].setPosition({ -8.f - (16.f * mnoznik) + (textureSize.x / 3) * 16 * mnoznik, 0.f });
    }

    // BOTTOM MAIN
    mnoznik = 0;
    for (int i = 18; i <= 35; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
        this->object[i].setPosition({ -8.f - (16.f * mnoznik) + (textureSize.x / 3) * 16 * mnoznik, 659.f });
    }

    // LEFT MAIN
    mnoznik = 0;
    for (int i = 36; i <= 46; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
        this->object[i].setPosition({ -8.f, 0.f - (16.f * mnoznik) + (textureSize.y / 3) * 16 * mnoznik });
    }

    // RIGHT MAIN
    mnoznik = 0;
    for (int i = 47; i <= 58; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
        this->object[i].setPosition({ 1270.f, 0.f - (16.f * mnoznik) + (textureSize.y / 3) * 16 * mnoznik });
        this->object[i].setScale(-1.f, 1.f);
    }

    mnoznik = 0;

    // CORNERS
    this->object[59].setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 0, textureSize.x, textureSize.y));
    this->object[59].setPosition({ -8.f, 0 });
    this->object[59].setScale(4.f, 4.f);

    this->object[60].setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
    this->object[60].setPosition({ -8.f, 659.f });
    this->object[60].setScale(4.f, 4.f);

    this->object[61].setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 0, textureSize.x, textureSize.y));
    this->object[61].setPosition({ 1270.f, 0.f });
    this->object[61].setScale(-4.f, 4.f);

    this->object[62].setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
    this->object[62].setPosition({ 1270.f, 659.f });
    this->object[62].setScale(-4.f, 4.f);

    for (int i = 0; i <= 58; i++)
    {
        this->object[i].scale(4.f, 4.f);
    }
}

void Map::renderMap(sf::RenderTarget* target)
{
    //target->draw(this->mapBackground);
}

void Map::renderObject(sf::RenderTarget* target)
{
    for (int i = 0; i <= 62; i++)
    {
        target->draw(this->object[i]);
    }
}
