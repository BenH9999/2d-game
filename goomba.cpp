#include "include/goomba.hpp"
#include "include/game.hpp"

goomba::goomba(){
    this->alive = 1;
    this->position = this->spawnPosition;
    this->size = {25.0f, 25.0f};
    this->velocity = 0.0f;
}

void goomba::goombaWalkSlowForward(){
    this->setPosition({this->getPosition().x - 0.5f,this->getPosition().y});
    processFalling();
}

void goomba::processFalling(){
    for(size_t i = 0; i < g.getGroundBlocks().size();i++){
        if (CheckCollisionRecs({this->getPosition().x, this->getPosition().y, this->getSize().x, this->getSize().y}, g.getGroundBlocks()[i].rect)){
            if (g.collidedFromTop(this->getOldPosition(), this->getPosition(), g.getGroundBlocks()[i].rect)){
                this->setPosition({this->getPosition().x, g.getGroundBlocks()[i].rect.y - this->getSize().y});
                this->setVelocity(0.0f);
            }
        }
    }
    this->setOldPosition(this->getPosition());
}

void goomba::resetGoomba(){
    this->setAlive(1);
    this->setPosition(this->spawnPosition);
    this->setSize({25.0f, 25.0f});
    this->setVelocity(0.0f);
}

void goomba::setAlive(bool newAlive){
    alive = newAlive;
}

bool goomba::getAlive(){
    return alive;
}