/* My Classes */
#include "Game.h"

/* Namespaces */
using namespace gm;

/* Functions */
// Main, our applicaiton entry function
int main()
{
    sf::RenderWindow window(sf::VideoMode(910, 450), "SFML works!");
    Game game;

    while (window.isOpen())
    {
        game.run(window);
    }


    // The game has exited normally so send a normal exit status integer back
    return 0;
}