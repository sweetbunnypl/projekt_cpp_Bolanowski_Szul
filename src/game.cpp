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

	// states
	this->PLAYING_STATE = false;
	this->IN_MENU_STATE = true;
	this->GAME_STOPPED = false;
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
					this->player.playerHealth = player.playerHealth - 1.f;
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
					showheart = true;
					break;

				}
			}

			// "G" MA DZIALAÆ ¯EBY PRZENIEŒÆ GRACZA DO SKLEPU
			if (player.playerSprite.getPosition().x > 400 and player.playerSprite.getPosition().x < 500 and player.playerSprite.getPosition().y > 63 and IN_STARTING_ROOM)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::G:
						std::cout << "TELEPORTACJA! WZIUUU..." << '\n';
						IN_STARTING_ROOM = false;
						IN_SHOP = true;

						std::cout << "IN STARTING ROOM: " << IN_STARTING_ROOM << '\n';
						std::cout << "IN_SHOP: " << IN_SHOP << '\n';
						
						PLAYER_TELEPORTATION = true;	
					}
				}
			}

			// I Z POWRTOEM....WZIUU
			if (player.playerSprite.getPosition().x > 400 and player.playerSprite.getPosition().x < 500 and player.playerSprite.getPosition().y > 534 and IN_SHOP)
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::G:
						std::cout << "TELEPORTACJA! WZIUUU..." << '\n';
						IN_STARTING_ROOM = true;
						IN_SHOP = false;

						std::cout << "IN STARTING ROOM: " <<  IN_STARTING_ROOM << '\n';
						std::cout << "IN_SHOP: " << IN_SHOP << '\n';

						PLAYER_TELEPORTATION = true;
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
		this->updatePlayerMovement();
		this->borders();
		this->animation();
	}
}

void Game::render()
{
	this->window->clear();

	// render (draw) objects below

	while (IN_MENU_STATE)
	{
		// after entering the playing state music stops so it plays
		// the music again when you go back to the menu
		if (this->menu_music.getStatus() == 0)
		{
			this->menu_music.play();
		}

		this->menuDrawMenu(this->window);
		this->window->display();
		this->update();
		break;
	}

	while (PLAYING_STATE)
	{
		menu_music.stop();

		// ustawienie, ze pokojem poczatkowym jest room1
		IN_STARTING_ROOM = true;

		while (IN_STARTING_ROOM)
		{
			this->window->clear(sf::Color(42, 33, 52, 255));
			this->room1.renderMap(this->window);
			this->room1.renderObject(this->window);
	
			if (showheart)
			{
				heart.create({ 390.f, 290.f }, { 3.f, 3.f });
				heart.render(this->window);
			}

			// ustawienie gracza w odpowiedniej pozycji po przejsciu do innego pokoju
			if (PLAYER_TELEPORTATION)
			{
				this->player.playerSprite.setPosition({ 440.f, 65.f });
				PLAYER_TELEPORTATION = false;
			}

			this->player.render(this->window);

			this->renderGUI(this->window);

			this->update();

			this->window->display();
		}

		while (IN_SHOP)
		{
			this->window->clear(sf::Color(42, 33, 52, 255));

			this->shop.renderMap(this->window);
			this->shop.renderObject(this->window);
			
			// ustawienie gracza w odpowiedniej pozycji po przejsciu do innego pokoju
			if (PLAYER_TELEPORTATION)
			{
				this->player.playerSprite.setPosition({ 440.f, 580.f });
				PLAYER_TELEPORTATION = false;
			}

			this->armorer.render(this->window);

			this->player.render(this->window);

			this->renderGUI(this->window);

			this->update();
			this->animation();

			this->window->display();
		}	
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
	this->MOOVING_UP = false;
	this->MOOVING_DOWN = false;
	this->MOOVING_RIGHT = false;
	this->MOOVING_LEFT = false;
	this->BEFORE_MOOVING = true;
	this->screenshotNumber = 0;

	this->armorer.create({ 250.f, 430.f }, { -3.f, 3.f });

	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

// GUI METHODS
void Game::initGUI()
{
	if (!this->guiTexture.loadFromFile("res/textures/gui.png"))
	{
		std::cout << "ERROR::GAME::initGUI::Could not load the GUI texture!" << "\n";
	}

	sf::Vector2f playerHealthBarPosition = sf::Vector2f( 980, 50);

	this->playerHealthBarEmpty.setTexture(this->guiTexture);
	this->playerHealthBarEmpty.setTextureRect(sf::IntRect(7, 11, 50, 8));
	this->playerHealthBarEmpty.setPosition(playerHealthBarPosition);
	this->playerHealthBarEmpty.setScale(4.5f, 4.5f);

	this->playerHealthBar.setTexture(this->guiTexture);
	this->playerHealthBar.setTextureRect(sf::IntRect(7, 1, 49 * this->player.playerHealth * 0.01, 8));
	this->playerHealthBar.setPosition(playerHealthBarPosition);
	this->playerHealthBar.setScale(4.5f, 4.5f);
}

void Game::renderGUI(sf::RenderTarget* target)
{
	initGUI();
	target->draw(this->playerHealthBarEmpty);
	target->draw(this->playerHealthBar);
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
	int dt = 30;
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
	// player position to console
	//std::cout << "X: " << player.playerSprite.getPosition().x << '\n';
	//std::cout << "Y: " << player.playerSprite.getPosition().y << '\n';

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		// moving up
		this->MOOVING_UP = true;
		this->BEFORE_MOOVING = false;
		this->player.playerSprite.move({ 0.f, -5.f });

		// collision with upper side of object
		for (int i = 0; i <= 52; i++)
		{
			if (this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()))
			{
				this->player.playerSprite.move({ 0.f, 5.f });	
			}
		}	
	}
	else
	{
		this->MOOVING_UP = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		// moving bottom
		this->MOOVING_DOWN = true;
		this->BEFORE_MOOVING = false;
		this->player.playerSprite.move({ 0.f, 5.f });

		// collision with bottom side of object
		for (int i = 0; i <= 52; i++)
		{
			if (this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()))
			{
				this->player.playerSprite.move({ 0.f, -5.f });
			}
		}	
	}
	else
	{
		this->MOOVING_DOWN = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		// moving left
		this->MOOVING_LEFT = true;
		this->BEFORE_MOOVING = false;
		this->player.playerSprite.move({ -5.f, 0.f });

		// collision with left side of object
		for (int i = 0; i <= 52; i++)
		{
			if (this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()))
			{
				this->player.playerSprite.move({ 5.f, 0.f });
			}
		}
	}
	else
	{
		this->MOOVING_LEFT = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		// moving right
		this->MOOVING_RIGHT = true;
		this->BEFORE_MOOVING = false;
		this->player.playerSprite.move({ 5.f, 0.f });

		// collision with right side of object
		for (int i = 0; i <= 52; i++)
		{
			if(this->room1.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->shop.object[i].getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()) or
				this->armorer.sprite.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()))
			{
				this->player.playerSprite.move({ -5.f, 0.f });
			}
		}
	}
	else
	{
		this->MOOVING_RIGHT = false;
	}

}

// COLLISION METHODS
// with window borders
void Game::borders()
{
	//std::cout << "x: " << player.playerSprite.getPosition().x << '\n';
	//std::cout << "y: " << player.playerSprite.getPosition().y << '\n';

	if (player.playerSprite.getPosition().x <= 0)
	{
		player.playerSprite.setPosition(0.f, player.playerSprite.getPosition().y);
	}

	if (player.playerSprite.getPosition().y <= 0)
	{
		player.playerSprite.setPosition(player.playerSprite.getPosition().x, 0);
	}

	if (player.playerSprite.getPosition().x + player.playerSprite.getGlobalBounds().width >= window->getSize().x)
	{
		player.playerSprite.setPosition(window->getSize().x - player.playerSprite.getGlobalBounds().width, player.playerSprite.getPosition().y);
	}

	if (player.playerSprite.getPosition().y + player.playerSprite.getGlobalBounds().height >= window->getSize().y)
	{
		player.playerSprite.setPosition(player.playerSprite.getPosition().x, window->getSize().y - player.playerSprite.getGlobalBounds().height);
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
			if (obj.liczba > 12 * 4)
			{
				this->obj.liczba -= 12 * 5;
				this->mnoznikStatic -= 5;
			}
			else
			{
				this->obj.liczba += 12;
				this->mnoznikStatic += 1;
			}

			//this->room1.shard.setTextureRect(sf::IntRect(map.liczba, 0, 12, 30));
			//this->room1.coin.setTextureRect(sf::IntRect(map.liczba, 0, 12, 17));
			//this->room1.key.setTextureRect(sf::IntRect(map.liczba, 0, 12, 21));
			//this->room1.heart.setTextureRect(sf::IntRect(map.liczba - mnoznikStatic, 0, 11, 16));

			heart.sprite.setTextureRect(sf::IntRect(obj.liczba - mnoznikStatic, 0, 11, 16));
		}

		if (IN_SHOP)
		{
			// STATIC ANIMATIONS COUNTER
			if (obj.liczba > 12 * 4)
			{
				this->obj.liczba -= 12 * 5;
				this->mnoznikStatic -= 5;
			}
			else
			{
				this->obj.liczba += 12;
				this->mnoznikStatic += 1;
			}

			// DYNAMIC ANIMATION
			if (player.liczba > 32)
			{
				this->player.liczba -= 32 * 2;
			}
			else
			{
				this->player.liczba += 32;
			}

			this->armorer.sprite.setTextureRect(sf::IntRect(player.liczba, 0, 32, 38));

			//this->shop.shard.setTextureRect(sf::IntRect(map.liczba, 0, 12, 30));
			//this->shop.coin.setTextureRect(sf::IntRect(map.liczba, 0, 12, 17));
			//this->shop.key.setTextureRect(sf::IntRect(map.liczba, 0, 12, 21));
			//this->shop.heart.setTextureRect(sf::IntRect(map.liczba - mnoznikStatic, 0, 11, 16));
		}
		

		// DYNAMIC ANIMATION
		if (player.liczba > 32)
		{
			this->player.liczba -= 32 * 2;
		}
		else
		{
			this->player.liczba += 32;
		}

		if (BEFORE_MOOVING)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			this->armorer.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		}
		if (MOOVING_DOWN)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.liczba, 0, 32, 32));
		}
		if (MOOVING_UP)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.liczba, 32 * 3, 32, 32));
		}

		if (MOOVING_LEFT)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.liczba, 32 * 1, 32, 32));
		}

		if (MOOVING_RIGHT)
		{
			this->player.playerSprite.setTextureRect(sf::IntRect(player.liczba, 32 * 2, 32, 32));
		}

		this->clock.restart();
	}
}

