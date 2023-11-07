#include "include/levels.hpp"

std::vector<GroundBlock> newGroundBlocks;
std::vector<goomba*> newGoombaVector;

void loadLevelFromFile(int level){
    std::string fileGroundName = "levels/"+ std::to_string(level) + "/ground.txt";
    std::string fileEntityName = "levels/"+ std::to_string(level) + "/entity.txt";
    std::fstream fileGround;
    std::fstream fileEntity;
    fileGround.open(fileGroundName, std::ios::in);
    if(fileGround.is_open()){
        std::string lineGround;
        while(std::getline(fileGround,lineGround)){
            std::istringstream iss(lineGround);
            int x,y,w,h;
            std::string typeStr;
            groundType type;

            if(iss >> x >> y >> w >> h >> typeStr){
                if(typeStr == "NORMAL")type = NORMAL;
                else if(typeStr == "LAVA")type = LAVA;
                else if(typeStr == "WATER")type = WATER;
                else if(typeStr == "FINISH")type = FINISH;
                else type = NORMAL;

                GroundBlock block = {(float)x,(float)y,(float)w,(float)h,type};
                newGroundBlocks.push_back(block);
            }
        }
        fileGround.close();
    }
    fileEntity.open(fileEntityName, std::ios::in);
    if(fileEntity.is_open()){
        std::string lineEntity;
        while(std::getline(fileEntity,lineEntity)){
            std::istringstream iss(lineEntity);
            int x,y;
            std::string entityTypeStr;

            if(iss >> entityTypeStr >> x >> y){
                if(entityTypeStr == "GOOMBA"){
                    goomba* goo = new  goomba;
                    goo->setSpawnPosition({(float)x,(float)y});
                    goo->resetGoomba();
                    newGoombaVector.push_back(goo);
                }
            }
        }
        fileEntity.close();
    }
    g.setGroundBlocks(newGroundBlocks);
    g.setGoombaVector(newGoombaVector);
}