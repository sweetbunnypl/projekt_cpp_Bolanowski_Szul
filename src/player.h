#ifndef PLAYER_H
#define PLAYER_H

#include "libs.h"

class Player
{
private:
    sf::Vector2f coordinates;
    sf::Sprite player_texture;
    int player_health;
    int points;

public:
    Player();
    ~Player();

    int movement(sf::Vector2f coordinates);
    int health(int player_health);
    int pointsSystem(int points);
    void player_death();

};

#endif // PLAYER_H
