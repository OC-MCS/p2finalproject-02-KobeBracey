//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <time.h>
#include "level.h"
#include "Ship.h"
#include "enemy.h"
#include "enemyGroup.h"
#include "Missile.h"
#include "MissileGroup.h"
#include "Bomb.h"
#include "BombGroup.h"
#include "UI.h"

//============================================================
// YOUR HEADER WITH YOUR NAME GOES HERE. PLEASE DO NOT FORGET THIS
//============================================================


GameStateEnum resetState(int lives, int &destroyedAliens, GameStateEnum currentState, EnemyGroup &enemys);

int main()
{
	srand(time(NULL)); 
	int randNum;

	int lives = 3;
	int destroyedEnemys = 0;

	GameStateEnum currentState = START;

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	window.setFramerateLimit(60);

	UI userInt(window);
	Ship player(window);
	EnemyGroup enemys;
	MissileGroup missiles;
	BombGroup bombs;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) 
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					missiles.newMissile(player.getPosition());
				}
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				if (userInt.startPressed(mousePos))
				{
					currentState = LEVEL_ONE;

					enemys.makeEnemyList(currentState);
				}
			}
		}

		if (currentState == START)
		{
			userInt.startScreen(window);
		}
		else if (currentState == LEVEL_ONE || currentState == LEVEL_TWO)
		{
			userInt.gameScreen(window, lives, destroyedEnemys);

			if (player.shipHitMultiple(bombs.getBombList(), lives))
			{
				enemys.resetEnemyPos();
				player.resetShipPos(window);
			}
			if (enemys.reachedShip(lives))
			{
				player.resetShipPos(window);
			}
			player.moveShip(window);

			enemys.detectHitAliens(missiles.getMissileList(), destroyedEnemys);
			enemys.moveAlienArmy();

			missiles.moveMissileGroup();

			if (currentState == LEVEL_ONE)
			{
				randNum = rand() % 60 - 1;

			}
			else if (currentState == LEVEL_TWO)
			{
				randNum = rand() % 30 - 1;
			}
			if (randNum == 3)
			{
				if (!enemys.isListEmpty())
				{
					Vector2f tempPos = enemys.getRandomAlienPos(window, destroyedEnemys);
					bombs.newBomb(tempPos);
				}

			}
			bombs.moveBombs();

			player.drawShip(window);
			enemys.drawEnemys(window);
			missiles.drawMissileGroup(window);
			bombs.drawBombs(window);

			currentState = resetState(lives, destroyedEnemys, currentState, enemys);
		}
		else if (currentState == GAME_OVER)
		{
			userInt.startScreen(window);

			enemys.clearEnemys();
			destroyedEnemys = 0;
			lives = 3;

		}
		else if (currentState == WON)
		{
			userInt.winScreen(window);

			enemys.clearEnemys();
			destroyedEnemys = 0;
			lives = 3;
		}

		window.display();
	}

	return 0;
}

GameStateEnum resetState(int lives, int &killCount, GameStateEnum currentState, EnemyGroup &enemys)
{
	if (lives == 0)
	{
		currentState = GAME_OVER;
	}
	else if (killCount == 10)
	{
		if (currentState == LEVEL_TWO)
		{
			currentState = WON;
		}
		else
		{
			currentState = LEVEL_TWO;
			enemys.clearEnemys();
			enemys.makeEnemyList(currentState);
			killCount = 0;
		}
	}
	return currentState;
}

