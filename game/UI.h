#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class UI
{
private:
	RectangleShape startBtn;
	Texture starsTexture;
	Sprite background;
	int lifes;
	Font font;
public:
	UI (RenderWindow &window)
	{
		if (!starsTexture.loadFromFile("stars.jpg"))
		{
			cout << "Unable to load stars texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		{
			cout << "Unable to load fonts" << endl;
			exit(EXIT_FAILURE);
		}

		background.setTexture(starsTexture);
		background.setScale(1.5, 1.5);

		startBtn.setFillColor(Color::Green);
		startBtn.setPosition(350, 275);
		Vector2f buttonSize1(110, 60);
		startBtn.setSize(buttonSize1);

	}

	void startScreen(RenderWindow& window)
	{

		Text title("Start", font, 50);
		title.setPosition(350, 275); 

		window.draw(startBtn);
		window.draw(title);
	}

	bool startPressed(Vector2f mouse)
	{
		bool isPressed = false;
		if (startBtn.getGlobalBounds().contains(mouse))
		{
			isPressed = true;
		}
		return isPressed;
	}

	void gameScreen(RenderWindow & window, int lives, int killCount)
	{
		window.draw(background);
		Text livesCounter("Lives: " + to_string(lives), font, 15);
		livesCounter.setPosition(740, 2);
		window.draw(livesCounter);
		Text aliensCounter("Kills: " + to_string(killCount), font, 15);
		aliensCounter.setPosition(3, 2);
		window.draw(aliensCounter);
	}

	void winScreen(RenderWindow& window)
	{
		Text winner("YOU WIN", font, 50);
		winner.setPosition(330, 50);

		window.draw(background);
		window.draw(winner);
		window.draw(startBtn);
	}
};