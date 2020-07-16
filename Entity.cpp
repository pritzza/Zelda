#include "Entity.h"

Entity::Entity()
{
	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT / 3;
	width = 0;
	height = 0;
}

void Entity::getSpriteSheet(int spriteSheet)
{
	switch (spriteSheet)
	{
	case(0):
		texture.loadFromFile("Sprites/link.png");
		break;
	default:
		texture.loadFromFile("Sprites/link.png");
		break;
	}
}

int Creature::getDirection()
{
	if (yVel == 1)
		return 0;
	else if (yVel == -1)
		return 3;
	else if (xVel == -1)
		return 6;
	else if (xVel == 1)
		return 9;
	else
		return 0;
}

/* HITBOX:
_________________
| <----80%----> |
|               |
|   ^   o       |
|50%|           |
____V___________|
*/
void Creature::checkCollision(Map cmap, float elapsedTime) {
	float new_y = y + yVel * elapsedTime * speed;
	float new_x = x + xVel * elapsedTime * speed;

	if (xVel <= 0) {

		if (cmap.GetSolid(new_x/16 - 0.4f, y/16) || cmap.GetSolid(new_x / 16 - 0.4f, y / 16 + 0.5f)) {
			xVel = 0;
		}
	}
	else {
		if (cmap.GetSolid(new_x/16 + 0.4f, y/16) || cmap.GetSolid(new_x / 16 + 0.4f, y / 16 + 0.5f)) {
			xVel = 0;
		}
	}
	if (yVel <= 0) {
		if (cmap.GetSolid(x / 16 + 0.4f, new_y / 16) || cmap.GetSolid(x / 16 - 0.4f, new_y / 16)) {
			yVel = 0;
		}
	}
	else {
		if (cmap.GetSolid(x / 16 + 0.4f, new_y / 16 + 0.5f) || cmap.GetSolid(x / 16 - 0.4f, new_y / 16 + 0.5f)) {
			yVel = 0;
		}
	}
}

Player::Player()
{
	width = 16.0f;
	height = 16.0f;
	getSpriteSheet(0);
	sprite.setTexture(texture);
	sprite.setOrigin(width / 2.0f, height / 2.0f);
	updateSprite();
	sprite.setPosition(x, y);
	secondsPerUpdate = 0.3f;
}

void Player::setDirection(int d)
{
	if (d != oldDirection)
	{
		oldDirection = d;
		keyFrameDurationIndex = keyFrameDuration + 1;
	}
}

void Player::updateSprite()
{
	sf::IntRect frame((((getDirection()) + animationFrame) * 16), Link, width, height);
	sprite.setTextureRect(frame);
}

void Player::tick(float elapsedTime, const Map &cmap)
{
	//if (isMoving)
	//{
		if (downFlag)
		{	//South
			yVel = 1;
			xVel = 0;
		}
		else if (upFlag)	//North
		{	
			yVel = -1;
			xVel = 0;
		}
		else if (leftFlag)	//East
		{	
			xVel = -1;
			yVel = 0;
		}
		else if (rightFlag)	//West
		{	
			xVel = 1;
			yVel = 0;
		}
		else
		{
			xVel = 0;
			yVel = 0;
		}

		checkCollision(cmap, elapsedTime);

		y += yVel * elapsedTime * speed;
		x += xVel * elapsedTime * speed; //elapsedTime;

					// Check screen boundaries
		if (x < 0) x = 0;
		if (x > WINDOW_WIDTH) x = WINDOW_WIDTH;
		if (y < 0) y = 0;
		if (y > WINDOW_HEIGHT) y = WINDOW_HEIGHT;

		sprite.setPosition(x, y);

		if (xVel || yVel)
		{
			keyFrameDurationIndex += elapsedTime;
			if (keyFrameDurationIndex > secondsPerUpdate)
			{
				animationFrame = (animationFrame + 1) % 2;
				keyFrameDurationIndex = 0;
			}
			updateSprite();
		}

		

	//if (keyFrameDurationIndex > keyFrameDuration)
	//{
	//	animationFrame = (animationFrame + 1) % 2;
	//	updateSprite();
	//	keyFrameDurationIndex = 0;
	//}
	//else
	//	keyFrameDurationIndex++;



}
