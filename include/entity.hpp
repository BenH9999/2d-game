#pragma once

#include <raylib.h>
#include <vector>
#include <iostream>

class Entity{
    public:
        Entity();

        Vector2 getPosition();
        Vector2 getOldPosition();
        Vector2 getSpawnPosition();
        Vector2 getSize();
        float getVelocity();

        void setPosition(Vector2 newPos);
        void setOldPosition(Vector2 newOldPos);
        void setSpawnPosition(Vector2 setSpawnPosition);
        void setSize(Vector2 newSize);
        void setVelocity(float newVelocity);
    protected:
        Vector2 position;
        Vector2 oldPosition;
        Vector2 spawnPosition;
        Vector2 size;
        float velocity;
};