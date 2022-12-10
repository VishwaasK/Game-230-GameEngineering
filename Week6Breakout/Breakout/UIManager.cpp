#include "UIManager.h"

using namespace sf;
using namespace std;
using namespace gm;

UIManager::UIManager() {
}

UIManager::UIManager(int health, int score, int levelNum)
{

    //load font
    f.loadFromFile("arial.ttf");



    //set text
    playerHP.setFont(f);
    playerScore.setFont(f);
    levelNumText.setFont(f);
    lose.setFont(f);

    playerHP.setString(to_string(health) + " : Balls Left ");
    playerScore.setString(to_string(score) + " : Points ");
    levelNumText.setString(" Level # : " + to_string(levelNum));
    lose.setString("");

    playerHP.setCharacterSize(30);
    playerScore.setCharacterSize(30);
    levelNumText.setCharacterSize(30);
    lose.setCharacterSize(64);

    playerHP.setPosition(Vector2f(15.0f, 10.0f));
    playerScore.setPosition(Vector2f(760.0f - playerScore.getGlobalBounds().width, 10.0f));
    levelNumText.setPosition(Vector2f(390 - playerScore.getGlobalBounds().width / 2, 10.0f));
    lose.setPosition(loseTextDefaultPos);

    //set up ui of upper bound of playable area
    ceilingLine.setPosition(0, 50);
    ceilingLine.setSize(Vector2f(780, 1));
    ceilingLine.setFillColor(Color::White);

}

void UIManager::render(sf::RenderWindow& window) {
    window.draw(playerHP);
    window.draw(playerScore);
    window.draw(levelNumText);
    window.draw(lose);
    window.draw(ceilingLine);
}


void UIManager::updateHP(int hp) {
    playerHP.setString(to_string(hp) + " balls left");
}

void UIManager::updateScore(int score) {
    playerScore.setString(to_string(score) + " Points");
    playerScore.setPosition(Vector2f(760.0f - playerScore.getGlobalBounds().width, 10.0f));
}

void UIManager::updateLevelText(int levelNum) {
    levelNumText.setString("Level " + to_string(levelNum));
    levelNumText.setPosition(Vector2f(390 - playerScore.getGlobalBounds().width / 2, 10.0f));
}

void UIManager::updateLoseText(string str) {
    lose.setString(str);
    lose.setPosition(Vector2f(lose.getPosition().x - lose.getGlobalBounds().width / 2.0f, lose.getPosition().y - lose.getGlobalBounds().height / 2.0f));
}

UIManager::~UIManager() {

}