#ifndef BRICK_H
#define BRICK_H

//Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>

namespace gm {
	struct BrickType {
		int hp;
		sf::Color col;
	};

	class Brick {
	private:
		sf::Vector2f position;
		sf::FloatRect collider;
		sf::RectangleShape body;
		const BrickType* type;
		int maxHP;
		int hp;
		sf::Color c;
		bool isAlive;

	public:
		Brick();
		Brick(const sf::Vector2f& position, const sf::Vector2f& size, const BrickType* t);
		void update(sf::RenderWindow& window);
		void render(sf::RenderWindow& window);
		//get position
		virtual const sf::Vector2f& getPosition() const;
		//get collider
		const sf::FloatRect& getCollider() const;
		//get alive
		const bool getAlive() const;
		//set alive
		void setAlive(const bool state);
		//get health
		const int getHealth() const;
		//set health
		void setHealth(const int health);
		//reset brick
		void reset();
		~Brick();
	};
}

#endif BRICK_H