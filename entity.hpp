#pragma once

#include "game.hpp"

class entity{
    public:
        Vector2 getPosition();
        Vector2 getOldPosition();
        Vector2 getSize();
        float getVelocity();

        void setPosition(Vector2 newPos);
        void setOldPosition(Vector2 newOldPos);
        void setSize(Vector2 newSize);
        void setVelocity(float newVelocity);
    private:
        Vector2 position;
        Vector2 oldPosition;
        Vector2 size;
        float velocity;
};