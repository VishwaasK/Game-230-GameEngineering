#include "Brick.h"

using namespace std;
using namespace sf;
using namespace gm;

Brick::Brick() {

}

Brick::Brick(const Vector2f& position, const Vector2f& size, const BrickType* t) : position(position), collider(position, size), type(t)
{
	maxHP = t->hp;
	hp = t->hp;
	isAlive = true;
	c = t->col;

	body.setPosition(Vector2f(collider.left, collider.top));
	body.setSize(Vector2f(collider.width, collider.height));
	body.setFillColor(c);
	body.setOutlineThickness(2.0f);
	body.setOutlineColor(Color::Cyan);
}

void Brick::update(sf::RenderWindow& window) {
	if (hp == 1 && maxHP != 1 && body.getFillColor() != Color::Red)
	{
		body.setFillColor(Color::Red);
	}
	if (hp == 0)
	{
		setAlive(false);
	}
}

void Brick::render(sf::RenderWindow& window) {
	window.draw(body);
}

//get position
const sf::Vector2f& Brick::getPosition() const {
	return position;
}

//get collider
const sf::FloatRect& Brick::getCollider() const {
	return collider;
}

//get alive
const bool Brick::getAlive() const {
	return isAlive;
}

//set alive
void Brick::setAlive(const bool state) {
	isAlive = state;
}

//get health
const int Brick::getHealth() const {
	return hp;
}

//set health
void Brick::setHealth(const int health) {
	hp = health;
}

void Brick::reset() {
	hp = maxHP;
	isAlive = true;
	body.setFillColor(c);
}

Brick::~Brick()
{
}