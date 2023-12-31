#include "include/game.hpp"
#include "include/colour.hpp"
#include "include/levels.hpp"

Game::Game() {
    player = nullptr;
    goo = nullptr;
    draw_offset = 0;
    gameOver = 0;
    groundBlocks={};
    goomba_vector={};
}

void Game::initGame() {
    player = new Player;
    player->setLives(5);
    currentLives = player->getLives();
    InitWindow(screenW, screenH, "2D Game");
    SetTargetFPS(60);

    f = LoadFont("font/minecraft.ttf");

    loadLevelFromFile(1);

    /*for(int i = 0; i < 2;i++){
        goo = new goomba;
        goo->setSpawnPosition({500.0f,375.0f});
        if(i==1){
             goo->setPosition({600.0f,375.0f});
             goo->setSpawnPosition({600.0f,375.0f});
        }
        goomba_vector.push_back(goo);
    }*/

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(backgroundC);

        processGame();

        livesStr = "Lives: "+ std::to_string(currentLives);

        processAI();

        updateScreen();

        EndDrawing();

        if(gameOver)break;
    }
    CloseWindow();
    titleScreen();
}

void Game::updateScreen() {
    Color currentColor = black;
    ClearBackground(backgroundC);
    for(size_t i = 0; i < groundBlocks.size(); i++){
        switch(groundBlocks[i].type){
            case NORMAL:{
                currentColor = normalGroundC;
                break;
            }
            case LAVA:{
                currentColor = lavaC;
                break;
            }
            case WATER:{

            }
            case FINISH:{

            }
        }
        DrawRectangleRec({groundBlocks[i].rect.x+draw_offset,groundBlocks[i].rect.y,groundBlocks[i].rect.width,groundBlocks[i].rect.height}, currentColor);
    }
    for(size_t i = 0; i < goomba_vector.size();i++){
        if(goomba_vector[i]->getAlive()){
            DrawRectangleV({goomba_vector[i]->getPosition().x +draw_offset, goomba_vector[i]->getPosition().y},goomba_vector[i]->getSize(), GOOMBA);
        }
    }
    DrawRectangleV({player->getPosition().x+draw_offset, player->getPosition().y}, player->getSize(), playerC);
    DrawTextEx(f,livesStr.c_str(),{25,25},25,0,GetColor(0x000000ff));
}

int jump_count = 0;

void Game::processGame() {
    if (IsKeyDown(KEY_RIGHT)) {
        player->setPosition({player->getPosition().x + 4.0f, player->getPosition().y});
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->setPosition({player->getPosition().x - 4.0f, player->getPosition().y});
    }

    player->setPosition({player->getPosition().x, player->getPosition().y + player->getVelocity()});
    player->setVelocity(player->getVelocity() + 0.4f);

    for (size_t i = 0; i < groundBlocks.size(); i++) {
        if (CheckCollisionRecs({player->getPosition().x, player->getPosition().y, player->getSize().x, player->getSize().y}, groundBlocks[i].rect)) {
            if(groundBlocks[i].type == NORMAL){
                if (collidedFromTop(player->getOldPosition(), player->getPosition(), groundBlocks[i].rect)) {
                    player->setPosition({player->getPosition().x, groundBlocks[i].rect.y - player->getSize().y});
                    player->setVelocity(0.0f);
                    jump_count = 0;
                } else if (collidedFromBottom(player->getOldPosition(), player->getPosition(), groundBlocks[i].rect)) {
                    player->setPosition({player->getPosition().x, groundBlocks[i].rect.y + groundBlocks[i].rect.height});
                    player->setVelocity(0.0f);
                } else if (collidedFromLeft(player->getOldPosition(), player->getPosition(), groundBlocks[i].rect)) {
                    player->setPosition({groundBlocks[i].rect.x - player->getSize().x, player->getPosition().y});
                } else if (collidedFromRight(player->getOldPosition(), player->getPosition(), groundBlocks[i].rect)) {
                    player->setPosition({groundBlocks[i].rect.x + groundBlocks[i].rect.width, player->getPosition().y});
                }
            }
            else if(groundBlocks[i].type == LAVA){
                processDeath();
            }
        }
    }

    for(size_t i = 0; i < goomba_vector.size();i++){
        if(!goomba_vector[i]->getAlive())
            continue;
        if(CheckCollisionRecs({player->getPosition().x, player->getPosition().y, player->getSize().x, player->getSize().y},{goomba_vector[i]->getPosition().x, goomba_vector[i]->getPosition().y, goomba_vector[i]->getSize().x, goomba_vector[i]->getSize().y})){
            if(collidedFromTop(player->getOldPosition(),player->getPosition(), {goomba_vector[i]->getPosition().x,goomba_vector[i]->getPosition().y,goomba_vector[i]->getSize().x,goomba_vector[i]->getSize().y})){
                goomba_vector[i]->setAlive(0);
            }
            else if(collidedFromBottom(player->getOldPosition(),player->getPosition(), {goomba_vector[i]->getPosition().x,goomba_vector[i]->getPosition().y,goomba_vector[i]->getSize().x,goomba_vector[i]->getSize().y})){
                processDeath();
            }
            else if(collidedFromLeft(player->getOldPosition(),player->getPosition(), {goomba_vector[i]->getPosition().x,goomba_vector[i]->getPosition().y,goomba_vector[i]->getSize().x,goomba_vector[i]->getSize().y})){
                processDeath();
            }
            else if(collidedFromRight(player->getOldPosition(),player->getPosition(), {goomba_vector[i]->getPosition().x,goomba_vector[i]->getPosition().y,goomba_vector[i]->getSize().x,goomba_vector[i]->getSize().y})){
                processDeath();
            }
        }
    }

    player->setOldPosition(player->getPosition());

    if (player->getPosition().y >= 420.0f) {
        player->setPosition({player->getPosition().x, 420.0f});
        player->setVelocity(0.0f);
        jump_count = 0;
    }

    if (IsKeyPressed(KEY_UP) && jump_count < 2) {
        player->setVelocity(-9.0f);
        jump_count++;
    }

    while(player->getPosition().x < (screenW/4-draw_offset)){
        draw_offset++;
    }
    while(player->getPosition().x > (screenW/2-draw_offset)){
        draw_offset--;
    }
}

void Game::processAI(){
    if(!goomba_vector.empty()){
        goombaActions();
    }
}

void Game::goombaActions(){
    for(size_t i = 0; i < goomba_vector.size();i++){
        goomba_vector[i]->goombaWalkSlowForward();
    }
}

bool Game::collidedFromTop(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return oldPos.y + player->getSize().y <= rect.y && newPos.y + player->getSize().y >= rect.y;
}

bool Game::collidedFromLeft(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return newPos.x < rect.x + rect.width && oldPos.x + player->getSize().x <= rect.x;
}

bool Game::collidedFromRight(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return newPos.x + player->getSize().x > rect.x && oldPos.x >= rect.x + rect.width;
}

bool Game::collidedFromBottom(Vector2 oldPos, Vector2 newPos, Rectangle rect) {
    return oldPos.y >= rect.y + rect.height && newPos.y < rect.y + rect.height;
}

void Game::setGroundBlocks(std::vector<GroundBlock> newGroundBlocks){
    groundBlocks = newGroundBlocks;
}

std::vector<GroundBlock> Game::getGroundBlocks(){
    return groundBlocks;
}

void Game::setGoombaVector(std::vector<goomba*> newGoombaVector){
    goomba_vector = newGoombaVector;
}

std::vector<goomba*> Game::getGoombas(){
    return goomba_vector;
}

void Game::processDeath(){
    newPlayer = new Player;
    player =  newPlayer;
    currentLives--;
    player->setLives(currentLives);
    if(player->getLives()==0){
        gameOver =1;
    }

    resetEntities();
    draw_offset = 0;
}

void Game::resetEntities(){
    if(!goomba_vector.empty()){
        for(size_t i = 0; i < goomba_vector.size();i++){
            goomba_vector[i]->resetGoomba();
            goomba_vector[i]->setPosition(goomba_vector[i]->getSpawnPosition());
        }
    }
}
