#pragma once
#include "libs.h"

//class Player
//{
//private:
//    sf::RectangleShape body;

//    // never gets below zero
//    unsigned int row;
//    float playerSpeed;

//    // true or false
//    bool faceRight;

//public:
//    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float playerSpeed);
//    ~Player();

//    void Update(float deltaTime);
//    void Draw(sf::RenderWindow &window);

//};

class Player
{
<<<<<<< HEAD
public:
	Player();
	~Player();

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Vector2u textureSize;

	thor::FrameAnimation playerDown;
	thor::FrameAnimation playerLeft;
	thor::FrameAnimation playerRight;
	thor::FrameAnimation playerUp;

	thor::Animator<sf::Sprite, std::string> playerAnimation;

	float movementSpeed;

	void initTexture();
	void initSprite();
	//void updateMovement(const float& deltaTime, const float x, const float y);

	//void update(const float& deltaTime);
	void render(sf::RenderTarget* target);
=======
private:
    sf::Texture playerTexture;
    sf::RectangleShape playerShape;
    sf::Sprite playerSprite;
    sf::Vector2u textureSize;

    unsigned int row;
    float playerSpeed;
    bool faceRight;

//    void initVariables();
//    void initShape();

public:
    Player();
    virtual ~Player();

    void initTexture();
    void initSprite();
    void updateMovement();
    void update();
    void render(sf::RenderTarget* target);
>>>>>>> 744555fb668c93e060173744eb3ac832c8b02f5b

};

