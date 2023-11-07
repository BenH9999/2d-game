#include "include/levels.hpp"

std::vector<GroundBlock> newGroundBlocks;

void loadLevelFromFile(int level){
    std::string filename = "levels/"+ std::to_string(level) + "/ground.txt";
    std::fstream file;
    file.open(filename, std::ios::in);

    if(file.is_open()){
        std::string line;
        while(std::getline(file,line)){
            std::istringstream iss(line);
            int x,y,w,h;
            std::string typeStr;
            groundType type;

            if(iss >> x >> y >> w >> h >> typeStr){
                //std::cout << "Parsed values: x=" << x << " y=" << y << " width=" << w << " height=" << h << " type=" << typeStr << std::endl;
                if(typeStr == "NORMAL")type = NORMAL;
                else if(typeStr == "LAVA")type = LAVA;
                else if(typeStr == "WATER")type = WATER;
                else if(typeStr == "FINISH")type = FINISH;
                else type = NORMAL;

                GroundBlock block = {(float)x,(float)y,(float)w,(float)h,type};
                newGroundBlocks.push_back(block);
            }
        }
        file.close();
    }
    g.setGroundBlocks(newGroundBlocks);
}