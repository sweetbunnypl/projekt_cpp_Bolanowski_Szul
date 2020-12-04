#include "map.h"

Map::Map()
{
    this->initMap();
    this->initObjects();
}

Map::~Map()
{
}

void Map::initMap()
{
    if (!this->mapBackgroundTexture.loadFromFile("res/textures/floor.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    this->mapBackground.setTexture(this->mapBackgroundTexture);
    this->mapBackground.setPosition(56.f, 62.f);
    this->mapBackground.setScale(2.02f, 1.875f);
}

void Map::renderMap(sf::RenderTarget* target)
{
    target->draw(this->mapBackground);
}

void Map::initObjects()
{

    if (!this->tilesTexture.loadFromFile("res/textures/tiles.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    // getting texture size and dividing it to separate parts
    sf::Vector2u textureSize = tilesTexture.getSize();
    textureSize.x /= 3;
    textureSize.y /= 3;

    for (int i = 0; i <= 52; i++)
    {
        this->object[i].setTexture(this->tilesTexture);
    }

    // TOP MAIN
    mnoznik = 0;
    for (int i = 0; i <= 12; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
        this->object[i].setPosition({ -8.f - (16.f * mnoznik) + (textureSize.x / 3) * 16 * mnoznik, 0.f });
    }

    // BOTTOM MAIN
    mnoznik = 0;
    for (int i = 13; i <= 25; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
        this->object[i].setPosition({ -8.f - (16.f * mnoznik) + (textureSize.x / 3) * 16 * mnoznik, 659.f });
    }

    // LEFT MAIN
    mnoznik = 0;
    for (int i = 26; i <= 36; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
        this->object[i].setPosition({ -8.f, 0.f - (16.f * mnoznik) + (textureSize.y / 3) * 16 * mnoznik });
    }

    // RIGHT MAIN
    mnoznik = 0;
    for (int i = 37; i <= 48; i++)
    {
        mnoznik += 1;
        this->object[i].setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 1, textureSize.x, textureSize.y));
        this->object[i].setPosition({ 951.f, 0.f - (16.f * mnoznik) + (textureSize.y / 3) * 16 * mnoznik });
        this->object[i].setScale(-1.f, 1.f);
    }

    mnoznik = 0;

    // CORNERS
    this->object[49].setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 0, textureSize.x, textureSize.y));
    this->object[49].setPosition({ -8.f, 0 });
    this->object[49].setScale(4.f, 4.f);

    this->object[50].setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
    this->object[50].setPosition({ -8.f, 659.f });
    this->object[50].setScale(4.f, 4.f);

    this->object[51].setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 0, textureSize.x, textureSize.y));
    this->object[51].setPosition({ 951.f, 0.f });
    this->object[51].setScale(-4.f, 4.f);

    this->object[52].setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 1, textureSize.x, textureSize.y));
    this->object[52].setPosition({ 951.f, 659.f });
    this->object[52].setScale(-4.f, 4.f);

    for (int i = 0; i <= 48; i++)
    {
        this->object[i].scale(4.f, 4.f);
    }
}

void Map::renderObject(sf::RenderTarget* target)
{
    for (int i = 0; i <= 52; i++)
    {
        target->draw(this->object[i]);
    }
}
