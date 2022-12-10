#include "Game.h"

//Namespaces
using namespace sf;
using namespace std;
using namespace gm;


//Functions


//Main
int main()
{
    //create window
    RenderWindow window(VideoMode(780, 600), "SFML works!");

    Game g;

    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);

    //game loop
    while (window.isOpen())
    {
        g.play(window);
    }

    return 0;
}