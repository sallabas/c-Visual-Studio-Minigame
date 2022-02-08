/*
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
*/
#include "Game.h"
#include<time.h>

int main()
{
	srand(time_t(static_cast<unsigned>(0)));


	Game game;

	game.run();


	//End of app
	return 0;

}
