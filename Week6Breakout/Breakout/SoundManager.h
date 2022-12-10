#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

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
	class SoundManager {
	private:
		//sounds
		sf::SoundBuffer paddleHitSfx;
		sf::SoundBuffer wallHitSfx;
		sf::SoundBuffer winSfx;
		sf::SoundBuffer lifeLoseSfx;
		sf::SoundBuffer breakSfx;
		sf::SoundBuffer shatterSfx;
		sf::SoundBuffer loseSfx;
		sf::SoundBuffer arr[7];
		sf::Sound s;
	public:
		//Prototypes
		SoundManager();
		//0 = paddleHitSfx, 1 = wallHitSfx, 2 = winSfx, 3 = lifeLoseSfx, 4 = breakSfx, 5 = shatterSfx, 6 = loseSfx
		void playSfx(int index);
		~SoundManager();
	};
}

#endif