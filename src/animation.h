#ifndef ANIMATION_H
#define ANIMATION_H

#include "libs.h"


class Animation
{
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

public:
    Animation();
    ~Animation();

    sf::IntRect uvRect;

    void update(int row, float deltaTime);

};

#endif // ANIMATION_H
