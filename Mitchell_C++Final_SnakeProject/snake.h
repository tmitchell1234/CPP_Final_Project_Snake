#pragma once

// class header file to handle snake object

#ifndef snake_H
#define snake_H

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <random>
#include <list>
#include <vector>
#include <utility>

//#include "game.h" ////////////////

// represents Snake object, represented as sf::RectangleShape vector object

class Snake
{
protected:

	void initSnakeObj();

	int snakeBodySize = 4;
	float snakeX = 620.f;
	float snakeY = 340.f;
	float velocity;
	char direction = 'r';
	char previousDirection;

	sf::Vector2f snakeHeadPosition;
	std::vector<sf::Vector2f> previousPositions;

public:
	// snakeHead is instantiated with values to determine position

	// to get apparent center, screenwidth / 2 and screenheight / 2
	// minus half the value of the size length and width (apparent center)
	Snake(float x = 600.f, float y = 360.f);

	// make SFML RectangleShapes for snakeHead and snakeBody
	// snake is rendered as 2 separate objects so that calculation
	// can be performed on the snake head to determine collision
	sf::RectangleShape snakeHead;
	std::vector<sf::RectangleShape> snakeBody;

	sf::RectangleShape& getShape();

	void updateMovement();
	void updateBodyMovement();

	void growSnake();

	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

	bool collided = false;
};

#endif