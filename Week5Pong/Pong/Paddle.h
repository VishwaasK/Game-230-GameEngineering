#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"

namespace gm {
	enum moveDirection
	{
		Up = -1,
		None = 0,
		Down = 1
	};

	class Paddle : public GameObject
	{
	protected:
		moveDirection direction;
	public:
		//constructor
		Paddle(const sf::Vector2f& position, const sf::Vector2f& size);

		//update and render
		virtual void update(sf::RenderWindow& window, float deltaTime) override;
		virtual void render(sf::RenderWindow& window, float deltaTime) override;

		//move Paddle
		virtual void move() override;

		//get and set move direction
		virtual moveDirection getMoveDirection() const;

		virtual void setMoveDirection(moveDirection direction);

		//deconstructor
		~Paddle();
	};
}

#endif PADDLE_H