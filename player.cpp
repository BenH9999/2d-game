#include "player.hpp"

Player::Player(){
    position = {100.0f, 370.0f};
    size = {30.0f, 30.0f};
    velocity = 0.0f;
}

void Player::setLives(int newLives){
    lives = newLives;
}

int Player::getLives(){
    return lives;
}