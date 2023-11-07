#include "include/goomba.hpp"

goomba::goomba(){
    alive = 1;
    position = {500.0f, 375.0f};
    size = {25.0f, 25.0f};
    velocity = 0.0f;
}

void goomba::setAlive(bool newAlive){
    alive = newAlive;
}

bool goomba::getAlive(){
    return alive;
}