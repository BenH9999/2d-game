#pragma once

#include <raylib.h>
#include <vector>
#include <iostream>
#include "player.hpp"
#include "menu_screen.hpp"

const int screenW = 800;
const int screenH = 450;

enum groundType{
    NORMAL,
    LAVA,
    WATER,
    FINISH
};

struct GroundBlock {
    Rectangle rect;
    groundType type;
};

class Player;

class Game {
public:
    Game();
    void initGame();
    void processDeath();
    void processGame();
    void updateScreen();
    bool collidedFromTop(Vector2 oldPos, Vector2 newPos, Rectangle rect);
    bool collidedFromLeft(Vector2 oldPos, Vector2 newPos, Rectangle rect);
    bool collidedFromRight(Vector2 oldPos, Vector2 newPos, Rectangle rect);
    bool collidedFromBottom(Vector2 oldPos, Vector2 newPos, Rectangle rect);
    void setGroundBlocks(std::vector<GroundBlock> newGroundBlocks);
    std::vector<GroundBlock> getGroundBlocks();

protected:
    Player* player;
    std::vector<GroundBlock> groundBlocks;
    float draw_offset;
    Player* newPlayer;
    int currentLives;
    bool gameOver;
};

extern Game g;