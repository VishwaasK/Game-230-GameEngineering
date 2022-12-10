#ifndef GAME_H
#define GAME_H

//Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>
#include "Paddle.h"
#include "Ball.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "Level.h"

namespace gm {
	enum gameState {
		gameStop = 1,
		gamePlay = 2,
		gameStart = 3
	};

	class Game {
	private:
		Level l;

		//brick size
		const sf::Vector2f brickSize = sf::Vector2f(78, 28);

		//sound manager
		SoundManager sm;

		//ui manager
		UIManager ui;

		//ball positions for testing
			//top collision
		//const sf::Vector2f ballDefaultPos = sf::Vector2f(350, 80);
			//left collision
		//const sf::Vector2f ballDefaultPos = sf::Vector2f(0, 280);

		//default position values
		const sf::Vector2f ballDefaultPos = sf::Vector2f(380, 550);
		const sf::Vector2f paddleDefaultPos = sf::Vector2f(350, 570);


		const float ceilingY = 50.0f;

		//clock
		sf::Clock c;
		float deltaTime;

		//paddles
		Paddle paddle1;

		//ball
		Ball ball;

		//game state
		gameState gameState;

		//health and score
		int playerHealth;
		int playerScore;
		int levelNum;
	public:
		//Prototypes
		Game();
		void play(sf::RenderWindow& window);
		void handleInput(sf::RenderWindow& window);
		void update(sf::RenderWindow& window);
		void render(sf::RenderWindow& window);
		//returns 0 for top/bottom, 1 for sides
		int checkCollideBrick(Brick* b);
		//reset game
		void reset();
		~Game();
	};
}

#endif