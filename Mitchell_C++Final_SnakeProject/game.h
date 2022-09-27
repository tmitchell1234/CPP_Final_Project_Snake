#pragma once

// class to handle game engine

#ifndef game_H
#define game_H

#include "snake.h"
#include "food.h"

#include <iostream>
#include <ctime>
#include <vector>


class Game
{
protected:
	// variables
	// window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	bool endGame;
	bool crashed = false;

	// Game objects
	Snake snake;
	std::vector<Food> food;

	// private functions
	void initVariables();
	void initWindow();

public:
	// constructor / destructor
	Game();
	virtual ~Game();

	// accessors
	bool running();

	// engine functions
	void update();
	void render();
	void pollEvents();

	// detect snake collision
	void detectFoodCollision();
	void detectCrashed(sf::RenderTarget* target);

	// spawn food
	void spawnFood();
	int maxFood = 1;
};

#endif