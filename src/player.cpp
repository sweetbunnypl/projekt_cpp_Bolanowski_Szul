#include "player.h"

Player::Player()
{
    initTexture();
    initSprite();
}

void Player::initTexture()
{
    if (!playerTexture.loadFromFile("res/textures/spritesheet.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!copperArmor.loadFromFile("res/textures/armor_copper.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player armor_copper sheet!" << "\n";
    }

    if (!silverArmor.loadFromFile("res/textures/armor_silver.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player armor_silver sheet!" << "\n";
    }

    if (!goldenArmor.loadFromFile("res/textures/armor_golden.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!redSword.loadFromFile("res/textures/sword_red.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!blueSword.loadFromFile("res/textures/sword_blue.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!cyanSword.loadFromFile("res/textures/sword_cyan.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!copperRed.loadFromFile("res/textures/red_sword_copper.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!copperBlue.loadFromFile("res/textures/blue_sword_copper.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!copperCyan.loadFromFile("res/textures/cyan_sword_copper.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!silverRed.loadFromFile("res/textures/red_sword_silver.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!silverBlue.loadFromFile("res/textures/blue_sword_silver.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!silverCyan.loadFromFile("res/textures/cyan_sword_silver.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!goldenRed.loadFromFile("res/textures/red_sword_golden.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!goldenBlue.loadFromFile("res/textures/blue_sword_golden.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }

    if (!goldenCyan.loadFromFile("res/textures/cyan_sword_golden.png"))
    {
        std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
    }
}

void Player::initSprite()
{
    // getting texture size and dividing it to separate parts
    textureSize = playerTexture.getSize();
    textureSize.x /= 8;

    sprite.setTexture(playerTexture);

    // setting scale, bc it's a little bit too small 
    //this->playerSprite.scale(2.f, 2.f);

    // setting starting position
    sprite.setPosition(500.f, 500.f);
}

void Player::changePlayerEQ(bool& red, bool& blue, bool& cyan, bool& copper, bool& silver, bool& golden)
{
    if (red and !blue and !cyan and !copper and !silver and !golden)
    {
        sprite.setTexture(redSword);
    }

    if (!red and blue and !cyan and !copper and !silver and !golden)
    {
        sprite.setTexture(blueSword);
    }

    if (!red and !blue and cyan and !copper and !silver and !golden)
    {
        sprite.setTexture(cyanSword);
    }

    if (!red and !blue and !cyan and copper and !silver and !golden)
    {
        sprite.setTexture(copperArmor);
    }

    if (red and !blue and !cyan and !copper and silver and !golden)
    {
        sprite.setTexture(silverArmor);
    }

    if (red and !blue and !cyan and !copper and !silver and golden)
    {
        sprite.setTexture(goldenArmor);
    }

    if (red and !blue and !cyan and copper and !silver and !golden)
    {
        sprite.setTexture(copperRed);
    }

    if (red and !blue and !cyan and !copper and silver and !golden)
    {
        sprite.setTexture(silverRed);
    }

    if (red and !blue and !cyan and !copper and !silver and golden)
    {
        sprite.setTexture(goldenRed);
    }

    if (!red and blue and !cyan and copper and !silver and !golden)
    {
        sprite.setTexture(copperBlue);
    }

    if (!red and blue and !cyan and !copper and silver and !golden)
    {
        sprite.setTexture(silverBlue);
    }

    if (!red and blue and !cyan and !copper and !silver and golden)
    {
        sprite.setTexture(goldenBlue);
    }

    if (!red and !blue and cyan and copper and !silver and !golden)
    {
        sprite.setTexture(copperCyan);
    }

    if (!red and !blue and cyan and !copper and silver and !golden)
    {
        sprite.setTexture(silverCyan);
    }

    if (!red and !blue and cyan and !copper and !silver and golden)
    {
        sprite.setTexture(goldenCyan);
    }
}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}
