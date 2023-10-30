#include "menu_screen.hpp"

int screenW = 800;
int screenH = 450;
int currentMouseX = 0;
int currentMouseY = 0;

void titleScreen(){
    InitWindow(screenW,screenH,"2D Game");

    SetTargetFPS(60);
    Font f = LoadFont("font/minecraft.ttf");

    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(GetColor(0xffffffff));
        DrawTextEx(f,"Game",{320,50},70,0,GetColor(0x000000ff));

        DrawRectangleLines(300,150,200,100,GetColor(0x000000ff));
        DrawTextEx(f,"Start",{325,175},50,0,GetColor(0x000000ff));

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            currentMouseX = GetMouseX();
            currentMouseY = GetMouseY();
            if(currentMouseX >= 300 && currentMouseX <= 500 && currentMouseY >= 150 && currentMouseY <= 250){
                EndDrawing();
                CloseWindow();
                initGame();
            }
        }

        EndDrawing();
    }
    CloseWindow();
}