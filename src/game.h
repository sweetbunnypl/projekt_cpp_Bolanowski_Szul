#ifndef GAME_H
#define GAME_H

#include "libs.h"
#include "menu.h"

class Game{
public:
    // constructor and destructor
    Game();
    ~Game();
    // initialization of methods
    void updateSFMLevents();
    void update();
    void render();
    void run();
    void initMenu();
    void renderMenu();
    void runMenu();
    void updateSFMLeventsMenu();
    void drawMenu();
    // variables
    unsigned width_window = width_window_test; //1280;
    unsigned height_window = height_window_test; //720;
    sf::Font font;
    sf::RenderWindow *window;
    Menu* menu;
    sf::Event event;
    void initWindow();
};

#endif // GAME_H
