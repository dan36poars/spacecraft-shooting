#include "Enemy.h"

// Constructor and Destructor
Enemy::Enemy(float pos_x, float pos_y) : posX(pos_x), posY(pos_y)
{
    this->initPrivateMethods();
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
    return this->points;
}

const int& Enemy::getDamage() const
{
    return this->damage;
}

// Private Methods
void Enemy::initPrivateMethods()
{
    this->initVariables();
    this->initShape();
}

void Enemy::initVariables()
{
    this->pointCount = rand() % 8 + 3; // min - 3 , max - 10
    this->type = 0;
    this->hpMax = (int)this->pointCount;
    this->speed = (float)this->pointCount / 2;
    this->hp = this->hpMax;
    this->damage = this->pointCount;
    this->points = this->pointCount;
}

void Enemy::initShape()
{
    this->shape.setRadius(this->pointCount * 3);
    this->shape.setPointCount(this->pointCount);
    this->shape.setPosition(posX, posY);
    this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

// Modifiers

// Accessors

// Public Functions
void Enemy::update()
{
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
