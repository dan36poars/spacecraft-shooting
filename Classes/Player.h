#ifndef PLAYER_H
#define PLAYER

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Player
{
private:
    /* data */
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed, attackCoolDown, attackCoolDownMax;
    int hp, hpMax;

    // Private Methods
    void initPrivateMethods();
    void initAttack();
    void initTexture();
    void initSprite();

public:
    // Data

    // constructor and destructor
    Player();
    ~Player();

    // Accessors
    const sf::Vector2f &getPos() const;
    const float getWith() const;
    const float getHeight() const;
    const sf::FloatRect getBounds() const;
    const int &getHp() const;
    const int &getHpMax() const;

    // Modifiers
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);

    // Public Functions
    void update();
    void render(sf::RenderTarget &target);
    void move(const float dirX, const float dirY);
    const bool isAttack();
    void updateAttack();
};

#endif // PLAYER_H