#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/* SFML Includes             *
 * Add to every SFML project */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>

#include <SFML/Main.hpp>

 // Use our gm namespace for all our defined classes
namespace gm {
	// Our abstract GameObject class that defines the interface for all objects that appear in our games
	class GameObject
	{
		// Protected accessibility allows direct access for deriving classes
	protected:
		// All GameObjects should have a position
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::FloatRect collider;
		sf::RectangleShape body;
	public:
		// Default constructor
		GameObject();

		GameObject(const sf::Vector2f& position, const sf::Vector2f& size);

		// Overloaded constructor that takes a position
		//GameObject(const sf::Vector2f& position);

		// Our update interface, NOTE it is a pure virtual function
		virtual void update(sf::RenderWindow& window, float deltaTime) = 0;
		// Our render interface, NOTE it is a pure virtual function
		virtual void render(sf::RenderWindow& window, float deltaTime) = 0;

		//getters
		// Our position getter, NOTE the const reference return and marking the method itself const
		virtual const sf::Vector2f& getPosition() const;
		virtual const sf::Vector2f& getVelocity() const;
		//get collider
		virtual const sf::FloatRect& getCollider() const;
		//collision detection
		virtual bool collide(const sf::FloatRect& rect) const;

		//setters
		// Our position setter, NOTE the pass by const reference
		virtual void setPosition(const sf::Vector2f& position);
		virtual void setVelocity(const sf::Vector2f& vel);

		//gameObject movemenet
		virtual void move();

		//deconstructor
		~GameObject();
	};
}

#endif
