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
	float waveTimeResume;
	int savedWaveTime;

	// CREATING OBJECTS WHEN WINDOW IS READY

	// GUI
	Gui gui;

	// map object
	Map map;

	// rooms
	Shop shop;
	StartingRoom room1;

	// object objects
	Object obj;
	Bonfire bonfire;
	Portal portal;
	Portal shopPortal;

	// collectible objects
	Heart heart;
	Key key;
	Coin coin;
	Shard shard;

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
	bool GAME_OPEN;
	bool YOU_WON_STATE;

	// ROOM VARIABLES
	bool IN_STARTING_ROOM;
	bool IN_SHOP;
	bool PLAYER_TELEPORTATION;

	// MENU VARIABLES
	sf::Music menu_music;
	sf::SoundBuffer change_buffer;
	sf::Sound change_sound;
	sf::SoundBuffer enter_buffer;
	sf::Sound enter_sound;
	sf::SoundBuffer quit_buffer;
	sf::Sound quit_sound;

	sf::SoundBuffer picking_up;
	sf::Sound picking_up_sound;
	sf::SoundBuffer leveling_up;
	sf::Sound leveling_up_sound;
	sf::SoundBuffer boom;
	sf::Sound boom_sound;
	sf::SoundBuffer wave_active;
	sf::Sound wave_active_sound;

	void initSounds();

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
	std::string help_menu_txt[4] = { "PORADNIK", " ", " ", "BACK" };
	std::string help_menu_txt2[4] = { "- PORADNIK -", " ", " ", "- BACK -" };

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

	// MENU METHODS
	void initMenu();
	void menuMoveUp();
	void menuMoveDown();
	void menuRenderButtons(sf::RenderTarget* target);
	void menuRenderButtons2(std::string menu_string[MAX_NUMBER_OF_ITEMS], std::string menu_string2[MAX_NUMBER_OF_ITEMS]);
	void menuCreateButton(std::string button_name, int which, int of_how_many, int font_size);
	int menuGetPressedItem() { return MenuIndex; }
	void menuDrawMenu(sf::RenderTarget* target);

	// PLAYER METHODS
	void updatePlayerMovement();
	void updatePlayerAttack();
	void pickingUpObjects();
	void levelingUp();

	// PLAYER
	bool PLAYER_MOOVING_LEFT;
	bool PLAYER_MOOVING_RIGHT;
	bool PLAYER_IDLE;
	bool PLAYER_FACING_RIGHT;
	bool PLAYER_IS_ATTACKING;
	bool PLAYER_PICKING_UP;
	bool PLAYER_DIED;

	// which sword or armor player has
	bool RED_SWORD;
	bool BLUE_SWORD;
	bool CYAN_SWORD;
	bool COPPER_ARMOR;
	bool SILVER_ARMOR;
	bool GOLDEN_ARMOR;

	bool CAN_I_BUY_SWORD;
	bool CAN_I_BUY_ARMOR;
	bool CAN_I_BUY_POTION;
	int SwordNumer = 0;
	int ArmorNumber = 0;
	int whenIBuyPotion;

	UNSword Un_Sword;
	UNArmor Un_Armor;
	UNPotion Un_Potion;

	// how much xp is required to level up
	float xpRequired;

	// ADITIONAL THINGS
	sf::Texture screenshot;
	unsigned int screenshotNumber;
	void takeScreenshot(const sf::RenderWindow& window, const std::string& filename);

	void animation();
	
	int mnoznikStatic;
	int mnoznikDynamic;

	int howManyXP;

	sf::Text testText;

	// ENEMY:
	Enemy enemy;
	std::vector<Enemy> enemies;
	void animationEnemy();
	void updateEnemyMovement();
	void updateEnemyAttack();
	void createEnemies(int ile_enemy);

	sf::Clock enemyInterval;
	float enemyCooldown;

	//GreenFrog greenFrog;
	//std::vector<GreenFrog> greenFrogs;

	//RedFrog redFrog;
	//std::vector<RedFrog> redFrogs;

	//WAVE
	sf::Vector2f lastKnownEnemyPosition;
	int currentWave = 0;
	bool IS_WAVE_ACTIVE = false;
	void initWave();
	void endWave();

	std::vector<Coin> coins;
	std::vector<Heart> hearts;
	std::vector<Shard> shards;
	std::vector<Object> shop_deals;

	std::vector<int> randomShardPositionX;
	std::vector<int> randomShardPositionY;

	void initShopDeals();

	float CZAS_ROZGRYWKI;
};

