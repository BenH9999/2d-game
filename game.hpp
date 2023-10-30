#pragma once

#include <raylib.h>
#include <cstdlib>

struct player{
    Vector2 playerPosition;
    Vector2 playerSize;
    float velocity;
};


void initGame();
void processGame();
void updateScreen();