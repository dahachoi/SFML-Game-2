#include "Game.h"

using namespace std;

//Constructors and Destructors

Game::Game()
{
	initVariables();
	initWindow();
	initFont();
	initText();
}

Game::~Game()
{
	delete window;
}

const bool& Game::getEndGame() const
{
	return endGame;
}

void Game::initVariables()
{
	endGame = false;
	spawnTimerMax = 10.f;
	spawnTimer = spawnTimerMax;
	maxSwagBalls = 10;
	points = 0;
}

void Game::initFont()
{
	if (!font.loadFromFile("Fonts/Papernotes.ttf")) {
		cout << "load failed" << endl;
	}
}

void Game::initText()
{
	guiText.setFont(font);
	guiText.setFillColor(sf::Color::White);
	guiText.setCharacterSize(32);
	
	endGameText.setFont(font);
	endGameText.setFillColor(sf::Color::Red);
	endGameText.setCharacterSize(60);
	endGameText.setPosition(sf::Vector2f(20, 300));
	endGameText.setString("Game Over!");
}

void Game::initWindow()
{
	videoMode = sf::VideoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(60);
}

//Functions

const bool Game::running() const
{
	return window->isOpen() /*&& !endGame*/;

}

void Game::pollEvents()
{
	while (window->pollEvent(sfmlEvent)) {
		switch (sfmlEvent.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (sfmlEvent.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	//Timer
	if (spawnTimer < spawnTimerMax) //every 10 times, spawn a swagball
		spawnTimer += 1.f;
	else {
		if (swagBalls.size() < maxSwagBalls) { 
			swagBalls.push_back(SwagBall(*window,randomizeBallType()));
			spawnTimer = 0.f;
		}
		
	}
}

const int Game::randomizeBallType() const
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}

void Game::updatePlayer()
{
	player.update(window);

	if (player.getHp() <= 0) endGame = true;

}

void Game::updateCollision()
{
	//Check the collision

	for (size_t i = 0; i < swagBalls.size(); ++i) {
		if (player.getShape().getGlobalBounds().intersects(swagBalls[i].getShape().getGlobalBounds())) {
			switch (swagBalls[i].getType()) {
			case SwagBallTypes::DEFAULT:
				points++;
				break;
			case SwagBallTypes::DAMAGING:
				player.takeDamage(2);
				break;
			case SwagBallTypes::HEALING:
				player.gainHealth(1);
				break;

			}


			//Add points
			points++;
			//Remove the ball
			swagBalls.erase(swagBalls.begin() + i);
			
		}
	}

}

void Game::updateGui()
{
	stringstream ss;

	ss << "Points : " << points << "\n" << " - Health : " << player.getHp() << " / " << player.getHpMax() <<"\n";

	guiText.setString(ss.str());
}

void Game::update()
{
	pollEvents();

	if (!endGame) {
		spawnSwagBalls();
		updatePlayer();
		updateCollision();
		updateGui();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(guiText);
}

void Game::render()
{
	window->clear(); //must clear the old frame.

	//Render stuff in betwee
	player.render(window);

	for (auto i : swagBalls)
		i.render(*window);  

	//Render GUI at the end
	renderGui(window);

	//Render end Text
	if (endGame)
		window->draw(endGameText);
	window->display();
}