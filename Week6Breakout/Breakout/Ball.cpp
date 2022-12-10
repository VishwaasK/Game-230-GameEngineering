#include "Ball.h"

using namespace sf;
using namespace std;
using namespace gm;

//constructor
Ball::Ball(const sf::Vector2f& position, const sf::Vector2f& size) :GameObject(position, size) {
	canCollide = true;
	body.setPosition(position);
	body.setSize(size);
	setVelocity(Vector2f(Random::Range(-0.2f, 0.2f), -0.1f));
}

//update and render
void Ball::update(sf::RenderWindow& window, float deltaTime) {
	move();
}

void Ball::render(sf::RenderWindow& window, float deltaTime) {
	window.draw(body);
}

const bool Ball::getCanCollide() const {
	return canCollide;
}

void Ball::switchCanCollide() {
	canCollide = !canCollide;
}

//move Ball
void Ball::move() {
	GameObject::move();
	body.setPosition(position);
}

//bounce off wall/paddle
//3 types: 1 = wall, 2 = ceiling, 3 = paddle
void Ball::bounce(int type) {
	if (type == 1)
	{
		//invert x velocity
		setVelocity(Vector2f(-getVelocity().x, getVelocity().y));
	}
	else if (type == 2)
	{
		//invert y velocity
		setVelocity(Vector2f(getVelocity().x, -getVelocity().y));
	}
	else if (type == 3)
	{
		if (canCollide)
		{
			//hit paddle, x velocity is randomized and y velocity inverts and increases
			setVelocity(Vector2f((getVelocity().x + Random::Range(-0.1f, 0.1f)), -getVelocity().y * 1.05f));
			cout << "velocity: " << velocity.x << ", " << velocity.y << endl;
			switchCanCollide();
		}
	}
}

//reset velocity
void Ball::resetVel() {
	setVelocity(Vector2f(Random::Range(-0.2f, 0.2f), -0.1f));
}

//deconstructor
Ball::~Ball() {

}