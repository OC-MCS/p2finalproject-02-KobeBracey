#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "missile.h"
using namespace sf;

class MissileGroup
{
	Texture missileTexture;
	list<Missile> multipleMissiles;
public:

	MissileGroup()
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load Missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	void newMissile(Vector2f pos)
	{
		Missile temp(pos, missileTexture);
		multipleMissiles.push_back(temp);
	}

	void drawMissileGroup(RenderWindow &window)
	{
		list<Missile>::iterator iter;
		for (iter = multipleMissiles.begin(); iter != multipleMissiles.end(); iter++)
		{
			iter->drawMissile(window);
		}
	}

	void moveMissileGroup()
	{
		list<Missile>::iterator iter;
		for (iter = multipleMissiles.begin(); iter != multipleMissiles.end(); iter++)
		{
			iter->moveMissile();
		}

	}

	list<Missile> &getMissileList()
	{
		return multipleMissiles;
	}

	void clearMissiles()
	{
		multipleMissiles.clear();
	}
};
