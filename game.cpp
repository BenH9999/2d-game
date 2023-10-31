#include "game.hpp"

player *newPlayer = new player;

void initGame(){
    InitWindow(800,450,"2D Game");
    SetTargetFPS(60);
    Font f = LoadFont("font/minecraft.ttf");
    //player newPlayer = {.playerPosition=0};

    newPlayer->playerPosition = {(float)100, (float)370};
    newPlayer->playerSize = {30,30};
    newPlayer->velocity = 0;

    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(GetColor(0xffffffff));
        DrawRectangleV({50, 400},{700,50},GetColor(0x000000ff));

        processGame();

        updateScreen();

        EndDrawing();
    }
}
 
void updateScreen(){
    DrawRectangleV(newPlayer->playerPosition,newPlayer->playerSize,GetColor(0xff0000ff));
}

int jump_count = 0;
void processGame(){
    if(IsKeyDown(KEY_RIGHT)) newPlayer->playerPosition.x += 3.0f;
    if(IsKeyDown(KEY_LEFT)) newPlayer->playerPosition.x -= 3.0f;
    if(IsKeyPressed(KEY_UP)&&jump_count < 2){
        newPlayer->velocity = -9.0f;
        jump_count++;
    }

    newPlayer->velocity += 0.4f;
    newPlayer->playerPosition.y += newPlayer->velocity;

    if (newPlayer->playerPosition.y >= (float)370) {
        newPlayer->playerPosition.y = (float)370;
        newPlayer->velocity = 0;
        jump_count = 0;
    }

    //if(IsKeyDown(KEY_UP)) playerPosition.y += 3.0f
}