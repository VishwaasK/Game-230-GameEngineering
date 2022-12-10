#include "Paddle.h"

using namespace sf;
using namespace gm;

//constructor
Paddle::Paddle(const Vector2f& position, const Vector2f& size) : GameObject(position, size) {
	body.setPosition(position);
	body.setSize(size);
	paddleMidPosition = Vector2f(getPosition().x + (getCollider().width / 2), getPosition().y);
}

//update and render
void Paddle::update(RenderWindow& window, float deltaTime) {
	paddleMidPosition = Vector2f(getPosition().x + (getCollider().width / 2), getPosition().y);
}

void Paddle::render(RenderWindow& window, float deltaTime) {
	window.draw(body);
}

const sf::Vector2f& Paddle::getMidPosition() const {
	return paddleMidPosition;
}

//move Paddle
void Paddle::move() {
	GameObject::move();
	body.setPosition(position);
}

//deconstructor
Paddle::~Paddle() {

}