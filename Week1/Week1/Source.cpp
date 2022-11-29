#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <vector>


int main()
{
    //editor window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    float BrushDimension = 50.f;

    //enum for range of values in brush i.e. circle and square brush 
    enum BrushShapes {Circle, Square};

    //making brush shapes
    sf::CircleShape shape(BrushDimension);
    sf::RectangleShape square(sf::Vector2f(BrushDimension * 1.f, BrushDimension * 1.f));

    //local variable of brush selection enum to change brush type in the future
    //Circle Brush is active by default
    BrushShapes brushkind = Circle;
    sf::Shape* CurrentBrush = &shape;
    shape.setFillColor(sf::Color::Green);
    square.setFillColor(sf::Color::Green);  

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            //window close handle
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                //RED
                if (event.key.code == sf::Keyboard::R)
                {
                    shape.setFillColor(sf::Color::Red);
                    square.setFillColor(sf::Color::Red);
                }
                //GREEN
                else if (event.key.code == sf::Keyboard::G)
                {
                    shape.setFillColor(sf::Color::Green);
                    square.setFillColor(sf::Color::Green);
                }
                //BLUE
                else if (event.key.code == sf::Keyboard::B)
                {
                    shape.setFillColor(sf::Color::Blue);
                    square.setFillColor(sf::Color::Blue);
                }
                //BLACK
                else if (event.key.code == sf::Keyboard::V)
                {
                    shape.setFillColor(sf::Color::Black);
                    square.setFillColor(sf::Color::Black);
                }  
                //Size Decrement
                else if (event.key.code == sf::Keyboard::Left)
                {
                    if (BrushDimension >= 5)
                    {
                        BrushDimension -= 4.f;
                    }
                    else
                    {
                        BrushDimension = 1.f; 
                    }
                    square.setSize(sf::Vector2f(BrushDimension * 2.f, BrushDimension * 2.f));
                    shape.setRadius(BrushDimension);                    
                }
                //Size Increment
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (BrushDimension < 50.f)
                    {
                        BrushDimension += 4.f;
                    }
                    else
                    {
                        BrushDimension = 50.f;
                    }
                    square.setSize(sf::Vector2f(BrushDimension * 2.f, BrushDimension * 2.f));
                    shape.setRadius(BrushDimension);
                }
                //Shape Change Circle
                else if (event.key.code == sf::Keyboard::S)
                {
                    if (brushkind == Circle)
                    {
                      
                        square.setFillColor(sf::Color::Red);
                        square.setSize(sf::Vector2f(BrushDimension * 2.f, BrushDimension * 2.f));
                        CurrentBrush = &square;
                        brushkind = Square;                        
                    }
                    //Shape Change Square
                    else if (brushkind == Square)
                    {                        
                        shape.setFillColor(sf::Color::Green);
                        shape.setRadius(BrushDimension);
                        CurrentBrush = &shape;
                        brushkind = Circle;                        
                    }
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    sf::Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    if (texture.copyToImage().saveToFile("Homework 1 Screenshot.png"))
                    {
                        std::cout << "Screenshot saved to Homework 1 Screenshot.png" << std::endl;
                    }
                }
            }
        }
        
        shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        square.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        window.draw(*CurrentBrush);             
        window.display();        
    }
    return 0;
}