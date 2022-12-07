#include "Ball.h"

using namespace sf;
using namespace std;
using namespace gm;

//constructor
Ball::Ball(const sf::Vector2f& position, const sf::Vector2f& size) :GameObject(position, size) {
	canCollide = true;
	body.setPosition(position);
	body.setSize(size);
	setVelocity(Vector2f(-0.1f, Random::Range(-0.1f, 0.1f)));
}

//render and update
void Ball::update(sf::RenderWindow& window, float deltaTime) {
	move();
}

void Ball::render(sf::RenderWindow& window, float deltaTime) {
	window.draw(body);
}

const bool Ball::getCanCollide() const {
	return canCollide;
}

void Ball::changeCanCollide() {
	canCollide = !canCollide;
}

//Ball Movement
void Ball::move() {
	GameObject::move();
	body.setPosition(position);
}

//bounce off wall/paddle
//2 types: 1st is wall, 2nd is the paddle
void Ball::bounce(int type) {
	if (type == 1)
	{
		setVelocity(Vector2f(getVelocity().x, -getVelocity().y));
	}
	else if (type == 2)
	{
		if (canCollide)
		{
			setVelocity(Vector2f(-getVelocity().x * 1.1f, getVelocity().y + Random::Range(-0.1f, 0.1f)));
			cout << "velocity: " << velocity.x << ", " << velocity.y << endl;
			changeCanCollide();
		}
	}
}


//velocity reset 
void Ball::resetVelocity()
{
	setVelocity(Vector2f(-0.1f, Random::Range(-0.1f, 0.1f)));
}

//deconstructor
Ball::~Ball() {

}