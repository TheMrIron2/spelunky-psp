//
// Created by xdbeef on 24.02.18.
//

#ifndef SPELUNKYDS_CONSTS_H
#define SPELUNKYDS_CONSTS_H

#include "../input/InputHandler.h"
#include "../tiles/Level.hpp"
#include "../main_dude/MainDude.hpp"
#include "../hud/Hud.hpp"
#include "../main_dude/GameState.hpp"
#include "../decorations/_BaseDecoration.h"
#include "../treasures/_BaseTreasure.h"
#include "../items/_BaseItem.h"

#include <vector>

// Dummy function replacing sound effects.
// TODO: Implement real sounds.
#define mmEffect(x)

#define GRAVITY_DELTA_SPEED 0.22 //FIXME isn't it mob-specific?
#define DEFAULT_DMA_CHANNEL 3

//https://stackoverflow.com/questions/21505021/extern-and-global-same-variable-in-same-file
//https://stackoverflow.com/questions/37323227/benefits-of-using-extern-declaration-in-same-file-as-definition
namespace global {
    extern float *timer;
    extern float clean_unused_oam_timer;
    extern InputHandler *input_handler;
    extern Level *current_level;
    extern Camera *camera;
    extern MainDude *main_dude;
    extern Hud *hud;
    extern GameState *game_state;

    extern std::vector<BaseCreature *> creatures;
    extern std::vector<BaseCreature *> creatures_to_add;

    extern std::vector<BaseDecoration *> decorations;
    extern std::vector<BaseDecoration *> decorations_to_add;

    extern std::vector<BaseTreasure *> treasures;
    extern std::vector<BaseTreasure *> treasures_to_add;

    extern std::vector<BaseItem *> items;
    extern std::vector<BaseItem *> items_to_add;

    extern std::vector<SpriteInfo *> sprite_infos; //technically list of wrappers around OAM entries FIXME naming
    extern std::vector<CreatureType> killed_npcs; //list of NPCs killed in current level //FIXME should be SpriteType
    extern std::vector<TreasureType> collected_treasures; //list of loot collected in current level

}

#endif //SPELUNKYDS_CONSTS_H
