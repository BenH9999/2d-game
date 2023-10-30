#include "game.hpp"

player *newPlayer = new player;

void initGame(){
    InitWindow(800,450,"2D Game");
    SetTargetFPS(60);
    Font f = LoadFont("font/minecraft.ttf");
    //player newPlayer = {.playerPosition=0};

    newPlayer->playerPosition = {(float)800/2, (float)450/2};
    newPlayer->playerSize = {30,30};
    newPlayer->velocity = 0;

    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(GetColor(0xffffffff));

        processGame();

        updateScreen();

        EndDrawing();
    }
}
 
void updateScreen(){
    DrawRectangleV(newPlayer->playerPosition,newPlayer->playerSize,GetColor(0xff0000ff));
}

void processGame(){
    if(IsKeyDown(KEY_RIGHT)) newPlayer->playerPosition.x += 3.0f;
    if(IsKeyDown(KEY_LEFT)) newPlayer->playerPosition.x -= 3.0f;
    if(IsKeyDown(KEY_UP)&&newPlayer->playerPosition.y >= (float)450/2){
        newPlayer->velocity = -9.0f;
    }

    newPlayer->velocity += 0.4f;
    newPlayer->playerPosition.y += newPlayer->velocity;

    if (newPlayer->playerPosition.y >= (float)450 / 2) {
        newPlayer->playerPosition.y = (float)450 / 2;
        newPlayer->velocity = 0;
    }

    //if(IsKeyDown(KEY_UP)) playerPosition.y += 3.0f
}