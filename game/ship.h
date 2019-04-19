#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "bomb.h"
#include "bombGroup.h"

class Ship
{
private:
	Texture shipTexture;
	Sprite ship;
public:

	Ship(RenderWindow &window)
	{
		if (!shipTexture.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}

		ship.setTexture(shipTexture);

		float shipX = window.getSize().x / 2.0f;
		float shipY = 550;
		ship.setPosition(shipX, shipY);
	}

	void drawShip(RenderWindow &window)
	{
		window.draw(ship);
	}

	void moveShip(RenderWindow &window)
	{
		const float DISTANCE = 5.0;

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			ship.move(-DISTANCE, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			ship.move(DISTANCE, 0);
		}
	}

	Vector2f getPosition()
	{
		return ship.getPosition();
	}

	void resetShipPos(RenderWindow &window)
	{
		float shipX = window.getSize().x / 2.0f;
		float shipY = (window.getSize().y / 4.0f) * 3;
		ship.setPosition(shipX, shipY);
	}

	bool shipHit(FloatRect bombBounds)
	{
		bool isHit = false;
		FloatRect shipBounds = ship.getGlobalBounds();
		if (bombBounds.intersects(shipBounds))
		{
			isHit = true;
		}
		return isHit;
	}

	bool shipHitMultiple(list<Bomb> &multipleBombs, int &lives)
	{
		list<Bomb>::iterator Iter; 
		bool isHit = false;
		for (Iter = multipleBombs.begin(); Iter != multipleBombs.end() && !isHit;)
		{
			isHit = shipHit(Iter->getGlobalBounds());
			if (isHit)
			{
				Iter = multipleBombs.erase(Iter);
				lives -= 1;
			}
			else
			{
				Iter++;
			}
		}
		return isHit;
	}
};