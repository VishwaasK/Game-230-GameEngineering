#include "SoundManager.h"

using namespace std;
using namespace sf;
using namespace gm;

SoundManager::SoundManager() {
    //load sounds
    paddleHitSfx.loadFromFile("Paddle.wav");
    arr[0] = paddleHitSfx;

    wallHitSfx.loadFromFile("Wall.wav");
    arr[1] = wallHitSfx;

    winSfx.loadFromFile("LevelWin.wav");
    arr[2] = winSfx;

    lifeLoseSfx.loadFromFile("LoseLife.wav");
    arr[3] = lifeLoseSfx;

    breakSfx.loadFromFile("break.wav");
    arr[4] = breakSfx;

    shatterSfx.loadFromFile("BrickDamage.wav");
    arr[5] = shatterSfx;

    loseSfx.loadFromFile("GameOver.wav");
    arr[6] = loseSfx;

    s.setBuffer(arr[0]);
}

//0 = paddleHitSfx, 1 = wallHitSfx, 2 = winSfx, 3 = lifeLoseSfx, 4 = breakSfx, 5 = shatterSfx, 6 = loseSfx
void SoundManager::playSfx(int index) {
    s.setBuffer(arr[index]);
    s.play();
}

SoundManager::~SoundManager() {
}