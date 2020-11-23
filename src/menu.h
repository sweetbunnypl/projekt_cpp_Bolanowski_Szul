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
    void getButtons(int i);
    void MoveDown();
    void drawMenu(sf::RenderWindow* window);
    int GetPressedItem() { return MenuIndex; }
    bool MAIN_MENU;
    bool OPTIONS;
    bool CREATORS;
    bool HELP;
    void renderButtons(sf::RenderWindow* window);
    void renderCreators();
    //int GetPressedItem() { return MenuIndex; }

    //functions changed from Game
    //void render(sf::RenderWindow* window);
    //void run(sf::RenderWindow* window);
    //void updateSFMLevents(sf::RenderWindow* window);
    //void update(sf::RenderWindow* window);

    //variables
    int MenuIndex = 0;
    sf::Text text[MAX_NUMBER_OF_ITEMS];
    sf::RectangleShape rectangle;
    sf::Font font;
    //background
    //sf::Texture bcg;
    //sf::Sprite bcg_s;
    sf::Texture gif_bcg[7];
    sf::Sprite gif_bcg_s[7];

    std::string main_menu_txt[4] = { "PLAY", "CREATORS", "HELP", "EXIT" };
    std::string main_menu_txt2[4] = { "- PLAY -", "- CREATORS -", "- HELP -", "- EXIT -" };
    std::string creators_menu_txt[4] = { "PLAY", "CREATORS", "HELP", "EXIT" };
    std::string creators_menu_txt2[4] = { "- PLAY -", "- CREATORS -", "- HELP -", "- EXIT -" };
    std::string help_menu_txt[4] = { "PLAY", "CREATORS", "HELP", "EXIT" };
    std::string help_menu_txt2[4] = { "- PLAY -", "- CREATORS -", "- HELP -", "- EXIT -" };

    int pause = 0;
};

#endif // MENU_H