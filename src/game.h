#pragma once
#include "player.h"
#include "map.h"
#include "libs.h"
#include "player.h"

#define MAX_NUMBER_OF_ITEMS 4

class Game
{
private:
<<<<<<< HEAD
	// GAME VARIABLES
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock clock;
	sf::Time deltaTime;
	
	// CREATING OBJECTS WHEN WINDOW IS READY

	// map object
	Map map;

	// player object
	Player player;

	// end-screen object (etc.)

	// init.
	void initWindow();
=======
    // variables
    sf::RenderWindow *window;
    sf::Event event;
    Player player;

    void initWindow();
>>>>>>> 744555fb668c93e060173744eb3ac832c8b02f5b

public:
	Game();
	~Game();

	// WINDOW VARIABLES
	unsigned windowWidth = 1280;
	unsigned windowHeight = 720;

	// GAME STATE VARIABLES
	bool playingState;
	bool inMenuState;

	// MENU VARIABLES
	sf::Music menu_music;
	sf::SoundBuffer change_buffer;
	sf::Sound change_sound;
	sf::SoundBuffer enter_buffer;
	sf::Sound enter_sound;
	sf::SoundBuffer quit_buffer;
	sf::Sound quit_sound;

	int MenuIndex = 0;
	int pause = 0;
	bool MAIN_MENU;
	bool OPTIONS;
	bool CREATORS;
	bool HELP;

	std::string main_menu_txt[4] = { "PLAY", "CREATORS", "HELP", "EXIT" };
	std::string main_menu_txt2[4] = { "- PLAY -", "- CREATORS -", "- HELP -", "- EXIT -" };
	std::string creators_menu_txt[4] = { "Karol Bolanowski", "Michal Szul", "ISSP sem III", "BACK" };
	std::string creators_menu_txt2[4] = { "- Karol Bolanowski -", "- Michal Szul -", "- ISSP sem III -", "- BACK -" };
	std::string help_menu_txt[4] = { " ", " ", " ", "BACK" };
	std::string help_menu_txt2[4] = { " ", " ", " ", "- BACK -" };

	sf::Text text[MAX_NUMBER_OF_ITEMS];
	sf::RectangleShape rectangle;
	sf::Font font;

	sf::Texture gif_bcg[8];
	sf::Sprite gif_bcg_s[8];

	// GAME CLASS METHODS
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();
	void render();
	void run();

	// MENU METHODS
	void initMenu();
	void menuMoveUp();
	void menuMoveDown();
	void menuRenderButtons(sf::RenderTarget* target);
	void menuRenderButtons2(std::string menu_string[MAX_NUMBER_OF_ITEMS], std::string menu_string2[MAX_NUMBER_OF_ITEMS]);
	void menuCreateButton(std::string button_name, int which, int of_how_many, int font_size);
	int menuGetPressedItem() { return MenuIndex; }
	//void menuDeleteMenu();
	void menuDrawMenu(sf::RenderTarget* target);

	// PLAYER METHODS
	void updatePlayerMovement();

	// COLLISION METHODS
	void borders();				// handling collisons with window borders
	void collision();			// handling collisions with object

<<<<<<< HEAD
=======
    // initialization of methods
    void updateSFMLevents();
    void updatePlayer();
    void updatePlayerMovement();
    void update();
    void render();
    void run();
>>>>>>> 744555fb668c93e060173744eb3ac832c8b02f5b

};

