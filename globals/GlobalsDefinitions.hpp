//
// Created by xdbeef on 06.05.18.
//

#ifndef SPELUNKYDS_GLOBALS_DEFINITIONS_H
#define SPELUNKYDS_GLOBALS_DEFINITIONS_H

#include "../input/InputHandler.h"
#include "GlobalsDeclarations.hpp"

namespace global {
    float *timer;
    float clean_unused_oam_timer;
    InputHandler *input_handler;
    Level *current_level;
    Camera *camera;
    MainDude *main_dude;
    Hud *hud;
    GameState *game_state;

    std::vector<BaseCreature *> creatures;
    std::vector<BaseCreature *> creatures_to_add;

    std::vector<BaseDecoration *> decorations;
    std::vector<BaseDecoration *> decorations_to_add;

    std::vector<BaseTreasure *> treasures;
    std::vector<BaseTreasure *> treasures_to_add;

    std::vector<BaseItem *> items;
    std::vector<BaseItem *> items_to_add;

    std::vector<SpriteInfo *> sprite_infos; //technically list of wrappers around OAM entries FIXME naming
    std::vector<CreatureType> killed_npcs; //list of NPCs killed in current level //FIXME should be SpriteType
    std::vector<TreasureType> collected_treasures; //list of loot collected in current level

    //https://softwareengineering.stackexchange.com/questions/245236/is-heap-fragmentation-a-problem-in-bare-metal-arm-with-g
    void init_globals() {
        input_handler = new InputHandler();
        timer = new float;
        clean_unused_oam_timer = 0;
        camera = new Camera();
        current_level = new Level(camera);
        main_dude = new MainDude(224, 300);
        hud = new Hud();
        game_state = new GameState();

        //some of the moving objects aren't rendered as entities, like the ArrowTrap, which is render as a map tile,
        //so the the list is bigger, though the maximum number of entities that can be rendered on NDS is 128
        global::creatures.reserve(64);
        //some of the entities in this list may just wait to be disposed, that's why this size is slightly bigger that 128
        global::sprite_infos.reserve(128);
        //I assume there won't be a situation when we'll add more than 64 objects in a single frame
        global::creatures_to_add.reserve(64);

        global::decorations.reserve(64);
        global::decorations_to_add.reserve(64);

        global::treasures.reserve(8);
        global::treasures_to_add.reserve(8);

    }

}
#endif //SPELUNKYDS_GLOBALS_DEFINITIONS_H
