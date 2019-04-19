#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Bomb.h"
#include <list>

class BombGroup
{
	Texture BombTexture;
	list<Bomb> bombs; 
public:

	BombGroup()
	{
		if (!BombTexture.loadFromFile("bomb.png"))
		{
			cout << "Unable to load Bomb texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	void newBomb(Vector2f pos)
	{
		Bomb temp(pos, BombTexture);
		bombs.push_back(temp);
	}

	void drawBombs(RenderWindow &window)
	{
		list<Bomb>::iterator iter;
		for (iter = bombs.begin(); iter != bombs.end(); iter++)
		{
			iter->drawBomb(window);
		}
	}

	void moveBombs()
	{
		list<Bomb>::iterator iter;
		for (iter = bombs.begin(); iter != bombs.end(); iter++)
		{
			iter->moveBomb();
		}
	}

	list<Bomb> &getBombList()
	{
		return bombs;
	}

	void clearBombs()
	{
		bombs.clear();
	}
};
