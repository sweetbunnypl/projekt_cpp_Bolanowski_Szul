#include "animation.h"

Animation::Animation()
{
    sf::Texture* playerTexture;
    sf::Vector2u imageCount;
    float switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width  = playerTexture->getSize().x / float(imageCount.x);
    uvRect.height = playerTexture->getSize().y / float(imageCount.y);

}

Animation::~Animation()
{

}

void Animation::update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}
