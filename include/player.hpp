#pragma once

#include "entity.hpp"

class Player : public Entity {
    public:
        Player();

        void setLives(int newLives);

        int getLives();
    private:
        int lives;
};