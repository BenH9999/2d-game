#include "entity.hpp"

Entity::Entity(){
    
}

Vector2 Entity::getPosition(){
    return position;
}

Vector2 Entity::getOldPosition(){
    return oldPosition;
}

Vector2 Entity::getSize(){
    return size;
}

float Entity::getVelocity(){
    return velocity;
}

void Entity::setPosition(Vector2 newPos){
    position = newPos;
}

void Entity::setOldPosition(Vector2 newOldPos){
    oldPosition = newOldPos;
}

void Entity::setSize(Vector2 newSize){
    size = newSize;
}

void Entity::setVelocity(float newVelocity){
    velocity = newVelocity;
}