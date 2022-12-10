#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"

namespace gm {

	class Paddle : public GameObject {
	private:
		//middle of paddle
		sf::Vector2f paddleMidPosition;
	public:
		//constructor
		Paddle(const sf::Vector2f& position, const sf::Vector2f& size);

		//update and render
		virtual void update(sf::RenderWindow& window, float deltaTime) override;
		virtual void render(sf::RenderWindow& window, float deltaTime) override;

		//get position of middle of paddle
		const sf::Vector2f& getMidPosition() const;

		//move Paddle
		virtual void move() override;

		//deconstructor
		~Paddle();
	};
}

#endif // PADDLE_H