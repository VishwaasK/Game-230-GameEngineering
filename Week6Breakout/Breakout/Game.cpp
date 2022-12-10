#include "Game.h"

using namespace std;
using namespace sf;
using namespace gm;

//constructor
Game::Game() :c(), sm(), ui(playerHealth = 3, playerScore = 0, levelNum = 1), deltaTime(0), paddle1(paddleDefaultPos, Vector2f(80, 15)), ball(ballDefaultPos, Vector2f(20, 20)), gameState(gameState::gameStart) {
}

//functions
void Game::play(RenderWindow& window) {
    while (window.isOpen()) {
        deltaTime = c.restart().asSeconds();
        handleInput(window);
        update(window);
        render(window);
    }
}

void Game::handleInput(RenderWindow& window) {
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            if (gameState == gameStop)
            {
                //restart game
                if (event.key.code == Keyboard::R)
                {
                    ui.updateHP(playerHealth = 3);
                    ui.updateScore(playerScore = 0);
                    ui.updateLevelText(levelNum = 1);
                    ui.updateLoseText("");
                    l.reset();
                    gameState = gameStart;
                }
            }
            if (event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        //paddle controls
        if (gameState != gameStop)
        {
            if (event.MouseMoved) {
                float xPosition = float(event.mouseMove.x);
                if (xPosition + paddle1.getCollider().width >= window.getSize().x)
                {
                    xPosition = window.getSize().x - paddle1.getCollider().width;
                }
                paddle1.setPosition(Vector2f(xPosition, paddle1.getPosition().y));
            }
        }

        if (event.type == Event::MouseButtonPressed)
        {
            //left click to begin play
            if (gameState == gameStart)
            {
                if (event.mouseButton.button == Mouse::Left) {
                    gameState = gamePlay;
                    ui.updateLoseText("");
                }
            }
        }

        //Exit program
        if (event.type == Event::Closed)
            window.close();
    }
}

void Game::update(RenderWindow& window) {
    {
        //game state is start
        if (gameState == gameStart) {
            paddle1.update(window, deltaTime);
            ball.setPosition(Vector2f(paddle1.getMidPosition().x - 10, paddle1.getMidPosition().y - 20));
        }
        else if (gameState == gamePlay) //game state is play
        {
            paddle1.update(window, deltaTime);
            ball.update(window, deltaTime);
            l.update(window);

            if (l.checkFinished())
            {
                reset();
                l.reset();
                sm.playSfx(2);
                if (l.getCurrentLevel() == 3)
                {
                    l.setLevel(1);
                }
                else
                {
                    l.setLevel(l.getCurrentLevel() + 1);
                }
                ui.updateLevelText(levelNum += 1);
            }

            //if hits wall, ceiling, or paddle
            if (ball.getCollider().left <= 0 || ball.getCollider().width + ball.getCollider().left >= window.getSize().x)
            {
                sm.playSfx(1);
                ball.bounce(1);
            }
            if (ball.getCollider().top <= ceilingY)
            {
                sm.playSfx(1);
                ball.bounce(2);
            }
            if (paddle1.collide(ball.getCollider()) && ball.getCanCollide())
            {
                sm.playSfx(0);
                ball.bounce(3);
            }

            //if ball hits brick
            for (int i = 0; i < 30; i++)
            {
                if (l.getBrick(i) != nullptr && ball.collide(l.getBrick(i)->getCollider()) && l.getBrick(i)->getAlive())
                {
                    if (checkCollideBrick(l.getBrick(i)) == 0)
                    {
                        cout << "top" << endl;
                        ball.bounce(2);
                    }
                    else if (checkCollideBrick(l.getBrick(i)) == 1) {
                        cout << "sides" << endl;
                        ball.bounce(1);
                    }
                    l.getBrick(i)->setHealth(l.getBrick(i)->getHealth() - 1);
                    if (l.getBrick(i)->getHealth() == 0)
                    {
                        l.setBricksBroken(l.getBricksBroken() + 1);
                        playerScore += 10;
                        ui.updateScore(playerScore);
                        sm.playSfx(4);
                    }
                    else {
                        sm.playSfx(5);
                    }
                }
            }

            //while ball is not intersecting with a paddle
            {
                if (paddle1.collide(ball.getCollider()) == false && ball.getCanCollide() == false)
                {
                    ball.switchCanCollide();
                }
            }

            //if out of bounds
            if (ball.getCollider().top + ball.getCollider().height >= window.getSize().y)
            {
                //pause game
                gameState = gameStart;

                //add score
                playerHealth--;
                ui.updateHP(playerHealth);
                cout << "player health: " << playerHealth << endl;
                //reset positions
                reset();
            }
        }
    }
}

void Game::render(RenderWindow& window) {
    window.clear();

    ui.render(window);
    paddle1.render(window, deltaTime);
    ball.render(window, deltaTime);
    l.render(window);

    window.display();

}

void Game::reset()
{
    sm.playSfx(3);
    gameState = gameStart;
    paddle1.setPosition(paddleDefaultPos);

    ball.setPosition(ballDefaultPos);
    ball.resetVel();

    if (playerHealth == 0)
    {
        sm.playSfx(6);
        cout << "Game Over!" << endl;
        ui.updateLoseText("Game Over!");
        gameState = gameStop;
    }
}

//returns 0 for top/bottom, 1 for sides
int Game::checkCollideBrick(Brick* b) {
    //values to make debugging easier
    float ballTop = ball.getCollider().top;
    float ballLeft = ball.getCollider().left;
    float ballBottom = ball.getCollider().top + ball.getCollider().height;
    float ballRight = ball.getCollider().left + ball.getCollider().width;

    float brickTop = b->getCollider().top;
    float brickLeft = b->getCollider().left;
    float brickBottom = b->getCollider().top + b->getCollider().height;
    float brickRight = b->getCollider().left + b->getCollider().width;

    //if ball moving downwards
    if (ball.getVelocity().y >= 0) {
        //if ball hits top of brick
        if (ballBottom >= brickTop &&
            ballBottom - brickTop <= ballRight - brickLeft &&
            ballBottom - brickTop <= brickRight - ballLeft)
        {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (ball.getVelocity().y <= 0) {
        //if ball hits bottom of brick
        if (brickBottom >= ballTop &&
            brickBottom - ballTop <= ballRight - brickLeft &&
            brickBottom - ballTop <= brickRight - ballLeft)
        {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return 3;
    }
}

Game::~Game() {

}