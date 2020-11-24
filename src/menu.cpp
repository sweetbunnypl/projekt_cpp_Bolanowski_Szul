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
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
			text[i].setString(main_menu_txt[i]);
		}
		this->getButtons(MAX_NUMBER_OF_ITEMS);
		text[0].setString(main_menu_txt2[0]);
		text[0].setCharacterSize(90);
		text[0].setPosition(sf::Vector2f((width_window_test / 2) - (text[0].getGlobalBounds().width / 2), (height_window_test / (MAX_NUMBER_OF_ITEMS + 1)) - (text[0].getGlobalBounds().height / 2)));
	};

	//background do tekstu
	rectangle.setSize(sf::Vector2f(400, height_window_test));
	rectangle.setFillColor(sf::Color(0, 0, 0, 170));
	rectangle.setPosition(width_window_test / 2 - 200, 0);
}

Menu::~Menu()
{

}
/*
void Menu::run(sf::RenderWindow* window) {
	while (this->window->isOpen())
	{
		this->update();
		this->Menu::render();
	}
}

void Menu::render(sf::RenderWindow* window) {
	this->window->clear();
	this->draw();
	this->window->display();
}
*/
void Menu::getButtons(int i)
{
	for (int k = 0; k < i; k++)
	{
		text[k].setFont(font);
		text[k].setCharacterSize(70);
		text[k].setStyle(sf::Text::Regular);
		text[k].setFillColor(sf::Color::White);
		text[k].setPosition(sf::Vector2f((width_window_test / 2) - (text[k].getGlobalBounds().width / 2), (height_window_test / (i+1) * (k+1)) - (text[k].getGlobalBounds().height / 2)));

		//rectangle[k].setSize(sf::Vector2f(text[k].getGlobalBounds().width, text[k].getGlobalBounds().height));
		//rectangle[k].setOutlineColor(sf::Color::Red);
		//rectangle[k].setPosition(sf::Vector2f((width_window / 2) - (text[k].getGlobalBounds().width / 2), (height_window / (i + 1) * (k + 1)) - (text[k].getGlobalBounds().height / 2)));

		//float f = (height_window / (i + 1) * (k + 1)) - (text[k].getGlobalBounds().width / 2);
		//printf("%f; ", f);
		//printf("%f,%f; ", );
	}

}

//alternatywna funkcja do powyzszej
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
	printf("%d\n", pause);
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
			//menu->StartGame();
			break;
		case 1:
			printf("Ktos nacisnal Creators");
			MAIN_MENU = false;
			CREATORS = true;
			renderButtons2(creators_menu_txt, creators_menu_txt2);
			break;
		case 2:
			printf("Ktos nacisnal Help");
			MAIN_MENU = false;
			//CREATORS = false;
			HELP = true;
			break;
		case 3:
			window->close();
		default:
			break;
		}
	}
	if (not MAIN_MENU and CREATORS and not HELP) {
		switch (GetPressedItem())
		{
		case 0:
			printf("Ktos nacisnal Bolanowski");
			break;
		case 1:
			printf("Ktos nacisnal Szul");
			break;
		case 2:
			printf("Ktos nacisnal nic");
			break;
		case 3:
			MAIN_MENU = true;
			CREATORS = false;
			renderButtons2(main_menu_txt, main_menu_txt2);
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
