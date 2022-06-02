#include "Player.h"

using namespace std;


void Player::initVariables()
{
	movementSpeed = 5.f;
	hpMax = 10;
	hp = hpMax;
}

void Player::initShape()
{
	shape.setFillColor(sf::Color::Green);
	shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	shape.setPosition(x, y);
	initVariables();
	initShape();
}

Player::~Player()
{
}

const sf::RectangleShape& Player::getShape() const
{
	return shape;
}

//Accessors
const int& Player::getHp() const
{
	return hp;
}

const int& Player::getHpMax() const
{
	return hpMax;
}

//Functions
void Player::takeDamage(const int damage)
{
	if (hp > 0)
		hp -= damage;

	if (hp < 0)
		hp = 0; 
}

void Player::gainHealth(const int health)
{
	if (hp < hpMax)
		hp += health; 
	
	if (hp > hpMax)
		hp = hpMax;	
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		shape.move(-movementSpeed, 0.f); //move object.
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->shape.move(this->movementSpeed, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		shape.move(0.f, -movementSpeed); //move object.
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		shape.move(0.f, movementSpeed); //move object.
	}
}

void Player::updateWindowsBoundsCollision(const sf::RenderTarget* target)
{
	//Left 
	if (shape.getGlobalBounds().left <= 0.f) 
		shape.setPosition(0.f, shape.getGlobalBounds().top);
	
	//right
	if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= target->getSize().x)
		shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);

	//top
	if (shape.getGlobalBounds().top <= 0.f)
		shape.setPosition(shape.getGlobalBounds().left, 0.f);
	//bottom
	if (shape.getGlobalBounds().top + shape.getGlobalBounds().height >= target->getSize().y)
		shape.setPosition(shape.getGlobalBounds().left, target->getSize().y - shape.getGlobalBounds().height);

}

void Player::update(const sf::RenderTarget* target)
{
	//keyboard input
	updateInput();

	//window bounds collision
	updateWindowsBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
