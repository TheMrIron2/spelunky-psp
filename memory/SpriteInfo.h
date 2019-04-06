//
// Created by xdbeef on 26.03.18.
//

#ifndef SPELUNKYDS_SPRITEINFO_H
#define SPELUNKYDS_SPRITEINFO_H

struct SpriteEntry {
    int x;
    int y;
    bool hFlip;
    bool vFlip;
    bool isHidden;
};

#include <psptypes.h>
#include "SpritesheetType.hpp"
#include "OamType.hpp"

class SpriteInfo {
public:
    u16 *sprite_address{};
    int offset_multiplier{};

    u8 oamId_palette{};
    int oamId_tiles{};

    //FIXME BaseCreature duplicates those fields:
    int width{};
    int height{};
    int angle{};
    SpriteEntry *entry{};

    SpritesheetType spriteType{};
    u16 oam_address{};
    OamType oamType{};

    void updateFrame(u8 *tile, u32 size);
};


#endif //SPELUNKYDS_SPRITEINFO_H
