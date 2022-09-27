// 'Food' class implementation file
#include "food.h"

/* ~~~~~~~~~~ constructor ~~~~~~~~~~ */
Food::Food(sf::RenderWindow& window)
{
	this->initShape(window);
}


/* ~~~~~~~~~~ initialize food shape model ~~~~~~~~~~ */
void Food::initShape(sf::RenderWindow& window)
{
	this->food.setRadius(15.f);
	this->food.setFillColor(sf::Color::Red);

	// set position at randomized x and y coordinates
	this->food.setPosition(sf::Vector2f(static_cast<float>(rand() % window.getSize().x),
		static_cast<float>(rand() % window.getSize().y)));
}

void Food::render(sf::RenderTarget& target)
{
	target.draw(this->food);
}

/* ~~~~~~~~~~ return food shape ~~~~~~~~~~ */
sf::CircleShape Food::getShape()
{
	// return current instance of food object
	return this->food;
}