#include "game.h"


Game::Game()
{
	this->initVariable();
	this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Private Functions
void Game::initVariable()
{
	this->window = nullptr;

    // Game Logic
    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = 0.f;
    this->maxEnemies = 5;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode;
	this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), "RADAR Visualizer", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

// Functions
void Game::spawnEnemy()
{
    /*
        Adds sprite to enemy array with pos and color settings
        - Sets rand pos
        - Sets rand color
        - Adds enemy to vector
    */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );
    this->enemy.setFillColor(sf::Color::Green);

    // Add enemy to list
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
        }
    }
}

void Game::update()
{
    this->pollEvents();
    this->updateMousePos();
    this->printMousePos();
    this->updateEnemies();
}

void Game::updateEnemies()
{
    /*
        Updates the enemy spawn timer and spawns enemies when
        the total amount of enemies is smaller than the max
        Moves enemies downward
        Removes the enemies at the edge of the screen // TODO
    */

    // Update the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    // Move the enemies
    for (auto &e : this->enemies)
    {
        e.move(0.f, 1.f);
    }
}

void Game::updateMousePos()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::printMousePos()
{
    std::cout << "Mouse pos: "
        << this->mousePosWindow.x << " "
        << this->mousePosWindow.y << std::endl;
}

void Game::renderEnemies()
{
    for (auto& e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::render()
{
    /*
        Renders the game objects
        - Clear old frame
        - Render objects
        - Display window
    */

    this->window->clear(sf::Color::Black);

    // Draw Game Objects
    this->renderEnemies();

    this->window->display();
}








