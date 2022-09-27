// "Game" class implementation file

#include "game.h"

/* ~~~~~~~~~~ constructor and destructor ~~~~~~~~~~ */
Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

/* ~~~~~~~~~~ private init functions ~~~~~~~~~~ */
void Game::initVariables()
{
	this->window = nullptr;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;

	// set pointer to object of SFML RenderWindow
	this->window = new sf::RenderWindow(this->videoMode, "Snake!", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(20);
}

/* ~~~~~~~~~~ accessors ~~~~~~~~~~ */
bool Game::running()
{
	return this->window->isOpen() && !this->endGame;
}

/* ~~~~~~~~~~ look for signals to end the game ~~~~~~~~~~ */
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		// actually close the window if the X is clicked
		case sf::Event::Closed:
			this->window->close();
			break;

		// if 'Escape' key is pressed, close the window
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}


/* ~~~~~~~~~~ game engine functions ~~~~~~~~~~ */
// main update sequence that runs every frame of the game
void Game::update()
{
	this->pollEvents();
	this->detectFoodCollision();

	this->spawnFood();

	this->snake.update(this->window);

	this->detectCrashed(this->window);
}

void Game::render()
{
	/*
		renders the game objects
		1. clear old frame
		2. render objects
		3. display new frame in window
	*/

	this->window->clear(sf::Color::Black);

	// draw game objects
	this->snake.render(this->window);

	// draw food on the screen
	for (auto i : this->food)
	{
		i.render(*this->window);
	}

	// display shapes after making calculations
	this->window->display();
}

/* ~~~~~~~~~~ spawn food objects ~~~~~~~~~~ */
void Game::spawnFood()
{
	// limits drawn food on screen to 1
	if (this->food.size() < this->maxFood)

		// insert new food object into vector, calls constructor
		// in 'Food' class to spawn a new food item
		this->food.push_back(Food(*this->window));
}

/* ~~~~~~~~~~ detect food collision ~~~~~~~~~~ */
void Game::detectFoodCollision()
{
	for (size_t i = 0; i < this->food.size(); i++)
	{
		// compare global boundary of snake head vs food shape
		if (this->snake.getShape().getGlobalBounds().intersects(this->food[i].getShape().getGlobalBounds()))
		{
			// erase the food item if snake head and food shape intersect
			this->food.erase(this->food.begin() + i);

			// grow snake body by adding rectangleshape into snakebody vector
			this->snake.growSnake();
		}
	}
}

/* ~~~~~~~~~~ detect walls and body collision ~~~~~~~~~~ */
void Game::detectCrashed(sf::RenderTarget* target)
{
	// left boundary
	if (this->snake.getShape().getGlobalBounds().left <= 0.f)
		endGame = true;
	// right boundary
	if (this->snake.getShape().getGlobalBounds().left + this->snake.getShape().getGlobalBounds().width + 2.f >= target->getSize().x)
		endGame = true;

	// top boundary
	if (this->snake.getShape().getGlobalBounds().top <= 0.f)
		endGame = true;

	// bottom boundary
	if (this->snake.getShape().getGlobalBounds().top + this->snake.getShape().getGlobalBounds().height + 1.f >= target->getSize().y)
		endGame = true;

	// detect if snake head collides with body
	for (int i = 0; i < snake.snakeBody.size(); i++)
	{
		// if the snake head intersects boundary of the body squares, end the game
		if (this->snake.getShape().getGlobalBounds().intersects(snake.snakeBody[i].getGlobalBounds()))
		{
			// limits the intersectable body square to be after the 4th body element
			// this prevents the snake head from intersecting with it's starting body and causing a game over
			if (i > 3)
				endGame = true;
		}
	}
}
