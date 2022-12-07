// We need to include our header file to implement the function prototypes of our Game class
#include "Game.h"

// Since we are in our private .cpp file, it's fine to use a namespace here
using namespace gm;
using namespace sf;
using namespace std;


// Implement constructor, this will effectively be a setup function as the game gets more complex
Game::Game() : clock(), deltaTime(0), paddleOne(paddle1DefaultPos, Vector2f(15, 80)), paddleTwo(paddle2DefaultPos, Vector2f(15, 80)), ball(ballDefaultPos, Vector2f(20, 20)), gameState(gameState::gameStop), gameMode(gameMode::onePlayer) {	// Set our fps to 60
    window.setFramerateLimit(60);
    playerOneScore = 0;
    playerTwoScore = 0;

    //load font
    font.loadFromFile("arial.ttf");

    //set text
    playerOneText.setFont(font);
    playerTwoText.setFont(font);
    winText.setFont(font);

    playerOneText.setString(to_string(playerOneScore));
    playerTwoText.setString(to_string(playerTwoScore));
    winText.setString("");

    playerOneText.setCharacterSize(64);
    playerTwoText.setCharacterSize(64);
    winText.setCharacterSize(40);

    playerOneText.setPosition(Vector2f(90.0f, 35.0f));
    playerTwoText.setPosition(Vector2f(788.0f, 35.0f));
    winText.setPosition(winTextDefaultPos);

}

void Game::run(RenderWindow& window) {
    // This is our game loop!
    // All input, logic, and rendering should be handled here
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        // Every frame we...
        // Handle input first...
        handleInput(window);

        // Then update...
        update(window);

        // Then render...
        render(window);
    }
}

// Implements the handle input portion of our Game Loop Programming Pattern
void Game::handleInput(RenderWindow& window) {
    // Check for events from the window
    // E.g., is the window being closed?
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            //press space to begin play
            if (gameState == gameStop)
            {
                if (event.key.code == Keyboard::Space) {
                    gameState = gamePlay;
                    winText.setString("");
                }
                if (event.key.code == Keyboard::Num1)
                {
                    gameMode = onePlayer;
                }
                if (event.key.code == Keyboard::Num2)
                {
                    gameMode = twoPlayer;
                }
            }

            //controls of player 1 
            if (event.key.code == Keyboard::W)
            {
                paddleOne.setMoveDirection(Up);
            }
            if (event.key.code == Keyboard::S) {
                paddleOne.setMoveDirection(Down);
            }

            //controls of player 2 
            //only on two player mode
            if (gameMode == twoPlayer)
            {
                if (event.key.code == Keyboard::Up)
                {
                    paddleOne.setMoveDirection(Up);
                }
                if (event.key.code == Keyboard::Down) {
                    paddleTwo.setMoveDirection(Down);
                }
            }
        }

        if (event.type == Event::KeyReleased) {
            //player 1 on key release
            if (event.key.code == Keyboard::W && paddleOne.getMoveDirection() == moveDirection::Up) {
                paddleOne.setMoveDirection(moveDirection::None);
            }
            if (event.key.code == Keyboard::S && paddleOne.getMoveDirection() == moveDirection::Down) {
                paddleOne.setMoveDirection(moveDirection::None);
            }

            //player 2 on key release
            //only on two player mode
            if (gameMode == twoPlayer)
            {
                if (event.key.code == Keyboard::Up && paddleTwo.getMoveDirection() == moveDirection::Up) {
                    paddleTwo.setMoveDirection(moveDirection::None);
                }
                if (event.key.code == Keyboard::Down && paddleTwo.getMoveDirection() == moveDirection::Down) {
                    paddleTwo.setMoveDirection(moveDirection::None);
                }
            }
        }

        //Exit program
        if (event.type == Event::Closed)
            window.close();
    }
}

// Implements the update portion of our Game Loop Programming Pattern
void Game::update(RenderWindow& window) {
    {
        if (gameState == gamePlay)
        {
            paddleOne.update(window, deltaTime);
            paddleTwo.update(window, deltaTime);
            ball.update(window, deltaTime);

            //move paddle 2
            //only on one player mode
            if (gameMode == onePlayer)
            {
                if (paddleTwo.getCollider().top > ball.getCollider().top + ball.getCollider().height / 2)
                {
                    paddleTwo.setMoveDirection(Up);
                }
                else if (paddleTwo.getCollider().height + paddleTwo.getCollider().top < ball.getCollider().top + ball.getCollider().height / 2)
                {
                    paddleTwo.setMoveDirection(Down);
                }
                else
                {
                    paddleTwo.setMoveDirection(None);
                }
            }

            //if hits paddle or wall
            if (ball.getCollider().top <= 0 || ball.getCollider().height + ball.getCollider().top >= window.getSize().y)
            {
                ball.bounce(1);
            }
            if ((paddleOne.collide(ball.getCollider()) || paddleTwo.collide(ball.getCollider())) && ball.getCanCollide())
            {
                ball.bounce(2);
            }

            //while ball is not intersecting with a paddle
            {
                if ((paddleOne.collide(ball.getCollider()) || paddleTwo.collide(ball.getCollider())) == false && ball.getCanCollide() == false)
                {
                    ball.changeCanCollide();
                }
            }

            //if out of bounds
            if (ball.getCollider().left <= 0 || ball.getCollider().left + ball.getCollider().width >= window.getSize().x)
            {
                //pause game
                gameState = gameStop;


                if (ball.getCollider().left <= 0)
                {
                    playerTwoScore++;
                    playerTwoText.setString(to_string(playerTwoScore));
                }
                else
                {
                    playerOneScore++;
                    playerOneText.setString(to_string(playerOneScore));
                }
                cout << "player 1 score: " << playerOneScore << " \n" << "player 2 score: " << playerTwoScore << endl;
                //reset positions
                reset();
            }
        }
    }
}

// Implements the render portion of our Game Loop Programming Pattern
void Game::render(RenderWindow& window)
{
    window.clear();

    window.draw(playerOneText);
    window.draw(playerTwoText);
    window.draw(winText);
    paddleOne.render(window, deltaTime);
    paddleTwo.render(window, deltaTime);
    ball.render(window, deltaTime);

    window.display();

}

//Reset the game 
void Game::reset()
{
    paddleOne.setPosition(paddle1DefaultPos);
    paddleTwo.setPosition(paddle2DefaultPos);
    paddleOne.setMoveDirection(None);

    ball.setPosition(ballDefaultPos);
    ball.resetVelocity();

    if (playerOneScore == 5 || playerTwoScore == 5)
    {

        if (playerOneScore == 5)
        {
            cout << "player 1 wins!" << endl;
            winText.setString("Player 1 Wins!");
            winText.setPosition(Vector2f(455 - winText.getGlobalBounds().width / 2.0f, 67.0f - winText.getGlobalBounds().height / 2.0f));
        }
        else
        {
            cout << "player 2 wins!" << endl;
            winText.setString("Player 2 Wins!");
            winText.setPosition(Vector2f(455 - winText.getGlobalBounds().width / 2.0f, 67.0f - winText.getGlobalBounds().height / 2.0f));
        }
        playerOneScore = 0;
        playerTwoScore = 0;

        playerOneText.setString(to_string(playerOneScore));
        playerTwoText.setString(to_string(playerTwoScore));
    }
}
// Implement destructor, make sure we free up any memory that we allocated here!
Game::~Game() {

}