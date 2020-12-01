#pragma once
#include "player.h"
#include "map.h"

class Game
{
private:
	// variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float deltaTime;
	
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

	// methods
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();
	void render();
	void run();

	// handling collisons with window borders
	void borders();

	// handling collisions with object
	void collision();


};

