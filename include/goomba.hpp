#pragma once

#include "entity.hpp"

class goomba : public Entity{
    public:
        goomba();

        bool getAlive();

        void setAlive(bool newAlive);
    private:
        bool alive;
};