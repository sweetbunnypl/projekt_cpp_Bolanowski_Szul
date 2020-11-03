#ifndef MENU_H
#define MENU_H

#define MAX_NUMBER_OF_ITEMS 4

#include "libs.h"
//#include "game.h"

class Menu
//    :public Game
{
public:
    // constructor and destructor
    Menu(float width_window, float height_window);
    ~Menu();
    // functions only in menu
    void MoveUp();
    void MoveDown();
    void drawMenu(sf::RenderWindow* window);
    int GetPressedItem() { return MenuIndex; }
    //int GetPressedItem() { return MenuIndex; }

    //functions changed from Game
    //void render(sf::RenderWindow* window);
    //void run(sf::RenderWindow* window);
    //void updateSFMLevents(sf::RenderWindow* window);
    //void update(sf::RenderWindow* window);

    //variables
    int MenuIndex = 0;
    sf::Text text[MAX_NUMBER_OF_ITEMS];
    sf::Font font;
};

#endif // MENU_H