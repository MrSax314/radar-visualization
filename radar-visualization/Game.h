#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Class for game engine (wrapper class)

class Game
{
private:
	// Variables
	sf::RenderWindow* window; 
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse Positions
	sf::Vector2i mousePosWindow;

	// Game Logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	// Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Private Functions
	void initVariable();
	void initWindow();
	void initEnemies();

public:
	// Constructors
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePos();
	void updateEnemies();

	void printMousePos();

	void update();
	void render();
	void renderEnemies();

};

#endif