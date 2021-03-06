#include "stdafx.h"
#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	const int windowWidth = 1024;
	const int windowHeight = 768;
	const int topPannelHeight = 90;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

	int score = 0;
	int lives = 3;

	Bat bat(windowWidth / 2, windowHeight - 20);

	Ball ball(windowWidth / 2, 100);

	Text hud;
	Font font;
	font.loadFromFile("DS-DIGIT.ttf");

	hud.setFont(font);
	hud.setCharacterSize(75);

	hud.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		/*
		Handle the player input
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		/*
		Update the frame
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		if (ball.getPosition().top > windowHeight)
		{
			ball.hitBottom();

			lives--;

			if (lives < 1) {
				score = 0;
				lives = 3;
			}

		}

		if (ball.getPosition().top - topPannelHeight < 0)
		{
			ball.reboundBatOrTop();
			score++;
		}

		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
		{
			ball.reboundSides();
		}

		if (ball.getPosition().intersects(bat.getPosition()))
		{
			ball.reboundBatOrTop();
		}

		ball.update();
		bat.update();

		// Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << "    Lives:" << lives;
		hud.setString(ss.str());
		/*
		Draw the frame
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		window.clear(Color(26, 128, 182, 255));
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.draw(hud);
		window.display();
	}

	return 0;
}

