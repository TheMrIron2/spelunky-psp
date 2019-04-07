//
// Created by xdbeef on 01.04.18.
//

#ifndef SPELUNKYDS_OAMMANAGER_H
#define SPELUNKYDS_OAMMANAGER_H

#define MAX_SPRITE_NUMBER 128

#include <vector>
#include "SpritesheetType.hpp"
#include "SpriteInfo.h"
#include "Texture.h"

class OAMManager {
public:

    std::vector<SpriteInfo*> oamTable{};
    std::vector<Texture*> textures{};

    void initTexture(const unsigned char * imagePtr, int file_width, int file_height, SpritesheetType type);

    SpriteInfo *initSprite(SpritesheetType type, int width, int height);

    void render();

};


#endif //SPELUNKYDS_OAMMANAGER_H
