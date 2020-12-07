#pragma once
#include "player.h"
#include "map.h"
#include "libs.h"
#define MAX_NUMBER_OF_ITEMS 4

class Game
{
private:
	// GAME VARIABLES
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock clock;
	sf::Time dt;

	// CREATING OBJECTS WHEN WINDOW IS READY

	// map object
	Map map;

	// player object
	Player player;

	// end-screen object (etc.)

	// init.
	void initWindow();

public:
	Game();
	~Game();

	// WINDOW VARIABLES
	unsigned windowWidth = 1280;
	unsigned windowHeight = 720;

	// GAME STATE VARIABLES
	bool PLAYING_STATE;
	bool IN_MENU_STATE;
	bool GAME_STOPPED;

	// GUI VARIABLES
	sf::Texture guiTexture;
	sf::Sprite playerHealthBar;
	sf::Sprite playerHealthBarEmpty;

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
	std::string creators_menu_txt[4] = { "K.Bolanowski", "M.Szul", "ISSP III", "BACK" };
	std::string creators_menu_txt2[4] = { "- K.Bolanowski -", "- M.Szul -", "- ISSP III -", "- BACK -" };
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
	
	// GUI METHODS
	void initGUI();
	void renderGUI(sf::RenderTarget* target);

	// MENU METHODS
	void initMenu();
	void menuMoveUp();
	void menuMoveDown();
	void menuRenderButtons(sf::RenderTarget* target);
	void menuRenderButtons2(std::string menu_string[MAX_NUMBER_OF_ITEMS], std::string menu_string2[MAX_NUMBER_OF_ITEMS]);
	void menuCreateButton(std::string button_name, int which, int of_how_many, int font_size);
	int menuGetPressedItem() { return MenuIndex; }
	void menuDrawMenu(sf::RenderTarget* target);

	// PLAYER MOVEMENT METHODS
	void updatePlayerMovement();
	void updatePlayerHealth();

	bool MOOVING_LEFT;
	bool MOOVING_RIGHT;
	bool MOOVING_UP;
	bool MOOVING_DOWN;
	bool BEFORE_MOOVING;
	
	int mnoznikStatic;
	int mnoznikDynamic;

	// COLLISION METHODS
	void borders();				// handling collisons with window borders
	//void collision();			// handling collisions with object


};