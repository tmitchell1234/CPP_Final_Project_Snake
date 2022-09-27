// Snake class implementation file

#include "snake.h"
#include "game.h" ///////////////////


/* ~~~~~~~~~~ constructor and destructor ~~~~~~~~~~ */
Snake::Snake(float x, float y)
{
	// initialize snake at specified x and y coordinates
	this->snakeHead.setPosition(x, y);

	// experimental
	snakeHeadPosition.x = x;
	snakeHeadPosition.y = y;

	// store x and y coordinates for calculation
	// later on snakeBody vector positions
	snakeX = x;
	snakeY = y;

	this->initSnakeObj();
}


void Snake::initSnakeObj()
{
	// origin of shape starts at top left corner
	this->snakeHead.setSize(sf::Vector2f(40.f, 40.f));
	this->snakeHead.setFillColor(sf::Color::White);
	this->snakeHead.setOutlineColor(sf::Color::Green);
	this->snakeHead.setOutlineThickness(3.f);

	// start loop at 1 so that first body block is not inside snake head
	for (int i = 1; i < 5; i++)
	{
		sf::RectangleShape bodyShape;

		bodyShape.setSize(sf::Vector2f(40.f, 40.f));
		bodyShape.setFillColor(sf::Color::White);
		bodyShape.setPosition(snakeX - (45.f * i), snakeY);

		snakeBody.emplace(snakeBody.begin(), bodyShape);
	}

	// initialize previous position vectors to size of snake body
	// allows game to start with 4 snake body blocks and adjusts
	// their positions accordingly at start of game

	// initialize 4 elements in previousPositions vector

	for (int i = 0; i < 4; i++)
	{
		previousPositions.push_back(this->snakeHead.getPosition());
	}
}


/* ~~~~~~~~~~ draw / render snake object ~~~~~~~~~~ */
void Snake::update(const sf::RenderTarget* target)
{
	this->updateMovement();

	this->updateBodyMovement();

	snakeHeadPosition = snakeHead.getPosition();
}


void Snake::render(sf::RenderTarget* target)
{
	target->draw(this->snakeHead);

	for (int i = 0; i < snakeBody.size(); i++)
	{
		target->draw(this->snakeBody[i]);
	}
}

/* ~~~~~~~~~~ manage snake movement ~~~~~~~~~~ */
void Snake::updateMovement()
{
	// keyboard input
	// 'A' key: move snake left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = 'l';
	}
	// 'D' key: move snake right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = 'r';
	}
	// 'W' key: move snake up
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = 'u';
	}
	// 'S' key: move snake down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = 'd';
	}

	// continuously move snake in specified direction
	switch (direction)
	{
	case 'l':
		// move snake negative x direction (left), no change in y direction

		// set new position of snake head each frame
		// move the snake head 30 pixels per frame
		this->snakeHead.setPosition(snakeHeadPosition.x - 30.f, snakeHeadPosition.y);

		// store previous position coordinates so the snake body can follow behind
		previousPositions.emplace(previousPositions.begin(), this->snakeHead.getPosition());
		break;

	case 'r':
		// move snake positive x direction (right)
		this->snakeHead.setPosition(snakeHeadPosition.x + 30.f, snakeHeadPosition.y);

		previousPositions.emplace(previousPositions.begin(), this->snakeHead.getPosition());

		break;

	case 'u':
		// move snake negative y direction (up), no change in x direction
		this->snakeHead.setPosition(snakeHeadPosition.x, snakeHeadPosition.y - 30.f);

		previousPositions.emplace(previousPositions.begin(), this->snakeHead.getPosition());

		break;
	case 'd':
		// move snake positive y direction (down)
		this->snakeHead.setPosition(snakeHeadPosition.x, snakeHeadPosition.y + 30.f);

		previousPositions.emplace(previousPositions.begin(), this->snakeHead.getPosition());

		break;
	}
}

void Snake::updateBodyMovement()
{
	// set body positions equal to previous snake head positions to follow behind the snake head
	for (int i = 0; i < snakeBodySize; i++)
	{
		snakeBody[i].setPosition(previousPositions[i]);
	}
}

/* ~~~~~~~~~~ handle increasing size of snake upon eating food ~~~~~~~~~~ */
void Snake::growSnake()
{
	snakeBodySize++;

	// create new rectangle (square) object
	sf::RectangleShape bodyShape;

	bodyShape.setSize(sf::Vector2f(40.f, 40.f));
	bodyShape.setFillColor(sf::Color::White);

	// set new body shape position to equal the coordinates
	// of the last value in previous positions vector
	bodyShape.setPosition(previousPositions.back());

	// insert new bodyShape object to the back of the
	// current instance of the snakeBody object vector
	this->snakeBody.push_back(bodyShape);
}


/* ~~~~~~~~~~ return snake head shape ~~~~~~~~~~ */
sf::RectangleShape& Snake::getShape()
{
	return this->snakeHead;
}

