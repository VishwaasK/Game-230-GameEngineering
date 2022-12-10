#include "Level.h"

using namespace std;
using namespace sf;
using namespace gm;

Level::Level() {
	currentLevel = 1;
	bricksBroken = 0;
	maxBricks = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (level1[i][j] == 0)
			{
				arr[(10 * i) + j] = nullptr;
			}
			else if (level1[i][j] == 1)
			{
				arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &normal_brick);
				maxBricks++;
			}
			else if (level1[i][j] == 2)
			{
				arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &tough_brick);
				maxBricks++;
			}
		}
	}
}

void Level::update(sf::RenderWindow& window) {
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (arr[i] != nullptr && arr[i]->getAlive())
		{
			arr[i]->update(window);
		}
	}
}

void Level::render(sf::RenderWindow& window) {
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (arr[i] != nullptr && arr[i]->getAlive())
		{
			arr[i]->render(window);
		}
	}
}

Brick* Level::getBrick(int index) {
	return arr[index];
}

const int Level::getCurrentLevel() {
	return currentLevel;
}

const int Level::getBricksBroken() {
	return bricksBroken;
}

const bool Level::checkFinished() {
	if (maxBricks - bricksBroken == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Level::setBricksBroken(int num) {
	bricksBroken = num;
}

void Level::setLevel(int l) {
	currentLevel = l;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (currentLevel == 1)
			{
				if (level1[i][j] == 0)
				{
					arr[(10 * i) + j] = nullptr;
				}
				else if (level1[i][j] == 1)
				{
					arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &normal_brick);
					maxBricks++;
				}
				else if (level1[i][j] == 2)
				{
					arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &tough_brick);
					maxBricks++;
				}
			}
			else if (currentLevel == 2)
			{
				if (level2[i][j] == 0)
				{
					arr[(10 * i) + j] = nullptr;
				}
				else if (level2[i][j] == 1)
				{
					arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &normal_brick);
					maxBricks++;
				}
				else if (level2[i][j] == 2)
				{
					arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &tough_brick);
					maxBricks++;
				}
			}
			if (currentLevel == 3)
			{
				if (level3[i][j] == 0)
				{
					arr[(10 * i) + j] = nullptr;
				}
				else if (level3[i][j] == 1)
				{
					arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &normal_brick);
					maxBricks++;
				}
				else if (level3[i][j] == 2)
				{
					arr[(10 * i) + j] = new Brick(Vector2f(78.0f * j, (28.0f * i) + 50.0f), Vector2f(78.0f, 28.0f), &tough_brick);
					maxBricks++;
				}
			}

		}
	}
}

void Level::reset() {
	bricksBroken = 0;
	maxBricks = 0;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (arr[i] != nullptr)
		{
			delete arr[i];
		}
	}
}

Level::~Level() {
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (arr[i] != nullptr)
		{
			delete arr[i];
		}
	}
}