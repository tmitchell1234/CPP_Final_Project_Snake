#pragma once

// Food class header file

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Food
{
protected:
	sf::CircleShape food;

	void initShape(sf::RenderWindow& window);

public:
	Food(sf::RenderWindow& window);

	sf::CircleShape getShape();

	void render(sf::RenderTarget& target);
};