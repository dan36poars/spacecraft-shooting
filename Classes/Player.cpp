#include "Player.h"
// constructor and destructor
Player::Player()
{
    this->initPrivateMethods();
}

Player::~Player()
{
}

// Private Methods
void Player::initPrivateMethods()
{
    this->initAttack();
    this->initTexture();
    this->initSprite();
}

void Player::initAttack()
{
    this->movementSpeed = 5.f;
    this->attackCoolDownMax = 15.f;
    this->attackCoolDown = this->attackCoolDownMax;
    this->hpMax = 100;
    this->hp = this->hpMax;
}

void Player::initTexture()
{
    // load a texture from file
    if (!this->texture.loadFromFile("images/ship.png"))
    {
        std::cout << "ERROR::PLAYER::INITEXTURE - Could not load texture file" << std::endl;
    }
}

void Player::initSprite()
{
    // set the texture to the sprite
    this->sprite.setTexture(this->texture);
    // resize sprite
    this->sprite.scale(0.1f, 0.1f);
}

// Accessors
const sf::Vector2f &Player::getPos() const
{
    return this->sprite.getPosition();
}

const float Player::getWith() const
{
    return this->sprite.getGlobalBounds().width;
}

const float Player::getHeight() const
{
    return this->sprite.getGlobalBounds().height;
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
    return this->hp;
}

const int& Player::getHpMax() const
{
    return this->hpMax;
}

// Modifiers
void Player::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp) 
{
    this->hp = hp;
}

void Player::loseHp(const int value) 
{
    this->hp -= value;
    if (this->hp < 0)
    {
        this->hp = 0;
    }
    
}

// Public Functions
void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}

void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::isAttack()
{
    if (this->attackCoolDown >= this->attackCoolDownMax)
    {
        this->attackCoolDown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if (this->attackCoolDown < this->attackCoolDownMax)
        this->attackCoolDown += 1.f;
}
