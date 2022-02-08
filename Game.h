#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//oyuncuyu classa ekledik 
#include "Player.h"
#include<map>
#include<string>
#include<sstream>
#include"Bullet.h"
#include"Enemy.h"


class Game
{
private:
	//oyun penceresini oluþturan kod
	sf::RenderWindow* window;

	//resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	//player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;


	//Enemies 
	//std-> ile baþlayan kod birden fazla düþman yaratmayý saðlar 
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;


	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
	

public:
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateBullets();
	void updateWorld();
	void updateCollision();
	void updateEnemies();
	void updateCombat();

	//oyunun framelerini tarar ve günceller, genel olarak her oyunda kullanýlýr
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};

