#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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

	class GameObject {
	protected:
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::FloatRect collider;
		sf::RectangleShape body;
	public:
		//constructor
		GameObject();

		//overloaded constructor with position and size
		GameObject(const sf::Vector2f& position, const sf::Vector2f& size);

		//update and render
		virtual void update(sf::RenderWindow& window, float deltaTime) = 0;
		virtual void render(sf::RenderWindow& window, float deltaTime) = 0;

		//get position
		virtual const sf::Vector2f& getPosition() const;

		//get velocity
		virtual const sf::Vector2f& getVelocity() const;

		//set position
		virtual void setPosition(const sf::Vector2f& pos);

		//set velocity
		virtual void setVelocity(const sf::Vector2f& vel);

		//get collider
		virtual const sf::FloatRect& getCollider() const;

		//collision detection
		virtual bool collide(const sf::FloatRect& rect) const;

		//move gameObject
		virtual void move();

		//deconstructor
		~GameObject();
	};
}

#endif