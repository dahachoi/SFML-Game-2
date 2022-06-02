#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "Player.h"
#include "SwagBall.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initWindow();
	void initVariables();
	void initFont();
	void initText();

public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors, get variables from this class

	const bool& getEndGame() const;
	//Modifiers, modify variables in this class

	//Functions, general stuff that can both modify and access

	const bool running() const;
	void pollEvents();

	void spawnSwagBalls();
	const int randomizeBallType() const;
	void updatePlayer();
	void updateCollision();

	void updateGui();
	void update();

	void renderGui(sf::RenderTarget *);
	void render();
};

