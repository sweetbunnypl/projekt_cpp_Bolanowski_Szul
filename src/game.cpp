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

void Game::initWindow()
{
	// all variables associated with window
	std::string title = "game project";
	sf::VideoMode windowBunds(windowWidth, windowHeight);
	this->window = new sf::RenderWindow(windowBunds, title, sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(30);

	// states
	this->playingState = false;
	this->inMenuState = true;
}

void Game::updateDeltaTime()
{
	// this->elapsedTime = this->dtClock.getElapsedTime().asSeconds();

	// updates the delta time variable with the time it takes to update and render one frame;
	this->deltaTime = this->dtClock.restart().asSeconds();

	// clears the console
	system("cls");
	std::cout << this->deltaTime << '\n';
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			window->close();
		}
		if (this->inMenuState)
		{
			switch (sfEvent.type)
			{
				// key pressed
			case sf::Event::KeyReleased:
				switch (sfEvent.key.code)
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
				// window closed
			case sf::Event::Closed:
				quit_sound.play();
				Sleep(500);
				this->window->close();
				break;
				// we don't process other types of events
			default:
				break;
			}

		}

	}
}

void Game::update()
{
	this->updateSFMLEvents();

	// update classes below
	if (this->playingState)
	{
		this->player.update(deltaTime);
		this->borders();
		this->collision();
	}
}

void Game::render()
{
	this->window->clear();

	// render (draw) objects here
	
	while (inMenuState)
	{
		this->menuDrawMenu(this->window);
		this->window->display();
		this->update();
		break;
	}

	while (playingState)
	{
		this->map.renderMap(this->window);
		this->map.renderObject(this->window);
		this->player.render(this->window);
		this->update();
		this->window->display();
	}
	// 

	//this->window->display();

}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}

void Game::initMenu()
{
	for (int i = 0; i <= 7; i++) {
		std::string path = "res/textures/gif/frame_" + std::to_string(i) + ".png";
		if (!gif_bcg[i].loadFromFile(path)) printf("nie wczytano chuja %d", i);
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
	menu_music.play();

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
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex--;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
	else if (not MAIN_MENU and CREATORS and not HELP) {
		if (MenuIndex - 1 >= 0) {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex--;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
}

void Game::menuMoveDown()
{
	change_sound.play();
	if (MAIN_MENU and not CREATORS and not HELP) {
		if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex++;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			menuCreateButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex = 0;
			menuCreateButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
	else if (not MAIN_MENU and CREATORS and not HELP) {
		if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex++;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			menuCreateButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
			MenuIndex = 0;
			menuCreateButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
}

void Game::menuRenderButtons(sf::RenderTarget* target)
{
	if (MAIN_MENU and not CREATORS and not HELP) {
		switch (menuGetPressedItem())
		{
		case 0:
			printf("Ktos nacisnal Play");
			enter_sound.play();
			this->inMenuState = false;
			this->playingState = true;
			break;
		case 1:
			printf("Ktos nacisnal Creators");
			enter_sound.play();
			MAIN_MENU = false;
			CREATORS = true;
			menuRenderButtons2(creators_menu_txt, creators_menu_txt2);
			break;
		case 2:
			printf("Ktos nacisnal Help");
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
			printf("Ktos nacisnal Bolanowski");
			enter_sound.play();
			//link otwiera sie tylko pod windowsem
			system("start https://github.com/sweetbunnypl/");
			break;
		case 1:
			printf("Ktos nacisnal Szul");
			enter_sound.play();
			//link otwiera sie tylko pod windowsem
			system("start https://github.com/SonOfGrabarz");
			break;
		case 2:
			printf("Ktos nacisnal nic");
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
	menuCreateButton(menu_string2[0], 0, MAX_NUMBER_OF_ITEMS, 82);
	menuCreateButton(menu_string[1], 1, MAX_NUMBER_OF_ITEMS, 82);
	menuCreateButton(menu_string[2], 2, MAX_NUMBER_OF_ITEMS, 82);
	menuCreateButton(menu_string[3], 3, MAX_NUMBER_OF_ITEMS, 82);
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

void Game::borders()
{
	std::cout << "X: " << player.playerSprite.getPosition().x << '\n';
	std::cout << "Y: " << player.playerSprite.getPosition().y << '\n';

	if (player.playerSprite.getPosition().x <= 0)
	{
		std::cout << "jeblo z lewej" << '\n';
		player.playerSprite.setPosition(0.f, player.playerSprite.getPosition().y);
	}

	if (player.playerSprite.getPosition().y <= 0)
	{
		std::cout << "jeblo z gory" << '\n';
		player.playerSprite.setPosition(player.playerSprite.getPosition().x, 0);
	}

	if (player.playerSprite.getPosition().x + player.playerSprite.getGlobalBounds().width >= window->getSize().x)
	{
		std::cout << "jeblo z prawej" << '\n';
		player.playerSprite.setPosition(window->getSize().x - player.playerSprite.getGlobalBounds().width, player.playerSprite.getPosition().y);
	}

	if (player.playerSprite.getPosition().y + player.playerSprite.getGlobalBounds().height >= window->getSize().y)
	{
		std::cout << "jeblo z dolu" << '\n';
		player.playerSprite.setPosition(player.playerSprite.getPosition().x, window->getSize().y - player.playerSprite.getGlobalBounds().height);
	}
}

void Game::collision()
{
	if (this->map.object.getGlobalBounds().intersects(this->player.playerSprite.getGlobalBounds()))
	{
		std::cout << "MPK znowu jeblo" << '\n';
	}
}



