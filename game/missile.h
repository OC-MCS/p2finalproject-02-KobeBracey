#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
	Sprite missile;
public:

	Missile(Vector2f pos, Texture &missileTexture)
	{
		missile.setTexture(missileTexture);
		missile.setPosition(pos);
	}

	void drawMissile(RenderWindow &window)
	{
		window.draw(missile);
	}

	void moveMissile()
	{
		const float DIST = 5.0f; 
		missile.move(0, -DIST); 
	}

	FloatRect getGlobalBounds()
	{
		return missile.getGlobalBounds();
	}

	bool isMissileOnScreen()
	{
		bool onScreen = false;
		if (missile.getPosition().y < 0)
		{
			onScreen = true;
		}
		return onScreen;
	}

};
