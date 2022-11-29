#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <vector>

//namespaces
using namespace std;

// Global Variables
sf::Window window;
sf::Music bgm;
sf::SoundBuffer sfxBuffer;
sf::Sound sfx;
sf::Texture tileTexture[20];
sf::Sprite tileSprite;
int SelectedSprite;
map<int, sf::Sprite*>ViewSprite;
sf::Font font;
sf::Text text;
sf::RectangleShape stem;
sf::CircleShape flower;
sf::CircleShape flowerBulb;
sf::Vector2f CurrentPos = { 0,0 };
int CurrentLevel[10][10];
int CurrentTile = 0;
int TileRow = 0;
int TileColumn = 0;
int TileHeight = 70;
int TileWidth = 70;
bool TileAdd = true;
bool TileRemove = true;

// Protoypes
void setup(sf::RenderWindow& window);
void handleInput(sf::RenderWindow& window, sf::Event& e);
void update(sf::RenderWindow& window);
void render(sf::RenderWindow& window);

// Main, the applicaiton entry function
int main()
{
    // Make the window for the game
    // Rendering stuff
    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML works!");

    // Handle all the setup that should be done once before we enter the game loop
    setup(window);

    // This is the game loop!
    // Every input, logic, and rendering is handled here
    while (window.isOpen())
    {
        // Checking for events from the window
        sf::Event event;
        while (window.pollEvent(event))
        {
            handleInput(window, event);
        }

        update(window);

        render(window);
    }

    // The game exits normally hence send a normal exit status integer back
    return 0;
}

// Function to handle all setup that needs to be done before entering the game loop
void setup(sf::RenderWindow& window)
{
    // Initializing  Level
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            CurrentLevel[i][j] = -1;
        }
    }

    // Load audio
    if (!bgm.openFromFile("Assets/Audio/BGM.wav"))
    {
        cout << "Error loading background music!" << endl;
    }
    bgm.play();
    bgm.setLoop(true);

    // Sound Effects SFX
    if (!sfxBuffer.loadFromFile("Assets/Audio/Victory Jingle SFX.wav"))
    {
        cout << "Error loading sfx!" << endl;
    }

    sfx.setBuffer(sfxBuffer);

    /* Texture
    if (!tileTexture.loadFromFile("Assets/Graphics/Tile1.png"))
    {
        cout << "Error loading image Tile2.png" << endl;
    }*/

    //Load textures
    for (int i = 1; i <= 20; i++)
    {
        if (!tileTexture[i - 1].loadFromFile("Assets/Graphics/Platformer-" + to_string(i) + ".png"))
        {
            cout << "Can not locate a texture!" << endl;

        }
        else
            cout << "Loaded texture" << i << endl;
    }


    SelectedSprite = 0;
    tileSprite.setTexture(tileTexture[SelectedSprite]);

    //Dimension for Texture 
    if (tileTexture[SelectedSprite].getSize().x % TileWidth != 0 || tileTexture[SelectedSprite].getSize().y % TileHeight != 0)
    {
        cout << "Error Tile row/column size not divisible by tile Size";
        exit(-1);
    }
    else
    {
        TileRow = tileTexture[SelectedSprite].getSize().y / TileHeight;
        TileColumn = tileTexture[SelectedSprite].getSize().x / TileWidth;
    }



    // Sprite
    tileSprite.setTexture(tileTexture[SelectedSprite]);
    //tileSprite.setPosition(0, 0);

    // Font
    if (!font.loadFromFile("Assets/Fonts/OneVerseRegular-PKM4x.ttf"))
    {
        cout << "Error loading font OneVerseRegular-PKM4x.ttf!" << endl;
    }

    /*
    // Text
    // Select the font
    text.setFont(font);
    // Set the string to display
    text.setString("Hello, world!");
    // Set the character size
    text.setCharacterSize(128); // In pixels, not points!
    // Set the color
    text.setFillColor(sf::Color::White);
    // Set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    // Set the text position
    text.setPosition(96, 96);
    // Shapes
    stem.setFillColor(Color::Green);
    stem.setPosition(397, 430);
    stem.setSize(Vector2f(6, 100));
    flower.setFillColor(Color::Magenta);
    flower.setPosition(375, 405);
    flower.setRadius(25);
    flowerBulb.setFillColor(Color::Yellow);
    flowerBulb.setPosition(392, 422);
    flowerBulb.setRadius(8);
    */

}

//Function to handle the input portion of our game loop programming pattern
void handleInput(sf::RenderWindow& window, sf::Event& e)
{
    if (e.type == sf::Event::Closed)
        window.close();

    //To display selected sprite on mouse position realtime
    if (e.MouseMoved)
    {
        tileSprite.setPosition(float(sf::Mouse::getPosition(window).x / TileWidth * TileWidth), float(sf::Mouse::getPosition(window).y / TileHeight * TileHeight));
    }


    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Up)
        {
            (SelectedSprite == sizeof(tileTexture) / sizeof(sf::Texture) - 1) ? 0 : SelectedSprite++;
            tileSprite.setTexture(tileTexture[SelectedSprite]);
        }
        else if (e.key.code == sf::Keyboard::Down)
        {
            (SelectedSprite == 0) ? sizeof(tileTexture) / sizeof(sf::Texture) - 1 : SelectedSprite--;
            tileSprite.setTexture(tileTexture[SelectedSprite]);

        }
    }
    //Left mouse click plays sfx
    //Left mouse click adds sprite
    if (TileAdd && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //sfx.play();
        TileAdd = false;
        CurrentPos.x = sf::Mouse::getPosition(window).x / TileWidth;
        CurrentPos.y = sf::Mouse::getPosition(window).y / TileHeight;

        //checking posistion and level array beofre entering if - for debugging
        cout << CurrentPos.x << " " << CurrentPos.y << endl;
        cout << "first " << CurrentLevel[sf::Mouse::getPosition(window).y / TileHeight][sf::Mouse::getPosition(window).x / TileWidth] << endl;

        //position.x * 10 because level array 0-99 blocks - example cordinate (9,9) is {(9*10)+9} space inthe level array
        if (0 <= (CurrentPos.x * 10 + CurrentPos.y) <= 99)
        {
            //for debugging
            cout << CurrentLevel[sf::Mouse::getPosition(window).y][sf::Mouse::getPosition(window).x] << endl;

            if (CurrentLevel[sf::Mouse::getPosition(window).y / TileHeight][sf::Mouse::getPosition(window).x / TileWidth] != CurrentTile)
            {
                //new allocates bytpes of object of that size -  in this case, Sprites - otherwise throws exception or  return nullpointer
                sf::Sprite* thatSprite = new sf::Sprite(tileTexture[SelectedSprite], sf::IntRect(CurrentTile / TileRow * TileWidth, CurrentTile / TileColumn * TileHeight, TileWidth, TileHeight));
                thatSprite->setPosition(sf::Mouse::getPosition(window).x / TileWidth * TileWidth, sf::Mouse::getPosition(window).y / TileHeight * TileHeight);
                /*if (ViewSprite.count(CurrentPos.x * 10 + CurrentPos.y))
                {
                    delete ViewSprite[CurrentPos.x * 10 + CurrentPos.y];
                    ViewSprite.erase(CurrentPos.x * 10 + CurrentPos.y);
                }
                */
                ViewSprite.insert({ CurrentPos.x * 10 + CurrentPos.y,thatSprite });
                CurrentLevel[sf::Mouse::getPosition(window).y / TileHeight][sf::Mouse::getPosition(window).x / TileWidth] = CurrentTile;
            }
        }
        TileAdd = true;

    }
    else if (TileRemove && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        TileRemove = false;
        CurrentPos.x = sf::Mouse::getPosition(window).x / TileWidth;
        CurrentPos.y = sf::Mouse::getPosition(window).y / TileHeight;
        if (0 <= CurrentPos.x * 10 + CurrentPos.y <= 99)
        {
            if (CurrentLevel[sf::Mouse::getPosition(window).y / TileHeight][sf::Mouse::getPosition(window).x / TileWidth] != -1)
            {
                //new allocates memory to Sprite* thats why after erasing memory need to be freed therefore delete
                delete ViewSprite[CurrentPos.x * 10 + CurrentPos.y];
                ViewSprite.erase(CurrentPos.x * 10 + CurrentPos.y);
            }
            CurrentLevel[sf::Mouse::getPosition(window).y / TileHeight][sf::Mouse::getPosition(window).x / TileWidth] = -1;
        }
        TileRemove = true;


    }
    //screenshot


        // Space key creates a screenshot
    if (e.key.code == sf::Keyboard::Space)
    {
        sf::Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        if (texture.copyToImage().saveToFile("Grid Game Level.png"))
        {
            std::cout << "Screenshot saved to Grid Game Level.png" << std::endl;
        }


    }


}

//Function to handle the logic and game step portion of our game loop programming pattern
void update(sf::RenderWindow& window)
{

}

//Function to handle the drawing portion of our game loop programming pattern
void render(sf::RenderWindow& window)
{
    // This clears the window at the beginning of every frame
    window.clear();
    for (auto s : ViewSprite)
    {
        window.draw(*s.second);
    }


    // Draw our sprites first
    window.draw(tileSprite);

    /*
    // Draw our flower on top of the sprites
    window.draw(stem);
    window.draw(flower);
    window.draw(flowerBulb);
    // Draw our text last on top of everything else
    window.draw(text);
    */

    // Display the window buffer for this frame
    window.display();
}