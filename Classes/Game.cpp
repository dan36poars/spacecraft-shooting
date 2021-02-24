#include "Game.h"

// Contructor
Game::Game()
{
    this->initPrivateFunctions();
}

Game::Game(std::string title = "title game") : title(title)
{
    this->initPrivateFunctions();
}

// Destructor
Game::~Game()
{
    delete this->window;
    delete this->player;

    // Remove all the textures
    for (auto &i : this->textures)
    {
        delete i.second;
    }

    // Remove all bullets
    for (auto *i : this->bullets)
    {
        delete i;
    }

    // Remove all enemies
    for (auto *i : this->enemies)
    {
        delete i;
    }
}

// Private Functions

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(WIDTH_, HEIGHT_), title, sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(FRAME_RATE_LIMIT);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initPrivateFunctions()
{
    this->initWindow();
    this->initTextures();
    this->initPlayer();
    this->initEnemies();
    this->initGUI();
    this->initWorldBackground();
    this->initSystems();
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("images/bullet.png");
}

void Game::initEnemies()
{
    this->spawnTimerMax = 15.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initGUI()
{
    // Loads fonts
    if (!this->font.loadFromFile("fonts/PixellettersFull.ttf"))
    {
        std::cout << "ERROR::GAME::INITGUI:: font ttf don't loaded" << std::endl;
    }

    // Init point Text
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(32);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("test");
    this->pointText.setPosition(650.f, 8.f);

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Yellow);
    this->gameOverText.setOutlineColor(sf::Color(0, 0, 0, 255));
    this->gameOverText.setOutlineThickness(2.f);
    this->gameOverText.setString("Game Over!");
    this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    // init player GUI
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Green);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorldBackground()
{
    if (!this->worldBackgroundTexture.loadFromFile("images/background1.jpg"))
        std::cout << "ERROR::GAME::INITWORLDBACKGROUND - Don't load image" << std::endl;

    this->worldBackGroundSprite.setTexture(this->worldBackgroundTexture);
}

void Game::initSystems()
{
    this->points = 0;
}

// Modifiers

// Acessors

// Function
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updatePoolEvents();
        if (this->player->getHp() > 0)
        {
            this->update();
        }
        
        this->render();
    }
}

void Game::updatePoolEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            this->window->close();

        if (sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
            this->window->close();
    }
}

void Game::updateInput()
{
    // move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player->move(-1.f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player->move(1.f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->player->move(0.f, -1.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->player->move(0.f, 1.f);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->isAttack())
    {
        this->bullets.push_back(new Bullet{this->textures["BULLET"], this->player->getPos().x + this->player->getWith() / 2.3f, this->player->getPos().y + this->player->getHeight() / 4.f, 0.f, -1.f, 10.f});
    }
}

void Game::updateBullets()
{
    unsigned counter = 0;
    for (auto *bullet : this->bullets)
    {
        bullet->update();

        // Bullet Culling (top of screen)
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            // Delete the buller
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);

            //std::cout << this->bullets.size() << std::endl;
        }
        ++counter;
    }
}

void Game::updateGUI()
{
    std::stringstream ss;
    ss << "Points: " << this->points;
    this->pointText.setString(ss.str());

    // Update Player GUI
    float hpPercent = (float)this->player->getHp() / (float)this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
    // left world collision
    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }

    // right world collision
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    // top world collision
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }

    // bottom world collision
    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
}

void Game::updateEnemies()
{
    // Spawning
    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 40.f, -100.f));
        this->spawnTimer = 0.f;
    }

    // Update
    unsigned counter = 0;
    for (auto *enemy : this->enemies)
    {
        enemy->update();

        // Enemies Culling (bottom of screen)
        if (enemy->getBounds().top > this->window->getSize().y)
        {
            // Delete the enemies
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);

            //std::cout << this->bullets.size() << std::endl;
        }
        // Enemy player collision
        else if (enemy->getBounds().intersects(this->player->getBounds()))
        {
            this->player->loseHp(this->enemies.at(counter)->getDamage());
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }
        ++counter;
    }
}

void Game::updateCombat()
{

    for (int i = 0; i < this->enemies.size(); ++i)
    {
        bool enemy_deleted = false;
        for (int k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {
                this->points += this->enemies[i]->getPoints();

                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                enemy_deleted = true;
            }
        }
    }
}

void Game::update()
{
    this->updateInput();
    this->player->update();
    this->updateCollision();
    this->updateBullets();
    this->updateEnemies();
    this->updateCombat();
    this->updateGUI();
    this->updateWorld();
}

void Game::renderGUI()
{
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

void Game::renderBackground()
{
    this->window->draw(this->worldBackGroundSprite);
}

void Game::render()
{
    this->window->clear();

    // drawing world background
    this->renderBackground();

    // drawing all enemies
    for (auto *enemy : this->enemies)
    {
        enemy->render(this->window);
    }

    // drawing all bullets
    for (auto *bullet : this->bullets)
    {
        bullet->render(this->window);
    }

    // drawing all the stuffs
    this->player->render(*this->window);

    // drawing font
    this->renderGUI();

    // Game over screen
    if (this->player->getHp() <= 0)
    {
        this->window->draw(this->gameOverText);
    }
    

    this->window->display();
}
