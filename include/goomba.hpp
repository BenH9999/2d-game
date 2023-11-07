#pragma once

#include "entity.hpp"

class goomba : public Entity{
    public:
        goomba();
        //void goombaJumpOnTimer();
        void goombaWalkSlowForward();
        void resetGoomba();
        void processFalling();

        bool getAlive();

        void setAlive(bool newAlive);
    private:
        bool alive;
};