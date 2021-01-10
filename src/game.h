#pragma once
#include "player.h"
#include "map.h"
#include "object.h"
#include "libs.h"
#include "enemy.h"
#include "gui.h"
#define MAX_NUMBER_OF_ITEMS 4

class Game
{
private:
	// GAME VARIABLES
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock clock;
	sf::Clock waveClock;
	float waveTime;

	// CREATING OBJECTS WHEN WINDOW IS READY

	// GUI
	Gui gui;

	// map object
	Map map;

	// rooms
	Shop shop;
	StartingRoom room1;

	// object object
	Object obj;

	// player object
	Player player;

	// sellers
	Armorer armorer;

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

	// ROOM VARIABLES
	bool IN_STARTING_ROOM;
	bool IN_SHOP;
	bool PLAYER_TELEPORTATION;

	bool showheart;


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
	void updateSFMLEvents();
	void update();
	void render();
	void run();
	void newGame();
	
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
	void pickingUpObjects();

	// PLAYER MOVEMENT
	bool PLAYER_MOOVING_LEFT;
	bool PLAYER_MOOVING_RIGHT;
	bool PLAYER_IDLE;
	bool PLAYER_FACING_RIGHT;
	bool PLAYER_IS_ATTACKING;

	bool deleteHeart;

	// ADITIONAL THINGS
	sf::Texture screenshot;
	unsigned int screenshotNumber;
	void takeScreenshot(const sf::RenderWindow& window, const std::string& filename);

	void animation();
	
	int mnoznikStatic;
	int mnoznikDynamic;

	sf::Text testText;

	// COLLISION METHODS
	void borders();				// handling collisons with window borders

	// ENEMY:
	Enemy enemy;
	std::vector<Enemy> enemies;
	void updateEnemyMovement();
	void createEnemies();
	void updateEnemyHealth();
	int current_wave = 0;
	bool IS_WAVE_ACTIVE = false;

	// objects
	Heart heart;
	Key key;
	Coin coin;
	Shard shard;

	std::vector<Coin> coins;

};

