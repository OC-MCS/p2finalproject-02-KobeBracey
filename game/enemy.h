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
		enemy.setTexture(tex);
		enemy.setPosition(pos.x, pos.y);
	}
	void moveEnemy()
	{
		const float DIST = 0.5f;
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