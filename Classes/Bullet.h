#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
    /* data */
    sf::Sprite shape;
    sf::Vector2f direction;
    float movementSpeed;

    // Private Methods

public:
    // Constructor and Destructor
    Bullet();
    Bullet(sf::Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
    ~Bullet();

    // Modifiers
    const sf::FloatRect getBounds() const;

    // Accessors

    // Public Functions
    void update();
    void render(sf::RenderTarget *target);
};

#endif // BULLET_H