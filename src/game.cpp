#include "game.h"

Game::Game()
{
	initSounds();
	initWindow();
	initMenu();
}

Game::~Game()
{
	delete this->window;
}

// GAME METHODS
void Game::initWindow()
{
	// all variables associated with window
	std::string title = "WERSJA BETA";
	sf::VideoMode windowBunds(windowWidth, windowHeight);
	this->window = new sf::RenderWindow(windowBunds, title, sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(30);
}

void Game::initSounds()
{
	// menu music
	if (!menu_music.openFromFile("res/sounds/menu_music.ogg")) {
		printf("nie wczytano menu_music.ogg");
	}
	// looping menu music
	menu_music.setLoop(true);

	// menu music
	if (!shop_music.openFromFile("res/sounds/shop_music.wav")) {
		printf("nie wczytano shop_music.ogg");
	}
	// looping menu music
	shop_music.setLoop(true);

	// menu music
	if (!win_song.openFromFile("res/sounds/win_song.wav")) {
		printf("nie wczytano win_music.ogg");
	}
	// looping menu music
	win_song.setLoop(true);
	
	// menu music
	if (!combat_music.openFromFile("res/sounds/combat_music.wav")) {
		printf("nie wczytano combat_music.ogg");
	}
	// looping menu music
	combat_music.setLoop(true);

	// menu music
	if (!notcombat_music.openFromFile("res/sounds/notcombat_music.wav")) {
		printf("nie wczytano notcombat_musicogg");
	}
	// looping menu music
	notcombat_music.setLoop(true);

	// change music
	if (!change_buffer.loadFromFile("res/sounds/menu_change.wav")) {
		printf("nie wczytano menu_change.wav");
	}
	change_sound.setBuffer(change_buffer);

	// enter music
	if (!enter_buffer.loadFromFile("res/sounds/menu_enter.wav")) {
		printf("nie wczytano menu_change.wav");
	}
	enter_sound.setBuffer(enter_buffer);

	// quit music
	if (!quit_buffer.loadFromFile("res/sounds/menu_quit.wav")) {
		printf("nie wczytano menu_change.wav");
	}
	quit_sound.setBuffer(quit_buffer);

	// picking up loot music
	if (!picking_up.loadFromFile("res/sounds/pickup.wav")) {
		printf("nie wczytano pickup.wav");
	}
	picking_up_sound.setBuffer(picking_up);

	// leveling up music
	if (!leveling_up.loadFromFile("res/sounds/levelingup.wav")) {
		printf("nie wczytano levelingup.wav");
	}
	leveling_up_sound.setBuffer(leveling_up);

	// activating enemies wave music
	if (!wave_active.loadFromFile("res/sounds/waveactive.wav")) {
		printf("nie wczytano levelingup.wav");
	}
	wave_active_sound.setBuffer(wave_active);

	// sword sound
	if (!sword.loadFromFile("res/sounds/sword_sound.wav")) {
		printf("nie wczytano levelingup.wav");
	}
	sword_sound.setBuffer(sword);
}


void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event))
	{
		// HANDLING WINDOW ACTIONS
		if (this->event.type == sf::Event::Closed)
		{
			GAME_OPEN = false;
			window->close();
		}

		// HANDLING KEY PRESSING IN MENU
		if (IN_MENU_STATE and PLAYING_STATE == false)
		{
			switch (event.type)
			{
			// key pressed
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menuMoveUp();
					//printf("m_u");
					break;

				case sf::Keyboard::Down:
					menuMoveDown();
					//printf("m_d");
					break;

				case sf::Keyboard::Return:
					menuRenderButtons(this->window);
					break;

				case sf::Keyboard::Escape:
					quit_sound.play();
					Sleep(500);
					GAME_OPEN = false;
					this->window->close();
					break;

				}
				break;

			// we don't process other types of events
			default:
				break;
			}
		}

		// HANDLING KEY PRESSING WHILE PLAYING
		if (!IN_MENU_STATE and PLAYING_STATE and !GAME_STOPPED)
		{
			//std::cout << player.playerSprite.getPosition().y << std::endl;
			switch (event.type)
			{
				// key pressed
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{

				case sf::Keyboard::R:
					waveTimeResume = waveTime;
					//std::cout << "Zatrzymany czas:" << waveTimeResume <<std::endl;
					GAME_STOPPED = true;
					std::cout << "ZATRZYMUJE GRE" << '\n';
					break;
				/*
				case sf::Keyboard::Backspace:
					GAME_STOPPED = true;
					break;
				*/
				case sf::Keyboard::E:
					PLAYER_PICKING_UP = true;
					break;

				case sf::Keyboard::Escape:
					quit_sound.play();
					Sleep(500);
					GAME_OPEN = false;
					this->window->close();
					break;
				
				case sf::Keyboard::C:
					screenshotNumber += 1;
					std::string filename_core = "SCREENSHOT_";
					std::string filename_number = std::to_string(screenshotNumber);
					std::string filename_path = "";//"files/";
					std::string filename_format = ".png";
					std::string filename = filename_path + filename_core + filename_number + filename_format;
					takeScreenshot(*window, filename);
					break;
				}
			
			}
			if (PLAYER_IS_ATTACKING == false)
			{
				switch (event.type)
				{
				case sf::Event::MouseButtonPressed:
					switch (event.mouseButton.button)
					{
					case sf::Mouse::Left:
						sword_sound.play();
						PLAYER_MOOVING_RIGHT = false;
						PLAYER_MOOVING_LEFT = false;
						PLAYER_IDLE = false;
						PLAYER_IS_ATTACKING = true;
						
						//std::cout << "PRZYCZAJONY TYGRYS, UKRYTY SMOK!" << '\n';
						updatePlayerAttack();
					}
				case sf::Event::KeyReleased:
					switch (event.key.code) 
					{
					case sf::Keyboard::K:
						sword_sound.play();
						PLAYER_MOOVING_RIGHT = false;
						PLAYER_MOOVING_LEFT = false;
						PLAYER_IDLE = false;
						PLAYER_IS_ATTACKING = true;

						//std::cout << "PRZYCZAJONY TYGRYS, UKRYTY SMOK!" << '\n';
						updatePlayerAttack();

					}
				}
			}

			// "G" MA DZIALA� �EBY PRZENIE�� GRACZA DO SKLEPU
			if (player.sprite.getPosition().x > 400 and player.sprite.getPosition().x < 500 and player.sprite.getPosition().y < 70 and IN_STARTING_ROOM and !IS_WAVE_ACTIVE)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::G:
						//std::cout << "TELEPORTACJA! WZIUUU..." << '\n';
						IN_STARTING_ROOM = false;
						IN_SHOP = true;

						std::cout << "jestes w sklepie" << '\n';
						std::cout << "IN STARTING ROOM: " << IN_STARTING_ROOM << '\n';
						std::cout << "IN_SHOP: " << IN_SHOP << '\n';
						
						//PLAYER_TELEPORTATION = true;
						player.sprite.setPosition({ 440.f, 580.f });
					}
				}
			}
			// I Z POWRTOEM....WZIUU
			else if (player.sprite.getPosition().x > 400 and player.sprite.getPosition().x < 500 and player.sprite.getPosition().y > 534 and IN_SHOP and !IS_WAVE_ACTIVE)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::G:
						//std::cout << "TELEPORTACJA! WZIUUU..." << '\n';
						IN_STARTING_ROOM = true;
						IN_SHOP = false;

						std::cout << "jestes w starting roomie" << '\n';
						std::cout << "IN STARTING ROOM: " <<  IN_STARTING_ROOM << '\n';
						std::cout << "IN_SHOP: " << IN_SHOP << '\n';

						//PLAYER_TELEPORTATION = true;
						player.sprite.setPosition({ 440.f, 65.f });
					}
				}
			}
			// START FALI
			else if (player.sprite.getPosition().x > 400 and player.sprite.getPosition().x < 500 and player.sprite.getPosition().y > 534 and IN_STARTING_ROOM)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::G:
						if (!IS_WAVE_ACTIVE)
						{
							wave_active_sound.play();

							std::cout << "CZAS NA FALE" << '\n';

							currentWave += 1;
								
							IS_WAVE_ACTIVE = true;

							initWave();

							waveClock.restart();
						}
					}
				}
			}
		}
		else if (GAME_STOPPED)
		{
			switch (event.type)
			{
				// key pressed
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Q:
					PLAYING_STATE = false;
					IN_MENU_STATE = true;
					GAME_STOPPED = false;
					std::cout << "WYJSCIE DO MENU" << '\n';
					break;

				case sf::Keyboard::R:
					waveClock.restart();
					PLAYING_STATE = true;
					IN_MENU_STATE = false;
					GAME_STOPPED = false;
					std::cout << "WZNOWIENIE GRY" << '\n';
					break;

				case sf::Keyboard::Escape:
					quit_sound.play();
					Sleep(500);
					GAME_OPEN = false;
					this->window->close();
					break;
				}
			}
		}
	}
}

void Game::update()
{
	//pozycja myszki, przydaje sie
	//std::cout << " X:  " << player.sprite.getPosition().x << "  Y: " << player.sprite.getPosition().y << std::endl;
	updateSFMLEvents();
	// update classes below
	if (PLAYING_STATE and GAME_OPEN and !GAME_STOPPED)
	{
		animation();

		if (IS_WAVE_ACTIVE) 
		{
			updateEnemyMovement();
			updateEnemyAttack();
			waveTime = (int)(waveClock.getElapsedTime().asSeconds()*100 + .5);
			waveTime = waveTime / 100;
			waveTime = waveTime + waveTimeResume;
		}

		if (IN_STARTING_ROOM)
		{
			initShopDeals();
			if (SwordNumer < 3) { shop_deals.push_back(Un_Sword); };
			shop_deals.push_back(Un_Armor);
			shop_deals.push_back(Un_Potion);
		}

		updatePlayerMovement();
		
		pickingUpObjects();
		levelingUp();

		gui.changeValues(player.coins, player.level, currentWave, waveTime, player.hp, player.fullHP, player.xp, xpRequired, player.poisoning);
		player.changePlayerEQ(RED_SWORD, BLUE_SWORD, CYAN_SWORD, COPPER_ARMOR, SILVER_ARMOR, GOLDEN_ARMOR);

		if (player.poisoning == 1 and currentWave >= whenIBuyPotion + 2)
		{
			player.poisoning = 0;
			whenIBuyPotion = 0;
			CAN_I_BUY_POTION = true;
		}

		if (player.level >= 12 and SwordNumer >= 3 and ArmorNumber >= 3)
		{
			YOU_WON_STATE = true;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			if(enemies[i].DIED) enemies.erase(enemies.begin() + i);
		}
		if (enemies.empty() == true and IS_WAVE_ACTIVE) endWave();
	}
}

void Game::render()
{
	this->window->clear();

	// render (draw) objects below

	while (IN_MENU_STATE)
	{
		shop_music.stop();
		combat_music.stop();
		notcombat_music.stop();

		newGame();
		update();

		// after entering the playing state music stops so it plays
		// the music again when you go back to the menu
		if (menu_music.getStatus() == 0)
		{
			menu_music.play();
			menu_music.setVolume(50.f);
		}

		menuDrawMenu(this->window);
		
		this->window->display();
		IN_STARTING_ROOM = true;

		break;
	}

	while (PLAYING_STATE and IN_STARTING_ROOM and !GAME_STOPPED and !PLAYER_DIED and !YOU_WON_STATE)
	{
		menu_music.stop();
		shop_music.stop();

		if (notcombat_music.getStatus() == 0 and !IS_WAVE_ACTIVE)
		{
			notcombat_music.play();
			notcombat_music.setVolume(10.f);
		}

		update();
		window->clear(sf::Color(42, 33, 52, 255));
		room1.renderMap(this->window);
		room1.renderObject(this->window);

		if (IS_WAVE_ACTIVE) 
		{
			notcombat_music.stop();

			if (combat_music.getStatus() == 0)
			{
				combat_music.play();
				combat_music.setVolume(10.f);
			}

			CAN_I_BUY_SWORD = true;
			CAN_I_BUY_ARMOR = true;

			for(int i = 0; i < enemies.size(); i++)
			{
				//enemies[i].renderRadius(this->window);
				enemies[i].render(this->window);
			}
		}
		else
		{
			combat_music.stop();
		}

		if (coins.empty() == false)
		{
			for (int i = 0; i < coins.size(); i++)
			{
				coins[i].render(this->window);
			}
		}

		if (hearts.empty() == false)
		{
			for (int i = 0; i < hearts.size(); i++)
			{
				hearts[i].render(this->window);
			}
		}

		if (shards.empty() == false)
		{
			for (int i = 0; i < shards.size(); i++)
			{
				shards[i].render(this->window);
			}
		}

		bonfire.render(this->window);

		gui.render(this->window);
		player.render(this->window);
		
		this->window->display();
		if(!GAME_OPEN) break;
	}

	while (PLAYING_STATE and IN_SHOP and !GAME_STOPPED and !PLAYER_DIED and !YOU_WON_STATE)
	{
		notcombat_music.stop();

		if (shop_music.getStatus() == 0)
		{
			shop_music.play();
			shop_music.setVolume(10.f);
		}

		update();

		this->window->clear(sf::Color(42, 33, 52, 255));

		shop.renderMap(this->window);
		shop.renderObject(this->window);
		shop.renderPrices(this->window);

		if (shop_deals.empty() == false)
		{
			for (int i = 0; i < shop_deals.size(); i++)
			{
				shop_deals[i].render(this->window);
			}
		}

		gui.render(this->window);
		player.render(this->window);

		this->window->display();
		if (!GAME_OPEN) break;
	}

	while (GAME_STOPPED)
	{	
		notcombat_music.stop();
		combat_music.stop();

		if (shop_music.getStatus() == 0)
		{
			shop_music.play();
			shop_music.setVolume(10.f);
		}

		update();
		testText.setFont(font);
		testText.setCharacterSize(40);
		testText.setFillColor(sf::Color::White);
		testText.setOutlineColor(sf::Color::Black);
		testText.setOutlineThickness(2);
		testText.setStyle(sf::Text::Bold);
		testText.setString("> Click R to RESUME or Q to go back to the MENU <");
		testText.setPosition((windowWidth-testText.getGlobalBounds().width)/2, (windowHeight-testText.getGlobalBounds().height)/2);
		this->window->draw(testText);
		this->window->display();
		if (!GAME_OPEN) break;
	}

	if (PLAYER_DIED)
	{
		update();
		testText.setFont(font);
		testText.setCharacterSize(100);
		testText.setFillColor(sf::Color::Red);
		testText.setOutlineColor(sf::Color::Black);
		testText.setOutlineThickness(2);
		testText.setStyle(sf::Text::Bold);
		std::string currentWaveStr = "zaliczyles zgona na "+std::to_string(currentWave)+" fali byczq";
		testText.setString(currentWaveStr);
		testText.setPosition((windowWidth-testText.getGlobalBounds().width)/2, (windowHeight-testText.getGlobalBounds().height)/2);
		this->window->draw(testText);
		this->window->display();
		Sleep(5000);
		PLAYING_STATE = false;
		IN_MENU_STATE = true;
	}

	if (YOU_WON_STATE)
	{
		notcombat_music.stop();
		combat_music.stop();
		menu_music.stop();
		shop_music.stop();

		if (win_song.getStatus() == 0)
		{
			win_song.play();
			win_song.setVolume(50.f);
		}

		update();
		testText.setFont(font);
		testText.setCharacterSize(100);
		testText.setFillColor(sf::Color::Red);
		testText.setOutlineColor(sf::Color::Black);
		testText.setOutlineThickness(2);
		testText.setStyle(sf::Text::Bold);
		CZAS_ROZGRYWKI = (float) CZAS_ROZGRYWKI;
		std::string currentWaveStr = "Brawo byczq, wygrales w "+std::to_string(currentWave)+" rundzie!\nTwoj czas: "+std::to_string(CZAS_ROZGRYWKI)+" s";
		testText.setString(currentWaveStr);
		testText.setPosition((windowWidth - testText.getGlobalBounds().width) / 2, (windowHeight - testText.getGlobalBounds().height) / 2);
		this->window->draw(testText);
		this->window->display();
		Sleep(15000);
		win_song.stop();
		PLAYING_STATE = false;
		IN_MENU_STATE = true;
	}
}

void Game::run()
{
	// variables that should be defined only once and before the game start

	// game states
	GAME_OPEN = true;
	PLAYING_STATE = false;
	IN_MENU_STATE = true;
	GAME_STOPPED = false;

	CAN_I_BUY_ARMOR = true;
	CAN_I_BUY_SWORD = true;
	CAN_I_BUY_POTION = true;

	// setting that idle animation is starting animation
	PLAYER_MOOVING_RIGHT = false;
	PLAYER_MOOVING_LEFT = false;
	PLAYER_IDLE = true;
	PLAYER_PICKING_UP = false;

	// screenshot iterable
	screenshotNumber = 0;
	portal.create({ 435.f, 70.f }, { 0.5f, 0.5f });
	shopPortal.create({ 435.f, 562.f }, { 1.2f, 1.2f });
	bonfire.create({ 435.f, 562.f }, { 1.2f, 1.2f });

	// main loop
	while (this->window->isOpen())
	{
		update();
		render();
	}
}

void Game::newGame()
{
	CZAS_ROZGRYWKI = 0;
	YOU_WON_STATE = false;
	IS_WAVE_ACTIVE = false;
	currentWave = 0;
	waveTime = 0.0;
	waveTimeResume = 0.0;
	waveClock.restart();

	player.initSprite();
	PLAYER_DIED = false;
	player.coins = 0;
	player.xp = 0;
	player.drunk = false;
	player.level = 1;
	player.hp = 250;
	player.fullHP = 250;
	player.speed = 1;
	player.poisoning = 0;
	player.dmg = 20;
	player.def = 1;
	RED_SWORD = false;
	BLUE_SWORD = false;
	CYAN_SWORD = false;
	COPPER_ARMOR = false;
	SILVER_ARMOR = false;
	GOLDEN_ARMOR = false;

	enemyCooldown = 0.0;
	enemies.clear();
	coins.clear();
	shards.clear();
	hearts.clear();
}

// MENU METHODS
void Game::initMenu()
{
	for (int i = 0; i <= 7; i++) {
		std::string path = "res/textures/gif/frame_" + std::to_string(i) + ".png";
		if (!gif_bcg[i].loadFromFile(path)) printf("nie wczytano %d", i);
		gif_bcg_s[i].setTexture(gif_bcg[i]);
		gif_bcg_s[i].setScale(2.5, 2.5);
	};

	if (!font.loadFromFile("res/fonts/ostrich-regular.ttf")) printf("nie wczytalo czcionki");
	else {
		//if(play_pressed):
			//...GAME START
		MAIN_MENU = true;
		CREATORS = false;
		HELP = false;
		menuRenderButtons2(main_menu_txt, main_menu_txt2);
	};

	//background do tekstu
	rectangle.setSize(sf::Vector2f(400, windowHeight));
	rectangle.setFillColor(sf::Color(0, 0, 0, 170));
	rectangle.setPosition(windowWidth / 2 - 200, 0);
}

void Game::menuMoveUp()
{
	change_sound.play();
	if (MAIN_MENU and not CREATORS and not HELP) {
		if (MenuIndex - 1 >= 0) {
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex--;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
		else {
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
	}
	else if (not MAIN_MENU and CREATORS and not HELP) {
		if (MenuIndex - 1 >= 0) {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex--;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
		else {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
	}
	else if (not MAIN_MENU and not CREATORS and HELP) {
		if (MenuIndex - 1 >= 0) {
			menuCreateButton(help_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = MenuIndex - 3;
			menuCreateButton(help_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
		else {
			menuCreateButton(help_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
			menuCreateButton(help_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
	}
}

void Game::menuMoveDown()
{
	change_sound.play();
	if (MAIN_MENU and not CREATORS and not HELP) {
		if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex++;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
		else {
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = 0;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
	}
	else if (not MAIN_MENU and CREATORS and not HELP) {
		if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex++;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
		else {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = 0;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
	}
	else if (not MAIN_MENU and not CREATORS and HELP) {
		if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			menuCreateButton(help_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = MenuIndex + 3;
			menuCreateButton(help_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
		else {
			menuCreateButton(help_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 60);
			MenuIndex = 0;
			menuCreateButton(help_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 80);
		}
	}
}

void Game::menuRenderButtons(sf::RenderTarget* target)
{
	if (MAIN_MENU and not CREATORS and not HELP) {
		switch (menuGetPressedItem())
		{
		case 0:
			std::cout << "Ktos nacisnal Play" << '\n';
			enter_sound.play();
			IN_MENU_STATE = false;
			PLAYING_STATE = true;
			newGame();
			break;
		case 1:
			std::cout << "Ktos nacisnal Creators" << '\n';
			enter_sound.play();
			MAIN_MENU = false;
			CREATORS = true;
			menuRenderButtons2(creators_menu_txt, creators_menu_txt2);
			break;
		case 2:
			std::cout << "Ktos nacisnal Help" << '\n';
			enter_sound.play();
			MAIN_MENU = false;
			HELP = true;
			menuRenderButtons2(help_menu_txt, help_menu_txt2);
			break;
		case 3:
			quit_sound.play();
			Sleep(500);
			window->close();
		default:
			break;
		}
	}
	else if (not MAIN_MENU and CREATORS and not HELP) {
		switch (menuGetPressedItem())
		{
		case 0:
			std::cout << "Ktos nacisnal Bolanowski" << '\n';
			enter_sound.play();
			//link otwiera sie tylko pod windowsem
			system("start https://github.com/sweetbunnypl/");
			break;
		case 1:
			std::cout << "Ktos nacisnal Szul" << '\n';
			enter_sound.play();
			//link otwiera sie tylko pod windowsem
			system("start https://github.com/SonOfGrabarz");
			break;
		case 2:
			std::cout << "Ktos nacisnal ISSP" << '\n';
			enter_sound.play();
			//link otwiera sie tylko pod windowsem
			system("start https://wfa.uni.wroc.pl/pl/informatyka-stosowana-isystemy-pomiarowe/");
			break;
		case 3:
			MAIN_MENU = true;
			CREATORS = false;
			menuRenderButtons2(main_menu_txt, main_menu_txt2);
			quit_sound.play();
		default:
			break;
		}
	}
	else if (not MAIN_MENU and not CREATORS and HELP) {
		switch (menuGetPressedItem())
		{
		case 0:
			std::cout << "Ktos nacisnal Poradnik i info" << '\n';
			enter_sound.play();
			//link otwiera sie tylko pod windowsem
			system("start https://github.com/sweetbunnypl/projekt_cpp_Bolanowski_Szul/blob/main/README.md");
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			MAIN_MENU = true;
			HELP = false;
			menuRenderButtons2(main_menu_txt, main_menu_txt2);
			quit_sound.play();
		default:
			break;
		}
	}
}

void Game::menuRenderButtons2(std::string menu_string[MAX_NUMBER_OF_ITEMS], std::string menu_string2[MAX_NUMBER_OF_ITEMS])
{
	MenuIndex = 0;
	menuCreateButton(menu_string2[0], 0, MAX_NUMBER_OF_ITEMS, 80);
	//for (int i = 1; i<= value; i++) menuCreateButton(menu_string[i], i, MAX_NUMBER_OF_ITEMS, 60);
	menuCreateButton(menu_string[1], 1, MAX_NUMBER_OF_ITEMS, 60);
	menuCreateButton(menu_string[2], 2, MAX_NUMBER_OF_ITEMS, 60);
	menuCreateButton(menu_string[3], 3, MAX_NUMBER_OF_ITEMS, 60);
}

void Game::menuCreateButton(std::string button_name, int which, int of_how_many, int font_size)
{
	text[which].setFont(font);
	text[which].setCharacterSize(font_size);
	text[which].setStyle(sf::Text::Regular);
	text[which].setFillColor(sf::Color::White);
	text[which].setString(button_name);
	text[which].setPosition(sf::Vector2f((windowWidth / 2) - (text[which].getGlobalBounds().width / 2), (windowHeight / (of_how_many + 1) * (which + 1)) - (text[which].getGlobalBounds().height / 2)));
}

void Game::menuDrawMenu(sf::RenderTarget* target)
{
	pause++;
	int dt = 5;
	if (pause < dt) window->draw(gif_bcg_s[0]);
	else if (pause < dt * 2 and pause >= dt) window->draw(gif_bcg_s[1]);
	else if (pause < dt * 3 and pause >= dt * 2) window->draw(gif_bcg_s[2]);
	else if (pause < dt * 4 and pause >= dt * 3) window->draw(gif_bcg_s[3]);
	else if (pause < dt * 5 and pause >= dt * 4) window->draw(gif_bcg_s[4]);
	else if (pause < dt * 6 and pause >= dt * 5) window->draw(gif_bcg_s[5]);
	else if (pause < dt * 7 and pause >= dt * 6) window->draw(gif_bcg_s[6]);
	else if (pause < dt * 8 and pause >= dt * 7) window->draw(gif_bcg_s[7]);
	else {
		pause = 0;
		window->draw(gif_bcg_s[0]);
	}

	window->draw(rectangle);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window->draw(text[i]);
	}
}

// PLAYER METHODS
void Game::updatePlayerMovement()
{
	for (int i = 0; i < shards.size(); i++)
	{
		if (shards.empty() == false)
		{
			if (player.sprite.getGlobalBounds().intersects(shards[i].sprite.getGlobalBounds()))
			{
				picking_up_sound.play();
				player.xp += 2;
				shards.erase(shards.begin() + i);
				std::cout << "XP: " << player.xp << '\n';
			}
		}
	}
	// player position -> console
	//std::cout << "X: " << player.playerSprite.getPosition().x << '\n';
	//std::cout << "Y: " << player.playerSprite.getPosition().y << '\n';

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		// moving up
		player.sprite.move({ 0.f, -5.f });

		// collision with upper side of object
		for (int i = 0; i <= 52; i++)
		{
			if (room1.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds()) or
				shop.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds()))
			{
				player.sprite.move({ 0.f, 5.f });	
			}
		}	
	}
	else
	{
		PLAYER_IDLE = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		// moving bottom
		player.sprite.move({ 0.f, 5.f });

		// collision with bottom side of object
		for (int i = 0; i <= 52; i++)
		{
			if (room1.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds()) or
				shop.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds())
				)
			{
				player.sprite.move({ 0.f, -5.f });
			}
		}	
	}
	else
	{
		PLAYER_IDLE = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		// moving left
		PLAYER_MOOVING_LEFT = true;
		PLAYER_IDLE = false;
		player.sprite.move({ -5.f, 0.f });

		// collision with left side of object
		for (int i = 0; i <= 52; i++)
		{
			if (room1.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds()) or
				shop.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds())
				)
			{
				player.sprite.move({ 5.f, 0.f });
			}
		}
	}
	else
	{
		PLAYER_MOOVING_LEFT = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		// moving right
		PLAYER_MOOVING_RIGHT = true;
		PLAYER_IDLE = false;
		player.sprite.move({ 5.f, 0.f });

		// collision with right side of object
		for (int i = 0; i <= 52; i++)
		{
			if(room1.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds()) or
				shop.object[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds())
				)
			{
				player.sprite.move({ -5.f, 0.f });
			}
		}
	}
	else
	{
		PLAYER_MOOVING_RIGHT = false;
	}
}

void Game::pickingUpObjects()
{
	if (PLAYER_PICKING_UP)
	{
		// coins
		for (int i = 0; i < coins.size(); i++)
		{
			if (coins.empty() == false)
			{
				if (player.sprite.getGlobalBounds().intersects(coins[i].sprite.getGlobalBounds()))
				{
					picking_up_sound.play();
					player.coins += 1;
					coins.erase(coins.begin() + i);
				}
			}
		}

		for (int i = 0; i < hearts.size(); i++)
		{
			if (hearts.empty() == false)
			{
				if (player.hp > 0 and player.fullHP - player.hp <= player.fullHP - 15)
				{
					if (player.sprite.getGlobalBounds().intersects(hearts[i].sprite.getGlobalBounds()))
					{
						picking_up_sound.play();
						player.hp += 15;
						hearts.erase(hearts.begin() + i);
					}
				}
				
			}
		}

		if (IN_SHOP)
		{
			for (int i = 0; i < shop_deals.size(); i++)
			{
				if (shop_deals.empty() == false)
				{
					if (CAN_I_BUY_SWORD)
					{
						if (player.sprite.getGlobalBounds().intersects(Un_Sword.sprite.getGlobalBounds()) and player.coins >= 5 and SwordNumer < 3)
						{
							picking_up_sound.play();
							SwordNumer += 1;

							if (SwordNumer == 1)
							{
								RED_SWORD = true;
								BLUE_SWORD = false;
								CYAN_SWORD = false;
								player.dmg += 20;
							}

							if (SwordNumer == 2)
							{
								RED_SWORD = false;
								BLUE_SWORD = true;
								CYAN_SWORD = false;
								player.dmg += 30;
							}

							if (SwordNumer == 3)
							{
								RED_SWORD = false;
								BLUE_SWORD = false;
								CYAN_SWORD = true;
								player.dmg += 50;
							}

							player.coins -= 5;
							CAN_I_BUY_SWORD = false;
						}
					}

					if (CAN_I_BUY_ARMOR)
					{
						if (player.sprite.getGlobalBounds().intersects(Un_Armor.sprite.getGlobalBounds()) and player.coins >= 10 and ArmorNumber < 3)
						{
							picking_up_sound.play();
							ArmorNumber += 1;

							if (ArmorNumber == 1)
							{
								COPPER_ARMOR = true;
								SILVER_ARMOR = false;
								GOLDEN_ARMOR = false;
								player.def = 0.8;
							}

							if (ArmorNumber == 2)
							{
								COPPER_ARMOR = false;
								SILVER_ARMOR = true;
								GOLDEN_ARMOR = false;
								player.def = 0.5;
							}

							if (ArmorNumber == 3)
							{
								COPPER_ARMOR = false;
								SILVER_ARMOR = false;
								GOLDEN_ARMOR = true;
								player.def = 0.3;
							}

							player.coins -= 10;
							CAN_I_BUY_ARMOR = false;
						}
					}
					if (CAN_I_BUY_POTION)
					{
						if (player.sprite.getGlobalBounds().intersects(Un_Potion.sprite.getGlobalBounds()) and player.coins >= 3)
						{
							picking_up_sound.play();
							player.coins -= 3;
							player.hp += ((int)player.fullHP - (int)player.hp) * 0.8;
							player.poisoning = 1;
							CAN_I_BUY_POTION = false;
							whenIBuyPotion = currentWave;
						}
					}
				}
			}
		}

		PLAYER_PICKING_UP = false;
	}
}

void Game::levelingUp()
{
	// 1-15 lvl
	if (player.level > 0 and player.level <= 15)
	{
		xpRequired = 2 * player.level + 7;

		if (player.xp >= xpRequired)
		{
			leveling_up_sound.play();
			player.level += 1;
			player.xp = 0;
			player.fullHP += 2;
		}
	}

	// 15-30 lvl
	if (player.level > 15 and player.level <= 30)
	{
		xpRequired = 5 * player.level - 38;

		if (player.xp >= xpRequired)
		{
			leveling_up_sound.play();
			player.level += 1;
			player.xp = 0;
			player.fullHP += 5;
		}
	}

	// > 30 lvl
	if (player.level > 30)
	{
		xpRequired = 9 * player.level - 158;

		if (player.xp >= xpRequired)
		{
			leveling_up_sound.play();
			player.level += 1;
			player.xp = 0;
			player.fullHP += 10;
		}
	}
}

// ADITIONAL METHODS
void Game::takeScreenshot(const sf::RenderWindow& window, const std::string& filename)
{
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	if (texture.copyToImage().saveToFile(filename))
	{
		std::cout << "screenshot saved to " << filename << std::endl;
	}
}

void Game::animation()
{
	// ANIMATIONS
	if (clock.getElapsedTime().asSeconds() > 0.15f)
	{
		// coin animation
		if (coins.size() != 0)
		{
			if (coin.frame > 12 * 4)
			{
				coin.frame = 0;
			}
			else
			{
				coin.frame += 12;
			}

			for (int i = 0; i < coins.size(); i++)
			{
				coins[i].sprite.setTextureRect(sf::IntRect(coin.frame, 0, 12, 17));
			}
		}
		
		// shard animation
		if (shards.size() != 0)
		{
			if (shard.frame > 12 * 4)
			{
				shard.frame = 0;
			}
			else
			{
				shard.frame += 12;
			}

			for (int i = 0; i < shards.size(); i++)
			{
				shards[i].sprite.setTextureRect(sf::IntRect(shard.frame, 0, 12, 30));
			}
		}

		// heart animation
		if (hearts.size() != 0)
		{
			if (heart.frame > 11 * 4)
			{
				heart.frame = 0;
			}
			else
			{
				heart.frame += 11;
			}

			for (int i = 0; i < hearts.size(); i++)
			{
				hearts[i].sprite.setTextureRect(sf::IntRect(heart.frame, 0, 11, 16));
			}
		}

		// ENEMY MOVING ANIMATION
		for (int i = 0; i < enemies.size(); i++)
		{
			int dc = 0;
			if (enemies[i].color) dc = 559;
			if (!enemies[i].ATTACKING and !enemies[i].DYING)
			{
				if (enemies[i].frame >= 13)
				{
					enemies[i].frame = 0;
				}
				else
				{
					enemies[i].frame += 1;
				}

				if (enemies[i].ENEMY_IDLE and enemies[i].ENEMY_FACING_RIGHT == false)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].frame * 96, dc + 280, 96, 64));
				}
				else if (enemies[i].ENEMY_IDLE and enemies[i].ENEMY_FACING_RIGHT)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].frame * 96, dc + 0, 96, 64));
				}

				if (enemies[i].ENEMY_MOOVING_LEFT and !enemies[i].ENEMY_IDLE)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].frame * 100, dc + 346, 100, 68));
				}
				else if (enemies[i].ENEMY_MOOVING_RIGHT and !enemies[i].ENEMY_IDLE)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].frame * 100, dc + 68, 100, 68));
				}
			}
			else if (enemies[i].ATTACKING and !enemies[i].DYING) {
				if (enemies[i].attackFrame >= 13)
				{
					enemies[i].attackFrame = 0;
				}
				else
				{
					enemies[i].attackFrame += 1;
				}

				if (enemies[i].ENEMY_FACING_RIGHT == false)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].attackFrame * 136, dc + 416, 136, 72));
				}
				else if (enemies[i].ENEMY_FACING_RIGHT)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].attackFrame * 136, dc + 136, 136, 72));
				}
			}
			else if (enemies[i].DYING) {
				if (enemies[i].dyingFrame >= 13)
				{
					enemies[i].dyingFrame = 0;
					enemies[i].DIED = true;
				}
				else
				{
					enemies[i].dyingFrame += 1;
				}

				if (enemies[i].ENEMY_FACING_RIGHT == false)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].dyingFrame * 100, dc + 488, 100, 72));
				}
				else if (enemies[i].ENEMY_FACING_RIGHT)
				{
					enemies[i].sprite.setTextureRect(sf::IntRect(enemies[i].dyingFrame * 100, dc + 210, 100, 72));
				}
			}
		}

		// STATIC ANIMATIONS
		if (IN_STARTING_ROOM)
		{
			// STATIC ANIMATIONS COUNTER
			if (IS_WAVE_ACTIVE)
			{
				if (bonfire.frame > 64 * 5)
				{
					bonfire.frame = 64;
				}
				else
				{
					bonfire.frame += 64;
				}
				bonfire.sprite.setTextureRect(sf::IntRect(bonfire.frame, 0, 64, 64));
			}

			else if (!IS_WAVE_ACTIVE)
			{
				bonfire.sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
			}
		}

		// PLAYER MOVING ANIMATION
		if (player.frame > 384)
		{
			player.frame = 0;
		}
		else
		{
			player.frame += 64;
		}

		if (PLAYER_IDLE and PLAYER_FACING_RIGHT == false)
		{
			player.sprite.setTextureRect(sf::IntRect(player.frame, 128, 64, 64));
		}

		if (PLAYER_IDLE and PLAYER_FACING_RIGHT)
		{
			player.sprite.setTextureRect(sf::IntRect(player.frame, 192, 64, 64));
		}

		if (PLAYER_MOOVING_LEFT)
		{	
			PLAYER_FACING_RIGHT = false;
			player.sprite.setTextureRect(sf::IntRect(player.frame, 0, 64, 64));
		}

		if (PLAYER_MOOVING_RIGHT)
		{
			PLAYER_FACING_RIGHT = true;
			player.sprite.setTextureRect(sf::IntRect(player.frame, 64, 64, 64));
		}

		// PLAYER ATTACKING ANIMATION
		if (player.attackFrame > 720 and PLAYER_IS_ATTACKING)
		{
			player.attackFrame = 0;

			if (PLAYER_IS_ATTACKING)
			{
				PLAYER_IS_ATTACKING = false;
				PLAYER_IDLE = true;
			}	
		}
		else if (player.attackFrame <= 720 and PLAYER_IS_ATTACKING)
		{
			player.attackFrame += 120;
		}

		if (PLAYER_IS_ATTACKING and PLAYER_FACING_RIGHT == false)
		{
			player.sprite.setTextureRect(sf::IntRect(player.attackFrame, 256, 120, 76));
		}
		else if (PLAYER_IS_ATTACKING and PLAYER_FACING_RIGHT)
		{
			player.sprite.setTextureRect(sf::IntRect(player.attackFrame, 332, 120, 76));
		}

		clock.restart();
	}
}

void Game::animationEnemy()
{
}

void Game::createEnemies(int ile_enemy)
{
	for(int i = 0; i < ile_enemy; i++)
	{
		int delta_x = 30;
		float delta_y = (windowWidth - gui.size.x - delta_x*2 - ile_enemy * enemy.sprite.getGlobalBounds().width) / (ile_enemy + 1);
		float x_enemy = abs(delta_x+(delta_y*(i+1))+i*enemy.sprite.getGlobalBounds().width);
		float color = (float)rand() / RAND_MAX;
		//std::cout << color << std::endl;
		if (color >= 0.5) 
		{
			enemy.color = 1;
			enemy.ATTACKING = false;
			enemy.DYING = false;
			enemy.DIED = false;
			enemy.sprite.setTextureRect(sf::IntRect(0, 559, 96, 64));
			enemy.create(sf::Vector2f(x_enemy, 200), sf::Vector2f(1, 1), sf::Vector2f(1, 1), 50 + 25 * currentWave);
			enemy.damage = 5+(currentWave^2)/4;
		}
		else 
		{
			enemy.color = 0;
			enemy.ATTACKING = false;
			enemy.DYING = false;
			enemy.DIED = false;
			enemy.sprite.setTextureRect(sf::IntRect(0, 0, 96, 64));
			enemy.damage = 3+(currentWave^2)/5;
			enemy.create(sf::Vector2f(x_enemy, 200), sf::Vector2f(1, 1), sf::Vector2f(1, 1), 25 + 15 * currentWave);
		}
		//enemy.create(sf::Vector2f(20+(((windowWidth-200)/ile_enemy)*i), 100), sf::Vector2f(1, 1), sf::Vector2f(3, 3), 50+25*currentWave);
		enemies.push_back(enemy);
	}
}

void Game::updateEnemyMovement()
{
	sf::Vector2f gracz_size = sf::Vector2f(player.sprite.getGlobalBounds().width, player.sprite.getGlobalBounds().height);
	sf::Vector2f gracz = sf::Vector2f(player.sprite.getPosition().x + gracz_size.x/2, player.sprite.getPosition().y + gracz_size.y/2);
	for (int i = 0; i < enemies.size(); i++)
	{
		sf::Vector2f przeciwnik = sf::Vector2f(enemies[i].terror.getPosition().x + enemies[i].terrorRadius, enemies[i].terror.getPosition().y + enemies[i].terrorRadius);
		float dystans = sqrt(pow((przeciwnik.x - gracz.x), 2) + pow((przeciwnik.y - gracz.y), 2));
		//std::cout << "dystans dla przeciwnika" << i << ":" << dystans << std::endl;

		if (!player.sprite.getGlobalBounds().intersects(enemies[i].sprite.getGlobalBounds()) and dystans < enemies[i].terrorRadius)
		{
			enemies[i].ENEMY_IDLE = false;
			if (gracz.x > przeciwnik.x)
			{
				enemies[i].sprite.move(sf::Vector2f(enemy.speed.x, 0.f));
				enemies[i].terror.move(sf::Vector2f(enemy.speed.x, 0.f));
				enemies[i].attack.move(sf::Vector2f(enemy.speed.x, 0.f));
				enemies[i].ENEMY_MOOVING_RIGHT = true;
				enemies[i].ENEMY_FACING_RIGHT = true;
				enemies[i].ENEMY_MOOVING_LEFT = false;
			}

			else if (gracz.x < przeciwnik.x)
			{
				enemies[i].sprite.move(sf::Vector2f(-enemy.speed.x, 0.f));
				enemies[i].terror.move(sf::Vector2f(-enemy.speed.x, 0.f));
				enemies[i].attack.move(sf::Vector2f(-enemy.speed.x, 0.f));
				enemies[i].ENEMY_MOOVING_RIGHT = false;
				enemies[i].ENEMY_FACING_RIGHT = false;
				enemies[i].ENEMY_MOOVING_LEFT = true;
			}

			if (gracz.y > przeciwnik.y)
			{
				enemies[i].sprite.move(sf::Vector2f(0.f, enemy.speed.x));
				enemies[i].terror.move(sf::Vector2f(0.f, enemy.speed.x));
				enemies[i].attack.move(sf::Vector2f(0.f, enemy.speed.x));
			}

			else if (gracz.y < przeciwnik.y)
			{
				enemies[i].sprite.move(sf::Vector2f(0.f, -enemy.speed.x));
				enemies[i].terror.move(sf::Vector2f(0.f, -enemy.speed.x));
				enemies[i].attack.move(sf::Vector2f(0.f, -enemy.speed.x));
			}

			//enemies[i].txtHealth.setPosition(enemies[i].sprite.getPosition().x + (enemies[i].sprite.getGlobalBounds().width / 2) - enemies[i].txtHealth.getGlobalBounds().width / 2, enemies[i].sprite.getPosition().y + (enemies[i].sprite.getGlobalBounds().height / 2) - (enemies[i].txtHealth.getGlobalBounds().height / 2) - 40);
		}
		else enemies[i].ENEMY_IDLE = true;
	}
}

void Game::updateEnemyAttack()
{
	sf::Vector2f gracz_size = sf::Vector2f(player.sprite.getGlobalBounds().width, player.sprite.getGlobalBounds().height);
	sf::Vector2f gracz = sf::Vector2f(player.sprite.getPosition().x + gracz_size.x / 2, player.sprite.getPosition().y + gracz_size.y / 2);
	for (int i = 0; i < enemies.size(); i++)
	{
		sf::Vector2f przeciwnik = sf::Vector2f(enemies[i].attack.getPosition().x + enemies[i].attackRadius, enemies[i].attack.getPosition().y + enemies[i].attackRadius);
		float dystans = sqrt(pow((przeciwnik.x - gracz.x), 2) + pow((przeciwnik.y - gracz.y), 2));
		//std::cout << dystans << "   " << przeciwnik.x << "   " << przeciwnik.y << std::endl;
		if (dystans < enemies[i].attackRadius)
		{
			if (enemyCooldown >= 5)
			{
				enemies[i].ATTACKING = true;
				enemyInterval.restart();
				player.hp = player.hp - (enemies[i].damage * 0.8 * currentWave * player.def);
				std::cout << i << "# enemy hit!  your health: " << player.hp << std::endl;
			}

			enemyCooldown = (int)(enemyInterval.getElapsedTime().asSeconds() * 100 + .5);
			enemyCooldown = enemyCooldown / 100;

			//std::cout << enemyCooldown << std::endl;

			if (player.hp <= 0)
				PLAYER_DIED = true;
				//std::cout << "zaliczyles zgona byczq, liczba fal, ktora przezyles:" << std::endl;
			//std::cout << "twoje hp: " << player.hp << std::endl;
		}
		else {
			enemies[i].ATTACKING = false;
		}
	}
}

void Game::updatePlayerAttack()
{
	sf::Vector2f gracz_size = sf::Vector2f(player.sprite.getGlobalBounds().width, player.sprite.getGlobalBounds().height);
	sf::Vector2f gracz = sf::Vector2f(player.sprite.getPosition().x + gracz_size.x / 2, player.sprite.getPosition().y + gracz_size.y / 2);
	for (int i = 0; i < enemies.size(); i++)
	{
		sf::Vector2f przeciwnik = sf::Vector2f(enemies[i].attack.getPosition().x + enemies[i].attackRadius, enemies[i].attack.getPosition().y + enemies[i].attackRadius);
		float dystans = sqrt(pow((przeciwnik.x - gracz.x), 2) + pow((przeciwnik.y - gracz.y), 2));

		if (dystans < enemies[i].attackRadius)
		{
			enemies[i].health = enemies[i].health - player.dmg + player.level;
			std::cout << i << "# enemy got hit! health remaining: " << enemies[i].health << std::endl;
			//enemies[i].txtHealth.setPosition(enemies[i].sprite.getPosition().x + (enemies[i].sprite.getGlobalBounds().width / 2) - enemies[i].txtHealth.getGlobalBounds().width / 2, enemies[i].sprite.getPosition().y + (enemies[i].sprite.getGlobalBounds().height / 2) - (enemies[i].txtHealth.getGlobalBounds().height / 2) - 40);
			enemies[i].updateHealth(enemies[i].health);

			if (enemies[i].health <= 0)
			{	
				enemies[i].DYING = true;
				lastKnownEnemyPosition = sf::Vector2f({ enemies[i].sprite.getPosition().x+(enemies[i].sprite.getGlobalBounds().width/2)-(coin.sprite.getGlobalBounds().width/2), enemies[i].sprite.getPosition().y + (enemies[i].sprite.getGlobalBounds().height / 2) - (coin.sprite.getGlobalBounds().height / 2) });
				//std::cout << "LastKnownEnemyPosition X: " << enemies[i].sprite.getPosition().x << " Y: " << enemies[i].sprite.getPosition().y << '\n';
				coin.create({ lastKnownEnemyPosition.x, lastKnownEnemyPosition.y}, { 2.f, 2.f });
				coins.push_back(coin);

				if (enemies[i].color == 1)
				{
					lastKnownEnemyPosition = sf::Vector2f({ enemies[i].sprite.getPosition().x + (enemies[i].sprite.getGlobalBounds().width / 2) - (coin.sprite.getGlobalBounds().width / 2), enemies[i].sprite.getPosition().y + (enemies[i].sprite.getGlobalBounds().height / 2) - (coin.sprite.getGlobalBounds().height / 2) });
					heart.create({ lastKnownEnemyPosition.x + 20, lastKnownEnemyPosition.y + 20 }, { 2.f, 2.f });
					hearts.push_back(heart);
					coin.create({ lastKnownEnemyPosition.x, lastKnownEnemyPosition.y }, { 2.f, 2.f });
					coins.push_back(coin);
				}
				//if (enemies[i].DIED) enemies.erase(enemies.begin() + i);
			}
		}
	}

	//if (enemies.empty() == true and IS_WAVE_ACTIVE) endWave();
}

void Game::initWave()
{
	for (int i = 0; i < 12; i++) 
	{
		if (i <= 5 and i == currentWave and IS_WAVE_ACTIVE) {
			enemies.clear();
			waveTimeResume = 0.0;
			createEnemies(i);
		}

		if (i >= 5 and i < 9 and i == currentWave and IS_WAVE_ACTIVE)
		{
			enemies.clear();
			waveTimeResume = 0.0;
			createEnemies(i-4);
		}

		if (i == 9 and i == currentWave and IS_WAVE_ACTIVE)
		{
			enemies.clear();
			waveTimeResume = 0.0;
			createEnemies(i - 5);
		}

		if (i == 10 and  i == currentWave and IS_WAVE_ACTIVE) 
		{
			enemies.clear();
			waveTimeResume = 0.0;
			createEnemies(i - 5);
		}

		if (i > 10 and i < 12 and i == currentWave and IS_WAVE_ACTIVE) 
		{
			enemies.clear();
			waveTimeResume = 0.0;
			createEnemies(i - 8);
		}
	}
}

void Game::endWave()
{
	std::random_device rd;										// obtain a random number from hardware
	std::mt19937 gen(rd());										// seed the generator
	std::uniform_int_distribution<> randX(370, 560);			// define the range
	std::uniform_int_distribution<> randY(240, 420);	

	savedWaveTime = waveTime;
	CZAS_ROZGRYWKI += waveTime;
	waveTime = 0;
	waveClock.restart();
	IS_WAVE_ACTIVE = false;

	std::cout << "KONIEC FALI" << '\n';

	savedWaveTime = (int)(savedWaveTime);

	if (savedWaveTime > 0 and savedWaveTime <= 10)
	{
		for (int i = 0; i < 13; i++)
		{
			float x = randX(gen);
			float y = randY(gen);
			shard.create({ x, y }, { 1.5f, 1.5f });
			shards.push_back(shard);
		}
	}

	if (savedWaveTime > 10 and savedWaveTime <= 30)
	{
		for (int i = 0; i < 11; i++)
		{
			float x = randX(gen);
			float y = randY(gen);
			shard.create({ x, y }, { 1.5f, 1.5f });
			shards.push_back(shard);
		}
	}

	if (savedWaveTime >= 30 and savedWaveTime <= 50)
	{
		for (int i = 0; i < 8; i++)
		{
			float x = randX(gen);
			float y = randY(gen);
			shard.create({ x, y }, { 1.5f, 1.5f });
			shards.push_back(shard);
		}
	}

	if (savedWaveTime > 50)
	{
		for (int i = 0; i < 4; i++)
		{
			float x = randX(gen);
			float y = randY(gen);
			shard.create({ x, y }, { 1.5f, 1.5f });
			shards.push_back(shard);
		}
	}


	//std::cout << "SHARDS VECTOR SIZE: " << shards.size() << '\n';
}

void Game::initShopDeals()
{
	Un_Sword.create({ 220.f, 300.f }, { 1.f, 1.f });
	Un_Armor.create({ 430.f, 165.f }, { 1.f, 1.f });
	Un_Potion.create({ 650.f, 300.f }, { 1.f, 1.f });
}
