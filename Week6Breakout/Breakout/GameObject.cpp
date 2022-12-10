#include "GameObject.h"

using namespace sf;
using namespace gm;

//constructor
GameObject::GameObject() {
}

GameObject::GameObject(const Vector2f& position, const Vector2f& size) :position(position), collider(position, size) {}

//get position
const Vector2f& GameObject::getPosition() const {
	return position;
}

//get velocity
const sf::Vector2f& GameObject::getVelocity() const {
	return velocity;
}

//set position
void GameObject::setPosition(const sf::Vector2f& pos) {
	this->position = pos;
	collider.left = position.x;
	collider.top = position.y;
	body.setPosition(pos);
}

//set velocity
void GameObject::setVelocity(const sf::Vector2f& vel) {
	this->velocity = vel;
}

//get collider
const sf::FloatRect& GameObject::getCollider() const {
	return collider;
}

//collision detection
bool GameObject::collide(const sf::FloatRect& rect) const {
	return collider.intersects(rect);
}

//move gameObject
void GameObject::move() {
	setPosition(position + velocity);
}

//deconstructor
GameObject::~GameObject() {

}