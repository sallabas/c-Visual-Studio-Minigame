#include "Player.h"

void Player::initVariables()
{
	this->movementspeed = 3.f;

    this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 50;
	this->hp = this->hpMax;

}

void Player::initTexture()
{
	//d�� dosyadan uzay gemisinin dokusunu olu�turuca��m�z sat�r
	if (this->texture.loadFromFile("Textures/ship.png")== false);
	{
		//e�er y�kledi�in doku hata verirse sistem crash vermek yerine bu hata kodunu vericek
		std::cout << "ERROR::fail to load texture." << "\n";

	}

}

void Player::initSprite()
{
	//sprite a doku at�yaca��m�z sat�r
	this->sprite.setTexture(this->texture);

	//sprite i yeniden yap�land�raca��m�z sat�r
	this->sprite.scale(0.15f, 0.15f);
} 

Player::Player()
{
	this->initVariables();

	this->initTexture();

	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
	
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
		this->hp = 0;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementspeed * dirX, this->movementspeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.9f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	//atak h�z� i�in cooldownu player �zerinden veriyoruz, mermiler �zerinden de�il :)
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 1.f;
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
