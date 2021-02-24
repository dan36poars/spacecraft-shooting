#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
    /* data */
    sf::CircleShape shape;
    int hp, hpMax, damage, points, type;
    float posX, posY, speed;
    unsigned pointCount;

    // Private Methods
    void initPrivateMethods();
    void initVariables();
    void initShape();

public:
    // Constructor and Destructor
    Enemy(float pos_x, float pos_y);
    ~Enemy();

    // Modifiers

    // Accessors
    const sf::FloatRect getBounds() const;
    const int& getPoints() const;
    const int& getDamage() const;

    // Public Functions
    void update();
    void render(sf::RenderTarget *target);
};

#endif // ENEMY_H