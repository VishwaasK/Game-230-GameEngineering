#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Random.h"

namespace gm {

	class Ball : public GameObject {
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
		virtual void switchCanCollide();

		//move Paddle
		virtual void move() override;

		//bounce off wall/paddle
		//3 types: 1 = wall, 2 = ceiling, 3 = paddle
		virtual void bounce(int type);

		//reset velocity
		virtual void resetVel();

		//deconstructor
		~Ball();
	};
}

#endif // BALL_H