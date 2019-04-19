#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
	Sprite bomb;

public:

	Bomb(Vector2f pos, Texture &BombTexture)
	{
		bomb.setTexture(BombTexture);
		bomb.setPosition(pos);
	}
	
	void drawBomb(RenderWindow &window)
	{
		window.draw(bomb);
	}
	void moveBomb()
	{
		const float DIST = 4.0f;
		bomb.move(0, DIST); 
	}

	bool onScreen()
	{
		bool onScreen = false;
		if (bomb.getPosition().y < 600)
		{
			onScreen = true;
		}

		return onScreen;
	}
	FloatRect getGlobalBounds()
	{
		return bomb.getGlobalBounds();
	}
};
