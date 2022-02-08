#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:

	//�oklu bir dokula yaratmak i�in kullan�l�r, sistem her zaman yeni bir doku olu�turmak istemez.
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementspeed;

public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//accesor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif //BULLET_H