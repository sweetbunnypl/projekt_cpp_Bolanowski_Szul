#ifndef PLAYER_H
#define PLAYER_H

#include "libs.h"

class Player
{
private:
    sf::RectangleShape body;

    // never gets below zero
    unsigned int row;
    float playerSpeed;

    // true or false
    bool faceRight;

public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float playerSpeed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window);

};

#endif // PLAYER_H
