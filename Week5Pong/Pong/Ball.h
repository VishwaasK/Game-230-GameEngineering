#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Random.h"

namespace gm {
	class Ball :public GameObject
	{
	private:
		//bool values so that ball can't hit paddle multiple times if intersecting at wrong place
		bool canCollide;
	public:
		//constructor
		Ball(const sf::Vector2f& position, const sf::Vector2f& size);

		//update and render
		virtual void update(sf::RenderWindow& window, float deltaTime) override;
		virtual void render(sf::RenderWindow& window, float deltaTime) override;

		//toggle whether ball can collide
		virtual const bool getCanCollide() const;
		virtual void changeCanCollide();

		//Paddle movement
		virtual void move() override;

		//bounce off wall(1), paddle(2)
		virtual void bounce(int type);

		//reset velocity
		virtual void resetVelocity();

		//deconstructor
		~Ball();
	};
}

#endif BALL_H