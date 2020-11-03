#include "menu.h"
#include "game.h"

Menu::Menu(float width_window, float height_window) {
	if (!font.loadFromFile("res/fonts/ostrich-regular.ttf")) printf("nie wczytalo czcionki");
	else {
		printf("wczytalo czcionke!");
		text[0].setFont(font);
		text[0].setFillColor(sf::Color::White);
		text[0].setString("PLAY");
		text[0].setPosition(sf::Vector2f((width_window / 2) - (text[0].getGlobalBounds().width / 2), (height_window / (MAX_NUMBER_OF_ITEMS + 1) * 1) - (text[0].getGlobalBounds().width / 2)));

		text[1].setFont(font);
		text[1].setFillColor(sf::Color::Red);
		text[1].setString("OPTIONS");
		text[1].setPosition(sf::Vector2f((width_window / 2) - (text[1].getGlobalBounds().width / 2), (height_window / (MAX_NUMBER_OF_ITEMS + 1) * 2) - (text[1].getGlobalBounds().width / 2)));

		text[2].setFont(font);
		text[2].setFillColor(sf::Color::Red);
		text[2].setString("CREATORS");
		text[2].setPosition(sf::Vector2f((width_window / 2) - (text[2].getGlobalBounds().width / 2), (height_window / (MAX_NUMBER_OF_ITEMS + 1) * 3) - (text[2].getGlobalBounds().width / 2)));

		text[3].setFont(font);
		text[3].setFillColor(sf::Color::Red);
		text[3].setString("EXIT");
		text[3].setPosition(sf::Vector2f((width_window / 2) - (text[3].getGlobalBounds().width / 2), (height_window / (MAX_NUMBER_OF_ITEMS + 1) * 4) - (text[3].getGlobalBounds().width / 2)));
	};
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
void Menu::drawMenu(sf::RenderWindow* window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) 
	{
		window->draw(text[i]);
		//.draw(text[i]);
	}
}

//R U C H
void Menu::MoveUp() {
	if (MenuIndex - 1 >= 0) {
		text[MenuIndex].setFillColor(sf::Color::Red);
		MenuIndex--;
		text[MenuIndex].setFillColor(sf::Color::White);
	}
	else {
		text[MenuIndex].setFillColor(sf::Color::Red);
		MenuIndex = MAX_NUMBER_OF_ITEMS - 1;
		text[MenuIndex].setFillColor(sf::Color::White);
	}
}

void Menu::MoveDown() {
	if (MenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		text[MenuIndex].setFillColor(sf::Color::Red);
		MenuIndex++;
		text[MenuIndex].setFillColor(sf::Color::White);
	}
	else {
		text[MenuIndex].setFillColor(sf::Color::Red);
		MenuIndex = 0;
		text[MenuIndex].setFillColor(sf::Color::White);
	}
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
