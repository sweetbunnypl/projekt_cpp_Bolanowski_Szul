#include "game.h"

Game::Game()
{
	this->initWindow();
	this->initMenu();
}

Game::~Game()
{
	delete this->window;
}

// GAME METHODS
void Game::initWindow()
{
	// all variables associated with window
	std::string title = "WERSJA PRE-ALPHA";
	sf::VideoMode windowBunds(windowWidth, windowHeight);
	this->window = new sf::RenderWindow(windowBunds, title, sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(30);
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event))
	{
		// HANDLING WINDOW ACTIONS
		if (this->event.type == sf::Event::Closed)
		{
			window->close();
		}

		// HANDLING KEY PRESSING IN MENU
		if (this->IN_MENU_STATE and this->PLAYING_STATE == false)
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
		if (this->IN_MENU_STATE == false and this->PLAYING_STATE)
		{
			//std::cout << player.playerSprite.getPosition().y << std::endl;
			switch (event.type)
			{
				// key pressed
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Backspace:
					PLAYING_STATE = false;
					IN_MENU_STATE = false;
					GAME_STOPPED = true;
					break;

				case sf::Keyboard::K:
					//this->player.playerHealth = player.playerHealth - 1.f;
					break;

				case sf::Keyboard::Escape:
					quit_sound.play();
					Sleep(500);
					this->window->close();
					break;
				
				case sf::Keyboard::C:
					screenshotNumber += 1;
					std::string filename_core = "SCREENSHOT_";
					std::string filename_number = std::to_string(screenshotNumber);
					std::string filename_path = "files/";
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
						this->PLAYER_MOOVING_RIGHT = false;
						this->PLAYER_MOOVING_LEFT = false;
						this->PLAYER_IDLE = false;
						this->PLAYER_IS_ATTACKING = true;
						
						std::cout << "PRZYCZAJONY TYGRYS, UKRYTY SMOK!" << '\n';
						this->updatePlayerAttack();
					}
				}
			}

			// "G" MA DZIALAÆ ¯EBY PRZENIEŒÆ GRACZA DO SKLEPU
			if (player.playerSprite.getPosition().x > 400 and player.playerSprite.getPosition().x < 500 and player.playerSprite.getPosition().y < 70 and IN_STARTING_ROOM and !IS_WAVE_ACTIVE)
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
						this->player.playerSprite.setPosition({ 440.f, 580.f });
					}
				}
			}
			// I Z POWRTOEM....WZIUU
			else if (player.playerSprite.getPosition().x > 400 and player.playerSprite.getPosition().x < 500 and player.playerSprite.getPosition().y > 534 and IN_SHOP and !IS_WAVE_ACTIVE)
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
						this->player.playerSprite.setPosition({ 440.f, 65.f });
					}
				}
			}
			// START FALI
			else if (player.playerSprite.getPosition().x > 400 and player.playerSprite.getPosition().x < 500 and player.playerSprite.getPosition().y > 534 and IN_STARTING_ROOM)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::G:
						if (!IS_WAVE_ACTIVE){
							std::cout << "CZAS NA FALE" << '\n';
							current_wave++;
							IS_WAVE_ACTIVE = true;
							initWave();
							this->waveClock.restart();
						}
					}
				}
			}
		}

		if (this->GAME_STOPPED)
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
					PLAYING_STATE = true;
					IN_MENU_STATE = false;
					GAME_STOPPED = false;
					std::cout << "WZNOWIENIE GRY" << '\n';
					break;

				case sf::Keyboard::Escape:
					quit_sound.play();
					Sleep(500);
					this->window->close();
					break;
				}
			}
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	// update classes below
	if (this->PLAYING_STATE)
	{
		if (IS_WAVE_ACTIVE) 
		{
			this->updateEnemyMovement();
			this->waveTime = (int)(this->waveClock.getElapsedTime().asSeconds() * 100 + .5);
			this->waveTime = waveTime / 100;
		}

		this->updatePlayerMovement();
		this->animation();
		this->pickingUpObjects();
		this->levelingUp();
		this->gui.changeValues(this->player.coins, this->player.keys, this->player.level, this->current_wave, this->waveTime);
	}
}

void Game::render()
{
	this->window->clear();

	// render (draw) objects below

	while (IN_MENU_STATE)
	{
		this->newGame();

		// after entering the playing state music stops so it plays
		// the music again when you go back to the menu
		if (this->menu_music.getStatus() == 0)
		{
			this->menu_music.play();
		}

		this->menuDrawMenu(this->window);
		this->window->display();
		this->update();
		IN_STARTING_ROOM = true;

		break;
	}

	while (PLAYING_STATE and IN_STARTING_ROOM)
	{
		menu_music.stop();

		this->window->clear(sf::Color(42, 33, 52, 255));
		this->room1.renderMap(this->window);
		this->room1.renderObject(this->window);

		if (IS_WAVE_ACTIVE) 
		{
			/*for (int i = 0; i < this->enemies.size(); i++)
			{
				this->enemies[i].renderRadius(this->window);
			}*/
			for(int i = 0; i < this->enemies.size(); i++)
			{
				this->enemies[i].render(this->window);
			}
		}

		if (coins.empty() == false)
		{
			for (int i = 0; i < this->coins.size(); i++)
			{
				this->coins[i].render(this->window);
			}
		}
		if (shards.empty() == false)
		{
			for (int i = 0; i < this->shards.size(); i++)
			{
				this->shards[i].render(this->window);
			}
		}

		bonfire.create({ 435.f, 562.f }, { 1.2f, 1.2f });
		bonfire.render(this->window);

		this->gui.render(this->window);
		this->player.render(this->window);

		this->update();
		this->window->display();
	}

	while (PLAYING_STATE and IN_SHOP)
	{
		this->window->clear(sf::Color(42, 33, 52, 255));

		this->shop.renderMap(this->window);
		this->shop.renderObject(this->window);
		this->gui.render(this->window);
		this->player.render(this->window);

		this->update();
		this->window->display();
	}

	while (GAME_STOPPED)
	{	
		this->testText.setFont(this->font);
		this->testText.setCharacterSize(40);
		this->testText.setFillColor(sf::Color::White);
		this->testText.setOutlineColor(sf::Color::Black);
		this->testText.setOutlineThickness(2);
		this->testText.setStyle(sf::Text::Bold);
		this->testText.setString("> Click R to RESUME or Q to go back to the MENU <");
		this->testText.setPosition(300.f, 300.f);
		this->window->draw(this->testText);

		this->update();
		this->window->display();
	}
}

void Game::run()
{
	// variables that should be defined once before game start
	// game states
	this->PLAYING_STATE = false;
	this->IN_MENU_STATE = true;
	this->GAME_STOPPED = false;
	// starting animation is idle animation
	this->PLAYER_MOOVING_RIGHT = false;
	this->PLAYER_MOOVING_LEFT = false;
	this->PLAYER_IDLE = true;
	// screenshot iterable
	this->screenshotNumber = 0;

	this->armorer.create({ 250.f, 430.f }, { -3.f, 3.f });

	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::newGame()
{
	this->waveTime = 0.0;

	this->player.coins = 0;
	this->player.keys = 0;
	this->player.xp = 0;

	this->player.drunk = false;

	this->player.level = 1;
	this->player.hp = 100;
	this->player.speed = 1;
	this->player.poisoning = 1;
	this->player.dmg = 1;
	this->player.def = 1;
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
	rectangle.setSize(sf::Vector2f(400, this->windowHeight));
	rectangle.setFillColor(sf::Color(0, 0, 0, 170));
	rectangle.setPosition(this->windowWidth / 2 - 200, 0);

	//muzyka w menu
	if (!menu_music.openFromFile("res/sounds/menu_music.ogg")) {
		printf("nie wczytano menu_music.ogg");
	}
	//odtworzenie muzyki
	menu_music.setLoop(true);
	//menu_music.play();

	//wczytywanie change
	if (!change_buffer.loadFromFile("res/sounds/menu_change.wav")) {
		printf("nie wczytano menu_change.wav");
	}
	change_sound.setBuffer(change_buffer);
	//change_sound.play();

	//wczytywanie enter
	if (!enter_buffer.loadFromFile("res/sounds/menu_enter.wav")) {
		printf("nie wczytano menu_change.wav");
	}
	enter_sound.setBuffer(enter_buffer);
	//enter_sound.play();

	//wczytywanie quit
	if (!quit_buffer.loadFromFile("res/sounds/menu_quit.wav")) {
		printf("nie wczytano menu_change.wav");
	}
	quit_sound.setBuffer(quit_buffer);
	//quit_sound.play();
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
}

void Game::menuRenderButtons(sf::RenderTarget* target)
{
	if (MAIN_MENU and not CREATORS and not HELP) {
		switch (menuGetPressedItem())
		{
		case 0:
			std::cout << "Ktos nacisnal Play" << '\n';
			enter_sound.play();
			this->IN_MENU_STATE = false;
			this->PLAYING_STATE = true;
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
			//CREATORS = false;
			HELP = true;
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
			std::cout << "Ktos nacisnal nic" << '\n';
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
}

void Game::menuRenderButtons2(std::string menu_string[MAX_NUMBER_OF_ITEMS], std::string menu_string2[MAX_NUMBER_OF_ITEMS])
{
	MenuIndex = 0;
	menuCreateButton(menu_string2[0], 0, MAX_NUMBER_OF_ITEMS, 80);
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
	text[which].setPosition(sf::Vector2f((this->windowWidth / 2) - (text[which].getGlobalBounds().width / 2), (this->windowHeight / (of_how_many + 1) * (which + 1)) - (text[which].getGlobalBounds().height / 2)));
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
	// player position -> console
	//std::cout << "X: " << player.playerSprite.getPosition().x << '\n';
	//std::cout << "Y: " << player.playerSprite.getPosition().y << '\n';

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		// moving up
		this->player.playerSprite.move({ 0.f, -5.f });

		// collision with upper side of object
		for (int i = 0; i <= 52; i++)
		{
			if (this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				(this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) and IN_SHOP))
			{
				this->player.playerSprite.move({ 0.f, 5.f });	
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
		this->player.playerSprite.move({ 0.f, 5.f });

		// collision with bottom side of object
		for (int i = 0; i <= 52; i++)
		{
			if (this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				(this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) and IN_SHOP))
			{
				this->player.playerSprite.move({ 0.f, -5.f });
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
		this->PLAYER_MOOVING_LEFT = true;
		this->PLAYER_IDLE = false;
		this->player.playerSprite.move({ -5.f, 0.f });

		// collision with left side of object
		for (int i = 0; i <= 52; i++)
		{
			if (this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				(this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) and IN_SHOP))
			{
				this->player.playerSprite.move({ 5.f, 0.f });
			}
		}
	}
	else
	{
		this->PLAYER_MOOVING_LEFT = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		// moving right
		this->PLAYER_MOOVING_RIGHT = true;
		this->PLAYER_IDLE = false;
		this->player.playerSprite.move({ 5.f, 0.f });

		// collision with right side of object
		for (int i = 0; i <= 52; i++)
		{
			if(this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				(this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) and IN_SHOP))
			{
				this->player.playerSprite.move({ -5.f, 0.f });
			}
		}
	}
	else
	{
		this->PLAYER_MOOVING_RIGHT = false;
	}
}

void Game::pickingUpObjects()
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (coins.empty() == false)
		{
			if (this->player.playerSprite.getGlobalBounds().intersects(this->coins[i].sprite.getGlobalBounds()))
			{
				this->player.coins += 1;
				this->coins.erase(coins.begin() + i);
			}
		}
		
	}
	for (int i = 0; i < shards.size(); i++)
	{
		if(shards.empty() == false)
		{
			if (this->player.playerSprite.getGlobalBounds().intersects(this->shards[i].sprite.getGlobalBounds()))
			{
				this->player.xp += 2;
				this->shards.erase(shards.begin() + i);
				std::cout << "XP: " << player.xp << '\n';
			}
		}
	}
}

void Game::levelingUp()
{
	int xpRequired;

	if (player.level > 0 and player.level <= 15)
	{
		xpRequired = 2 * player.level + 7;

		if (player.xp >= xpRequired)
		{
			player.level += 1;
			player.xp = 0;
		}
	}

	if (player.level > 15 and player.level <= 30)
	{
		xpRequired = 5 * player.level - 38;

		if (player.xp >= xpRequired)
		{
			player.level += 1;
			player.xp = 0;
		}
	}

	if (player.level > 30)
	{
		xpRequired = 9 * player.level - 158;

		if (player.xp >= xpRequired)
		{
			player.level += 1;
			player.xp = 0;
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
			this->player.frame = 0;
		}
		else
		{
			this->player.frame += 64;
		}

		if (PLAYER_IDLE and PLAYER_FACING_RIGHT == false)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.frame, 128, 64, 64));
		}

		if (PLAYER_IDLE and PLAYER_FACING_RIGHT)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.frame, 192, 64, 64));
		}

		if (PLAYER_MOOVING_LEFT)
		{	
			this->PLAYER_FACING_RIGHT = false;
			this->player.playerSprite.setTextureRect(sf::IntRect(player.frame, 0, 64, 64));
		}

		if (PLAYER_MOOVING_RIGHT)
		{
			this->PLAYER_FACING_RIGHT = true;
			this->player.playerSprite.setTextureRect(sf::IntRect(player.frame, 64, 64, 64));
		}

		// PLAYER ATTACKING ANIMATION
		if (player.attackFrame > 720 and PLAYER_IS_ATTACKING)
		{
			this->player.attackFrame = 0;

			if (PLAYER_IS_ATTACKING)
			{
				this->PLAYER_IS_ATTACKING = false;
				this->PLAYER_IDLE = true;
			}	
		}
		else if (player.attackFrame <= 720 and PLAYER_IS_ATTACKING)
		{
			this->player.attackFrame += 120;
		}

		if (PLAYER_IS_ATTACKING and PLAYER_FACING_RIGHT == false)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.attackFrame, 256, 120, 76));
		}
		else if (PLAYER_IS_ATTACKING and PLAYER_FACING_RIGHT)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.attackFrame, 332, 120, 76));
		}

		this->clock.restart();
	}
}

void Game::animationEnemy()
{
}

void Game::createEnemies(int ile_enemy)
{
	for(int i = 0; i < ile_enemy; i++)
	{
		this->enemy.create(sf::Vector2f(100+100*i, 100), sf::Vector2f(1, 1), sf::Vector2f(3, 3));
		this->enemies.push_back(this->enemy);
	}
}

void Game::updateEnemyMovement()
{
	sf::Vector2f gracz_size = sf::Vector2f(player.playerSprite.getGlobalBounds().width, player.playerSprite.getGlobalBounds().height);
	sf::Vector2f gracz = sf::Vector2f(player.playerSprite.getPosition().x + gracz_size.x/2, player.playerSprite.getPosition().y + gracz_size.y/2);
	for (int i = 0; i < this->enemies.size(); i++)
	{
		sf::Vector2f przeciwnik = sf::Vector2f(enemies[i].terror.getPosition().x + enemies[i].terrorRadius, enemies[i].terror.getPosition().y + enemies[i].terrorRadius);
		float dystans = sqrt(pow((przeciwnik.x - gracz.x), 2) + pow((przeciwnik.y - gracz.y), 2));

		if (!this->player.playerSprite.getGlobalBounds().intersects(this->enemies[i].enemySprite.getGlobalBounds()) and dystans < enemies[i].terrorRadius)
		{
			if (gracz.x > przeciwnik.x)
			{
				this->enemies[i].enemySprite.move(sf::Vector2f(this->enemy.speed.x, 0.f));
				this->enemies[i].terror.move(sf::Vector2f(this->enemy.speed.x, 0.f));
				this->enemies[i].attack.move(sf::Vector2f(this->enemy.speed.x, 0.f));
				//this->enemies[i].txtHealth.move(sf::Vector2f(this->enemy.speed.x, 0.f));
			}

			else if (gracz.x < przeciwnik.x)
			{
				this->enemies[i].enemySprite.move(sf::Vector2f(-this->enemy.speed.x, 0.f));
				this->enemies[i].terror.move(sf::Vector2f(-this->enemy.speed.x, 0.f));
				this->enemies[i].attack.move(sf::Vector2f(-this->enemy.speed.x, 0.f));
				//this->enemies[i].txtHealth.move(sf::Vector2f(-this->enemy.speed.x, 0.f));
			}

			if (gracz.y > przeciwnik.y)
			{
				this->enemies[i].enemySprite.move(sf::Vector2f(0.f, this->enemy.speed.x));
				this->enemies[i].terror.move(sf::Vector2f(0.f, this->enemy.speed.x));
				this->enemies[i].attack.move(sf::Vector2f(0.f, this->enemy.speed.x));
				//this->enemies[i].txtHealth.move(sf::Vector2f(0.f, this->enemy.speed.x));
			}

			else if (gracz.y < przeciwnik.y)
			{
				this->enemies[i].enemySprite.move(sf::Vector2f(0.f, -this->enemy.speed.x));
				this->enemies[i].terror.move(sf::Vector2f(0.f, -this->enemy.speed.x));
				this->enemies[i].attack.move(sf::Vector2f(0.f, -this->enemy.speed.x));
				//this->enemies[i].txtHealth.move(sf::Vector2f(0.f, -this->enemy.speed.x));
			}
			//this->enemies[i].txtHealth.setPosition(enemies[i].enemySprite.getPosition().x+(enemies[i].enemySprite.getGlobalBounds().width/2)-enemies[i].txtHealth.getGlobalBounds().width/2, enemies[i].enemySprite.getPosition().y+(enemies[i].enemySprite.getGlobalBounds().height/2)-(enemies[i].txtHealth.getGlobalBounds().height/2)-40);
			//this->enemies[i].txtHealth.setPosition(enemies[i].enemySprite.getPosition().x, enemies[i].enemySprite.getPosition().y-50);
		}
	}
}

void Game::updateEnemyAttack()
{
	sf::Vector2f gracz_size = sf::Vector2f(player.playerSprite.getGlobalBounds().width, player.playerSprite.getGlobalBounds().height);
	sf::Vector2f gracz = sf::Vector2f(player.playerSprite.getPosition().x + gracz_size.x / 2, player.playerSprite.getPosition().y + gracz_size.y / 2);
	for (int i = 0; i < this->enemies.size(); i++)
	{
		sf::Vector2f przeciwnik = sf::Vector2f(enemies[i].attack.getPosition().x + enemies[i].attackRadius, enemies[i].attack.getPosition().y + enemies[i].attackRadius);
		float dystans = sqrt(pow((przeciwnik.x - gracz.x), 2) + pow((przeciwnik.y - gracz.y), 2));
		//std::cout << dystans << "   " << przeciwnik.x << "   " << przeciwnik.y << std::endl;
		if (dystans < enemies[i].attackRadius)
		{
			enemies[i].health = enemies[i].health - 5;
			std::cout << "hit! health remaining: " << enemies[i].health << std::endl;
			this->enemies[i].txtHealth.setPosition(enemies[i].enemySprite.getPosition().x+(enemies[i].enemySprite.getGlobalBounds().width/2)-enemies[i].txtHealth.getGlobalBounds().width/2, enemies[i].enemySprite.getPosition().y+(enemies[i].enemySprite.getGlobalBounds().height/2)-(enemies[i].txtHealth.getGlobalBounds().height/2)-40);
			enemies[i].updateHealth(enemies[i].health);
			if (enemies[i].health <= 0) 
			{
				enemies.erase(enemies.begin() + i);
			}
		}
	}
}

void Game::updatePlayerAttack()
{
	sf::Vector2f gracz_size = sf::Vector2f(player.playerSprite.getGlobalBounds().width, player.playerSprite.getGlobalBounds().height);
	sf::Vector2f gracz = sf::Vector2f(player.playerSprite.getPosition().x + gracz_size.x / 2, player.playerSprite.getPosition().y + gracz_size.y / 2);
	for (int i = 0; i < this->enemies.size(); i++)
	{
		sf::Vector2f przeciwnik = sf::Vector2f(enemies[i].attack.getPosition().x + enemies[i].attackRadius, enemies[i].attack.getPosition().y + enemies[i].attackRadius);
		float dystans = sqrt(pow((przeciwnik.x - gracz.x), 2) + pow((przeciwnik.y - gracz.y), 2));

		if (dystans < enemies[i].attackRadius)
		{
			enemies[i].health = enemies[i].health - 35;
			std::cout << i << "# enemy got hit! health remaining: " << enemies[i].health << std::endl;
			enemies[i].updateHealth(enemies[i].health);

			if (enemies[i].health <= 0)
			{	
				lastKnownEnemyPosition = sf::Vector2f({ this->enemies[i].enemySprite.getPosition().x, this->enemies[i].enemySprite.getPosition().y });
				std::cout << "LastKnownEnemyPosition X: " << this->enemies[i].enemySprite.getPosition().x << " Y: " << this->enemies[i].enemySprite.getPosition().y << '\n';
				coin.create({ lastKnownEnemyPosition.x + 10, lastKnownEnemyPosition.y - 10 }, { 0.5f, 0.5f });
				coins.push_back(this->coin);

				heart.create({ lastKnownEnemyPosition.x + 20, lastKnownEnemyPosition.y + 20 }, { 0.5f, 0.5f });
				hearts.push_back(this->heart);

				key.create({ lastKnownEnemyPosition.x - 30, lastKnownEnemyPosition.y + 20 }, { 0.5f, 0.5f });
				keys.push_back(this->key);

				enemies.erase(enemies.begin() + i);
			}
		}
	}

	if (enemies.empty() == true) endWave();
}

void Game::initWave()
{
	if (IS_WAVE_ACTIVE and current_wave == 1)
	{
		enemies.clear();
		createEnemies(2);
	}
	else if (IS_WAVE_ACTIVE and current_wave == 2)
	{
		enemies.clear();
		createEnemies(3);
	}
	else if (IS_WAVE_ACTIVE and current_wave == 3)
	{
		enemies.clear();
		createEnemies(5);
	}
}

void Game::endWave()
{
	this->savedWaveTime = waveTime;
	this->waveTime = 0;
	this->waveClock.restart();
	IS_WAVE_ACTIVE = false;

	
	std::cout << "KONIEC FALI" << '\n';

	savedWaveTime = (int)(savedWaveTime);

	if (savedWaveTime > 0 and savedWaveTime <= 10)
	{
		for (int i = 0; i < 10; i++)
		{
			shard.create({ 400.f + 10 * i, 400.f + 10 * i }, { 0.5f, 0.5f });
			shards.push_back(this->shard);
		}
	}

	if (savedWaveTime > 10 and savedWaveTime <= 25)
	{
		for (int i = 0; i < 6; i++)
		{
			shard.create({ 400.f + 10 * i, 400.f + 10 * i }, { 0.5f, 0.5f });
			shards.push_back(this->shard);
		}
	}

	if (savedWaveTime >= 25 and savedWaveTime <= 40)
	{
		for (int i = 0; i < 4; i++)
		{
			shard.create({ 400.f + 10 * i, 400.f + 10 * i }, { 0.5f, 0.5f });
			shards.push_back(this->shard);
		}
	}

	if (savedWaveTime > 40)
	{
		for (int i = 0; i < 2; i++)
		{
			shard.create({ 400.f + 10 * i, 400.f + 10 * i }, { 0.5f, 0.5f });
			shards.push_back(this->shard);
		}
	}

	std::cout << "SHARDS VECTOR SIZE: " << shards.size() << '\n';
}
