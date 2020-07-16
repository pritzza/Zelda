#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>
#include "map.h"
#include "TileMap.h"
#include "Entity.h"

class Game
{
private:
	sf::RenderWindow window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!" };
	sf::Clock clock;
	sf::Time elapsedTime;

	Player player;
	Map cmap;
	TileMap background;

	std::vector<Entity> Entities;

	float frame_counter = 0.0;
    int fps = 0;

	void getInput();

public:
	int GameLoop();
};

