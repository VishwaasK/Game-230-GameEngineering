// Our include guards
// These are critical for preventing collision related errors from a file accidentally getting fully included multiple times
#ifndef GAME_H
#define GAME_H

/* SFML Includes             *
 * Add to every SFML project */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>
#include "Ball.h"
#include "Paddle.h"

 /* Our Includes */


// Place our classes, functions, variables, and so forth in their own namespace to avoid naming collisions
namespace gm
{
	enum gameState {
		gameStop = 1,
		gamePlay = 2
	};

	enum gameMode {
		onePlayer = 1,
		twoPlayer = 2
	};

	/* Our Game Class                               *
	 * Implements the Game Loop Programming Pattern */
	class Game
	{
	private:
		sf::RenderWindow window;
		sf::Font font;
		sf::Text playerOneText;
		sf::Text playerTwoText;
		sf::Text winText;

		//default positions
		const sf::Vector2f ballDefaultPos = sf::Vector2f(445, 215);
		const sf::Vector2f paddle1DefaultPos = sf::Vector2f(20, 185);
		const sf::Vector2f paddle2DefaultPos = sf::Vector2f(875, 185);
		const sf::Vector2f winTextDefaultPos = sf::Vector2f(455, 225);

		//clock
		sf::Clock clock;
		float deltaTime;

		//paddles
		Paddle paddleOne;
		Paddle paddleTwo;

		//ball
		Ball ball;

		//game state
		gameState gameState;
		gameMode gameMode;

		//score
		int playerOneScore;
		int playerTwoScore;


	public:
		//Prototypes
		Game();
		void run(sf::RenderWindow& window);
		void handleInput(sf::RenderWindow& window);
		void update(sf::RenderWindow& window);
		void render(sf::RenderWindow& window);
		void reset();
		~Game();
	};
}

#endif
