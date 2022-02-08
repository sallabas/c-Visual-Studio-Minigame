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
	//oyun penceresini olu�turan kod
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
	//std-> ile ba�layan kod birden fazla d��man yaratmay� sa�lar 
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

	//oyunun framelerini tarar ve g�nceller, genel olarak her oyunda kullan�l�r
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};

