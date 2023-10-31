#pragma once

#include <raylib.h>
#include <cstdlib>
#include <vector>
#include <iostream>

struct player{
    Vector2 position;
    Vector2 oldPosition;
    Vector2 size;
    float velocity;
};

struct groundBlock{
    Rectangle rect;
};

void initGame();
void processGame();
void updateScreen();
bool collidedFromTop(Vector2 oldPos, Vector2 newPos, Rectangle rect);
bool collidedFromLeft(Vector2 oldPos, Vector2 newPos, Rectangle rect);
bool collidedFromRight(Vector2 oldPos, Vector2 newPos, Rectangle rect);
bool collidedFromBottom(Vector2 oldPos, Vector2 newPos, Rectangle rect);