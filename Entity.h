#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"

constexpr int WINDOW_WIDTH = 256;
constexpr int WINDOW_HEIGHT = 240;

enum SpriteSheetRows
{
	Link,
};

class Entity
{
protected:
	sf::IntRect frame;
	sf::Texture texture;

	int width;
	int height;

protected:
	void getSpriteSheet(int spriteSheet);
public:
	sf::Sprite sprite;
	float x;
	float y;
	Entity();
};


class Creature : public Entity
{
public:
	bool isMoving{ false };

protected:
	float xVel{ 0 };
	float yVel{ 0 };

	int health{ 1 };
	int speed{ 50 };

	short newDirection{ 0 };			// S = 0, N = 1, E = 2, W = 3
	short oldDirection{ 0 };			// old is set to new when direction doesnt change
	short animationFrame{ 0 };	// what frame of animation cycle
	const short keyFrameDuration{ 60 };
	float keyFrameDurationIndex{ 0.0f };
	void checkCollision(Map cmap, float elapsedTime);
	
	bool isPerformingAction { false };

	short attackDuration { 60 };	// in frames
	short attackCooldown  { 60 };	// also in frames

	int getDirection();

	Creature() : Entity() {}
};

class Player : public Creature
{
private:
	float secondsPerUpdate;
public:
	bool upFlag{}, downFlag{}, leftFlag{}, rightFlag{};
	void setDirection(int direction);
	void tick(float elapsedTime, const Map &cmap);
	void updateSprite();

	Player();
	//Player() : Creature() {}
};
