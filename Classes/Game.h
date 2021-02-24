#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <map>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

/*
    Class Game that acts as the game engine.
    Wrapper class
*/

#define WIDTH_ 800
#define HEIGHT_ 600
#define FRAME_RATE_LIMIT 60

class Game
{
private:
    /* data */
    sf::RenderWindow *window;
    std::string title;

    // Resources
    std::map<std::string, sf::Texture *> textures;
    std::vector<Bullet *> bullets;

    // GUI
    sf::Font font;
    sf::Text pointText;
    sf::Text gameOverText;

    // Player GUI
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    // World
    sf::Sprite worldBackGroundSprite;
    sf::Texture worldBackgroundTexture;

    // System
    unsigned points;

    // Player
    Player *player;

    // Enemy
    std::vector<Enemy *> enemies;
    float spawnTimer;
    float spawnTimerMax;

    // Private functions
    void initWindow();
    void initPrivateFunctions();
    void initPlayer();
    void initTextures();
    void initEnemies();
    void initGUI();
    void initWorldBackground();
    void initSystems();

public:
    // Contructor
    Game();
    Game(std::string title);
    // Destructor
    ~Game();

    // Modifiers

    // Acessors

    // Function
    void run();
    void updatePoolEvents();
    void updateInput();
    void updateBullets();
    void updateGUI();
    void updateWorld();
    void updateCollision();
    void updateEnemies();
    void updateCombat();
    void update();
    void renderGUI();
    void renderBackground();
    void render();
};

#endif // GAME_H