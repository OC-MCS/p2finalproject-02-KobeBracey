#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


class Enemy
{
private:
	Texture enemyTexture;
	Sprite enemy;
public:

	Enemy(Vector2f pos, Texture &tex)
	{
		if (!enemyTexture.loadFromFile("enemy.png"))
		{
			cout << "Unable to load enemy texture!" << endl;
			exit(EXIT_FAILURE);
		}
		enemy.setTexture(tex); //set the Alien's texture to the same texture passed by reference
		enemy.setPosition(pos.x, pos.y); //set the Alien's position to the position handed to the constructor
	}
	void moveEnemy()
	{
		const float DIST = 0.5f; //(will move 0.2 pixles every 60th of a second)
		enemy.move(0, DIST);
	}

	Vector2f getPosition()
	{
		return enemy.getPosition();
	}

	void resetYPos()
	{
		Vector2f temp = enemy.getPosition();
		enemy.setPosition(temp.x, 0);
	}

	void drawEnemy(RenderWindow &window)
	{
		window.draw(enemy);
	}

	bool isHit(FloatRect missileBounds)
	{
		bool isHit = false;
		FloatRect enemyBounds = enemy.getGlobalBounds();
		if (missileBounds.intersects(enemyBounds))
		{
			isHit = true;
		}
		return isHit;
	}

	bool atShip()
	{
		bool reached = false;
		if (getPosition().y > ((600 / 4) * 3) - 48)
		{
			reached = true;
		}
		return reached;
	}
};