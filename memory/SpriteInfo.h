//
// Created by xdbeef on 26.03.18.
//

#ifndef SPELUNKYDS_SPRITEINFO_H
#define SPELUNKYDS_SPRITEINFO_H

#include <psptypes.h>
#include "SpritesheetType.hpp"
#include "Texture.h"

class SpriteInfo {
public:
    int width{};
    int height{};
    int angle{};
    int x{};
    int y{};
    bool hFlip{};
    bool vFlip{};
    bool isHidden{};
    SpritesheetType spriteType{};
    u16 oam_address{};
    Texture *texture;
    float coordinates[4][2];
    int tile{};
    void set_texture_pointer_to_tile(int type);

    void updateFrame(u8 *tile, u32 size);
    void render();
};


#endif //SPELUNKYDS_SPRITEINFO_H
