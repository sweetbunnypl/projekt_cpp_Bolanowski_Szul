#ifndef GAME_H
#define GAME_H

#include "libs.h"

class Game{
private:
    // variables
    sf::RenderWindow *window;
    sf::Event event;
    void initWindow();

public:
    // constructor and destructor
    Game();
    ~Game();

    // initialization of methods
    void updateSFMLevents();
    void update();
    void render();
    void run();

};

#endif // GAME_H
