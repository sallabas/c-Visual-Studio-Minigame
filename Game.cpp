#include "Game.h"

//Private function
void Game::initWindow()
{
	//oyun i�i penceresini ve alan�n� ayarlad�k
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "The Space Gamy!", sf::Style::Close | sf::Style::Titlebar);
	//oyuna frame limiti atad�k
	this->window->setFramerateLimit(144);
	//dikey senkronizasyonu sa�lad�k
	this->window->setVerticalSyncEnabled(false);

}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
	//Font
	if(!this->font.loadFromFile("Fonts/ZillaSlab-Light.ttf"));
	   std::cout << "ERROR::Failed to load font" << "\n";
	//init point text / yaz� tipi ayarlar� 
	   this->pointText.setPosition(700.f, 25.f);
	   this->pointText.setFont(this->font);
	   this->pointText.setCharacterSize(20);
	   this->pointText.setFillColor(sf::Color::White);
	   this->pointText.setString("Test");

	   this->gameOverText.setFont(this->font);
	   this->gameOverText.setCharacterSize(100);
	   this->gameOverText.setFillColor(sf::Color::Red);
	   this->gameOverText.setString("Game Over!");
	   this->gameOverText.setPosition(
		   this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		   this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	   //init player GUI
	   this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	   this->playerHpBar.setFillColor(sf::Color::Red);
	   this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	   this->playerHpBarBack = this->playerHpBar;
	   this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	if(this->worldBackgroundTex.loadFromFile("Textures/Space1.jpg") == false);
	{
		std::cout << "ERROR::failed to load background image" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	//d��manlar�n oyun i�i ekran�nda bulunaca�� s�reyi ayarlamak i�in kullan�l�r
	this->spawnTimerMax = 60.f;
	this->spawnTimer = this->spawnTimerMax;
}

//constructor/destructor/oyun i�i yap�c� ve de�i�tirici
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
}


Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete Textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//Delete Enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}

}

//Function

void Game::run()
{
	//pencere a��k oldu�u s�rece uygulamay� devam ettirir
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if(this->player->getHp() > 0)
		   this->update();

		this->render();
	}
}

void Game::updatePollEvents()
{
	//sa� �stte kapatma tu�una bas�nca sisteme kapanma komutu verir
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		//uygulamay� kapatmak i�in escape tu�unu atama kodu 
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//gemiyi hareket ettirme
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	//ate� ettirme
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		//merminin ��k�� pozisyonu/koordinat�
		this->bullets.push_back(
		new Bullet(
		this->textures["BULLET"],
		this->player->getPos().x + this->player->getBounds().width/40.f,
		this->player->getPos().y,
		0.f,
		-1.f,
		5.f
		)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points:" << this->points;
	this->pointText.setString(ss.str());

	//update player gu�
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateBullets()
{
	unsigned counter = 0;

	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//mermilerin ekran d���na ��kt���nda silinmesini sa�lar
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//erase something from array, mermileri silme
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		//optimization
		++counter;
	}
}


void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//prevent the player get out of screen -> MT PVJ PONG GAME PROJECT VIDEO 2! 

	//left collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	//top collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//this bottom and right collision things are shit!!!!
	//right collision 
	//sa� taraf�n kordinat�n� al�rken sol taraftaki gibi "getbound().left" komutunu kullanamazs�n, sol taraf + nesnenin �st y�zeyini hesaplamak gerekir!!!!
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//bottom collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateEnemies()
{
	//e�er d��manlar gere�inden fazla spawn olmaya �al���rsa bu kod spawn olmay� 0 a indirip, fazla y�klenmeyi engeller
	//spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//update
	unsigned counter = 0;

	for (auto *enemy : this->enemies)
	{
		enemy->update();

		//mermilerin ekran d���na ��kt���nda silinmesini sa�lar
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//erase something from array, d��manlar� silme
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//du�manlar oyuncuya de�di�inde ekrandan silinecek 
		else if(enemy->getBounds().intersects(this->player->getBounds()))
		{
			//oyuncu, d��manlara de�di�inde can keybeder
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

		}

		//optimization
		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			//mermilerin d��manlarla birle�mesini kontrol ediyoruz
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

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw bacground
	this->renderWorld();

	//b�t�n her �eyin ekrana g�r�nt�s�n� yans�t�r, display eder
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	this->renderGUI(); 

	//game over
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();

}
