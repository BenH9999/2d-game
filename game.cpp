#include "game.hpp"

Game::Game() {
    player = nullptr;
}

void Game::initGame() {
    player = new Player;
    InitWindow(800, 450, "2D Game");
    SetTargetFPS(60);

    player->setPosition({100.0f, 370.0f}); // Fixed float values
    player->setSize({30.0f, 30.0f}); // Fixed float values
    player->setVelocity(0.0f);

    groundBlocks.push_back({{50.0f, 400.0f, 700.0f, 50.0f}});
    groundBlocks.push_back({{50.0f, 250.0f, 700.0f, 50.0f}});

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(0xFFFFFFFF));

        DrawRectangleRec(groundBlocks[0].rect, GetColor(0x000000FF));
        DrawRectangleRec(groundBlocks[1].rect, GetColor(0x000000FF));

        processGame();

        updateScreen();

        EndDrawing();
    }
    CloseWindow();
}

void Game::updateScreen() {
    DrawRectangleV(player->getPosition(), player->getSize(), GetColor(0xFF0000FF));
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

    for (int i = 0; i < groundBlocks.size(); i++) {
        if (CheckCollisionRecs({player->getPosition().x, player->getPosition().y, player->getSize().x, player->getSize().y}, groundBlocks[i].rect)) {
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
