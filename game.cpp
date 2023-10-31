#include "game.hpp"

player* newPlayer = new player;
std::vector<groundBlock> groundBlocks;

void initGame(){
    InitWindow(800,450,"2D Game");
    SetTargetFPS(60);
    Font f = LoadFont("font/minecraft.ttf");
    //player newPlayer = {.position=0};

    newPlayer->position = {(float)100, (float)370};
    newPlayer->size = {30,30};
    newPlayer->velocity = 0;
    groundBlocks.push_back({50,400,700,50});
    groundBlocks.push_back({50,250,700,50});

    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(GetColor(0xffffffff));

        //ground

        DrawRectangleRec(groundBlocks[0].rect,GetColor(0x000000ff));
        DrawRectangleRec(groundBlocks[1].rect,GetColor(0x000000ff));

        processGame();

        updateScreen();

        EndDrawing();
    }
}
 
void updateScreen(){
    DrawRectangleV(newPlayer->position,newPlayer->size,GetColor(0xff0000ff));
}

int jump_count = 0;
void processGame(){
    if(IsKeyDown(KEY_RIGHT)) newPlayer->position.x += 3.0f;
    if(IsKeyDown(KEY_LEFT)) newPlayer->position.x -= 3.0f;

    newPlayer->position.y += newPlayer->velocity;
    newPlayer->velocity += 0.4f;

    for(int i = 0; i < groundBlocks.size();i++){
        if (CheckCollisionRecs({newPlayer->position.x,newPlayer->position.y, newPlayer->size.x,newPlayer->size.y}, groundBlocks[i].rect)) {
            if (collidedFromTop(newPlayer->oldPosition, newPlayer->position, groundBlocks[i].rect)) {
                newPlayer->position.y = groundBlocks[i].rect.y - newPlayer->size.y;
                newPlayer->velocity = 0;
                jump_count = 0;
            }
            else if (collidedFromBottom(newPlayer->oldPosition, newPlayer->position, groundBlocks[i].rect)) {
                newPlayer->position.y = groundBlocks[i].rect.y + groundBlocks[i].rect.height;
                newPlayer->velocity = 0.0;
            }
            else if (collidedFromLeft(newPlayer->oldPosition, newPlayer->position, groundBlocks[i].rect)) {
                newPlayer->position.x = groundBlocks[i].rect.x - newPlayer->size.x;
            }
            else if (collidedFromRight(newPlayer->oldPosition, newPlayer->position, groundBlocks[i].rect)) {
                newPlayer->position.x = groundBlocks[i].rect.x + groundBlocks[i].rect.width;
            }

        }
    }

    newPlayer->oldPosition = newPlayer->position;

    if (newPlayer->position.y >= (float)420) {
        newPlayer->position.y = (float)420;
        newPlayer->velocity = 0;
        jump_count = 0;
    }

    if (IsKeyPressed(KEY_UP) && jump_count < 2) {
        newPlayer->velocity = -9.0f;
        jump_count++;
    }
}

bool collidedFromTop(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return oldPos.y + newPlayer->size.y <= rect.y && newPos.y + newPlayer->size.y >= rect.y;
}

bool collidedFromLeft(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return newPos.x < rect.x + rect.width && oldPos.x + newPlayer->size.x <= rect.x;
}

bool collidedFromRight(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return newPos.x + newPlayer->size.x > rect.x && oldPos.x >= rect.x + rect.width;
}

bool collidedFromBottom(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return oldPos.y >= rect.y + rect.height && newPos.y < rect.y + rect.height;
}