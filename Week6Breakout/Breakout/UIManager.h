#ifndef	UIMANAGER_H
#define UIMANAGER_H

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

namespace gm {
	class UIManager {
	private:
		//font and text
		sf::Font f;
		sf::Font f2;

		sf::Text playerHP;
		sf::Text playerScore;
		sf::Text levelNumText;
		sf::Text lose;
		sf::RectangleShape ceilingLine;

		//default text position
		const sf::Vector2f loseTextDefaultPos = sf::Vector2f(390, 300);

	public:
		UIManager();
		UIManager(int health, int score, int levelNum);
		void render(sf::RenderWindow& window);
		void updateHP(int hp);
		void updateScore(int score);
		void updateLevelText(int levelNum);
		void updateLoseText(std::string str);
		~UIManager();
	};
}
#endif UIMANAGER_H