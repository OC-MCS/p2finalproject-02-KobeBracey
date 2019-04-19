#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <list>
#include "enemy.h"
#include "missile.h"
#include "missileGroup.h"
#include "bomb.h"
#include "level.h"
using namespace sf;


class EnemyGroup
{
private:
	Texture enemyTextureOne;
	Texture enemyTextureTwo;
	list<Enemy> enemyList;
	Vector2f pos;
public:

	EnemyGroup()
	{
		if (!enemyTextureOne.loadFromFile("enemy.png"))
		{
			cout << "Unable to load enemy texture!" << endl;
			exit(EXIT_FAILURE);
		}

		if (!enemyTextureTwo.loadFromFile("enemy.png"))
		{
			cout << "Unable to load enemy texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	void makeEnemyList(GameStateEnum currentState)
	{
		pos.x = 20;
		pos.y = 10;
		for (int i = 0; i < 10; i++)
		{
			if (currentState == LEVEL_ONE)
			{
				Enemy temp(pos, enemyTextureOne);
				enemyList.push_back(temp);
			}
			else if (currentState == LEVEL_TWO)
			{
				Enemy temp(pos, enemyTextureTwo);
				enemyList.push_back(temp);
			}
			pos.x += 80;
		}
	}

	void clearEnemys()
	{
		enemyList.clear();
	}

	void drawEnemys(RenderWindow &window)
	{
		list<Enemy>::iterator iter;
		for (iter = enemyList.begin(); iter != enemyList.end(); iter++)
		{
			iter->drawEnemy(window);
		}
	}

	void moveAlienArmy()
	{
		list<Enemy>::iterator iter;
		for (iter = enemyList.begin(); iter != enemyList.end(); iter++)
		{
			iter->moveEnemy();
		}
	}

	void detectHitAliens(list<Missile> &multipleMissiles, int &destroyed)
	{
		bool isHit = false; 
		list<Enemy>::iterator enemyIter; 
		list<Missile>::iterator missileIter; 
		for (enemyIter = enemyList.begin(); enemyIter != enemyList.end();)
		{
			isHit = false;
			for (missileIter = multipleMissiles.begin(); missileIter != multipleMissiles.end() && !isHit;)
			{
				isHit = enemyIter->isHit(missileIter->getGlobalBounds());
				if (isHit)
				{
					missileIter = multipleMissiles.erase(missileIter); 

				}
				else
				{
					missileIter++;
				}
			}
			if (isHit)
			{
				enemyIter = enemyList.erase(enemyIter); 
				destroyed += 1; 
			}
			else
			{
				enemyIter++;
			}
		}
	}


	bool isListEmpty()
	{
		bool isEmpty = false;
		if (enemyList.size() < 1)
		{
			isEmpty = true;
		}
		return isEmpty;
	}

	Vector2f getRandomAlienPos(RenderWindow &window, int destroyedAliens)
	{
		Vector2f returnValue;
		int randEnemy = rand() % enemyList.size();
		list<Enemy>::iterator Iter; 
		Iter = enemyList.begin();
		advance(Iter, randEnemy);
		return Iter->getPosition();
	}

	void resetEnemyPos()
	{
		list<Enemy>::iterator iter;
		for (iter = enemyList.begin(); iter != enemyList.end(); iter++)
		{
			iter->resetYPos();
		}
	}

	bool reachedShip(int &lives)
	{
		bool reached = false;
		list<Enemy>::iterator iter;
		if (enemyList.size() > 0)
		{
			if (enemyList.begin()->atShip())
			{
				lives -= 1;
				resetEnemyPos();
			}
		}

		return reached;
	}

};
