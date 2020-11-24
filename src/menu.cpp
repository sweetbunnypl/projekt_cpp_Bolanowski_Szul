#include "menu.h"
#include "game.h"

Menu::Menu(float width_window, float height_window) 
{
	//sf::Texture gif_bcg[7];
	//sf::Sprite gif_bcg_s[7];
	for (int i = 0; i <= 7; i++) {
		std::string path = "res/textures/gif/frame_"+std::to_string(i)+".png";
		if (!gif_bcg[i].loadFromFile(path)) printf("nie wczytano t³a %d", i);
		gif_bcg_s[i].setTexture(gif_bcg[i]);
		gif_bcg_s[i].setScale(2.5, 2.5);
		//gif_bcg_s[i].setPosition(sf::Vector2f((width_window_test / 2) - (gif_bcg[i].getSize().x / 2), (height_window_test / 2) - (gif_bcg[i].getSize().y / 2)));
		//gif_bcg_s[i].setTextureRect(sf::IntRect(0, 0, 1000, 1000));
	};

	if (!font.loadFromFile("res/fonts/ostrich-regular.ttf")) printf("nie wczytalo czcionki");
	else {
		//if(play_pressed):
			//...GAME START
		MAIN_MENU = true;
		CREATORS = false;
		HELP = false;
		renderButtons2(main_menu_txt, main_menu_txt2);
	};

	//background do tekstu
	rectangle.setSize(sf::Vector2f(400, height_window_test));
	rectangle.setFillColor(sf::Color(0, 0, 0, 170));
	rectangle.setPosition(width_window_test / 2 - 200, 0);

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

Menu::~Menu()
{
	menu_music.stop();
}

void Menu::createButton(std::string button_name, int which, int of_how_many, int font_size = 70) {
	text[which].setFont(font);
	text[which].setCharacterSize(font_size);
	text[which].setStyle(sf::Text::Regular);
	text[which].setFillColor(sf::Color::White);
	text[which].setString(button_name);
	text[which].setPosition(sf::Vector2f((width_window_test / 2) - (text[which].getGlobalBounds().width / 2), (height_window_test / (of_how_many+1) * (which+1)) - (text[which].getGlobalBounds().height / 2)));
}

void Menu::drawMenu(sf::RenderWindow* window)
{
	pause++;
	//printf("%d\n", pause);
	int dt = 30;
	if (pause < dt) window->draw(gif_bcg_s[0]);
	else if (pause < dt*2 and pause >= dt) window->draw(gif_bcg_s[1]);
	else if (pause < dt*3 and pause >= dt*2) window->draw(gif_bcg_s[2]);
	else if (pause < dt*4 and pause >= dt*3) window->draw(gif_bcg_s[3]);
	else if (pause < dt*5 and pause >= dt*4) window->draw(gif_bcg_s[4]);
	else if (pause < dt*6 and pause >= dt*5) window->draw(gif_bcg_s[5]);
	else if (pause < dt*7 and pause >= dt*6) window->draw(gif_bcg_s[6]);
	else if (pause < dt*8 and pause >= dt*7) window->draw(gif_bcg_s[7]);
	else {
		pause = 0;
		window->draw(gif_bcg_s[0]);
	}

	window->draw(rectangle);

	//window->draw(bcg_s);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) 
	{
		//window->draw(rectangle[i]);
		window->draw(text[i]);
		//.draw(text[i]);
	}
}

//R U C H
void Menu::MoveUp() {
	change_sound.play();
	if (MAIN_MENU and not CREATORS and not HELP) {
		if (MenuIndex - 1 >= 0) {
			createButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex--;
			createButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			createButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
			createButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
	else if (not MAIN_MENU and CREATORS and not HELP) {
		if (MenuIndex - 1 >= 0) {
			createButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex--;
			createButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			createButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
			createButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
}

void Menu::MoveDown() {
	change_sound.play();
	if (MAIN_MENU and not CREATORS and not HELP) {
		if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			createButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex++;
			createButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			createButton(main_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex = 0;
			createButton(main_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
	else if (not MAIN_MENU and CREATORS and not HELP) {
		if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
			createButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex++;
			createButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
		else {
			createButton(creators_menu_txt[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS);
			MenuIndex = 0;
			createButton(creators_menu_txt2[MenuIndex], MenuIndex, MAX_NUMBER_OF_ITEMS, 82);
		}
	}
}

void Menu::renderButtons(sf::RenderWindow* window) {
	if (MAIN_MENU and not CREATORS and not HELP) {
		switch (GetPressedItem())
		{
		case 0:
			printf("Ktos nacisnal Play");
			enter_sound.play();
			//menu->StartGame();
			break;
		case 1:
			printf("Ktos nacisnal Creators");
			enter_sound.play();
			MAIN_MENU = false;
			CREATORS = true;
			renderButtons2(creators_menu_txt, creators_menu_txt2);
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
		switch (GetPressedItem())
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
			renderButtons2(main_menu_txt, main_menu_txt2);
			quit_sound.play();
		default:
			break;
		}
	}
}

void Menu::renderButtons2(std::string menu_string[MAX_NUMBER_OF_ITEMS], std::string menu_string2[MAX_NUMBER_OF_ITEMS]) {
	MenuIndex = 0;
	createButton(menu_string2[0], 0, MAX_NUMBER_OF_ITEMS, 82);
	createButton(menu_string[1], 1, MAX_NUMBER_OF_ITEMS);
	createButton(menu_string[2], 2, MAX_NUMBER_OF_ITEMS);
	createButton(menu_string[3], 3, MAX_NUMBER_OF_ITEMS);
	
}

/*
void Menu::update(sf::RenderWindow* window) {
	this->updateSFMLevents();
}


void Menu::updateSFMLevents() {
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
			// key pressed
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp();
				printf("m_u");
				break;

			case sf::Keyboard::Down:
				MoveDown();
				printf("m_d");
				break;

			case sf::Keyboard::Return:
				switch (MenuIndex)
				{
				case 0:
					printf("Ktos nacisnal Play");
					break;
				case 1:
					printf("Ktos nacisnal Options");
					break;
				case 2:
					printf("Ktos nacisnal Creators");
					break;
				case 3:
					this->window->close();
				default:
					break;
				}
			}
			break;
			// window closed
		case sf::Event::Closed:
			this->window->close();
			break;
			// we don't process other types of events
		default:
			break;
		}
	}
}
*/
