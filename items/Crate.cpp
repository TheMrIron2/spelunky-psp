//
// Created by xdbeef on 16.05.18.
//

#include <cstdlib>
#include <cstdio>
#include "Crate.hpp"
#include "../globals/GlobalsDeclarations.hpp"
#include "../memory/SpriteUtils.hpp"
#include "../decorations/GotCollectible.hpp"
#include "_ItemsUtils.hpp"

void Crate::update_item_specific() {

    if (_ready_to_dispose) return;

    if (!_dropped_loot && global::input_handler->up_key_held && check_collision(global::main_dude)) {
        mmEffect(SFX_XPICKUP);
        _hold_by_main_dude = false;
        global::main_dude->holding_item = false;
        drop_loot();
    } else if (_activated) {
        // FIXME For now, throwing a chest requires pressing throwing key (Y) twice.
        // Launch throwing code manually?
        // write function that would work i.e like: throwItem(this);
    }

    if (_dropped_loot) play_collectible_animation();

    kill_creatures_if_have_speed(1);

    update_sprites_position();

    // TODO Let's make a function pointer for this, so it wouldn't be updated every frame,
    //  but rather every pickup/leaving item.
//    if (_hold_by_main_dude)
//        sprite_utils::set_priority(OBJPRIORITY_0, _main_sprite_info, _sub_sprite_info);
//    else
//        sprite_utils::set_priority(OBJPRIORITY_1, _main_sprite_info, _sub_sprite_info);


}

void Crate::init_sprites() {

    delete_sprites();

//    _sub_sprite_info = global::sub_oam_manager->initSprite(gfx_spike_collectibles_flamePal,
//                                                           gfx_spike_collectibles_flamePalLen,
//                                                           nullptr, _sprite_size, ObjSize::OBJSIZE_16,
//                                                           _spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);
//    _main_sprite_info = global::main_oam_manager->initSprite(gfx_spike_collectibles_flamePal,
//                                                             gfx_spike_collectibles_flamePalLen,
//                                                             nullptr, _sprite_size, ObjSize::OBJSIZE_16,
//                                                             _spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);
    if (!_activated) {
//        u8 *frame_gfx = sprite_utils::get_frame((u8 *) gfx_spike_collectibles_flameTiles, _sprite_size, 4);
//        sprite_utils::update_frame(frame_gfx, _sprite_size, _main_sprite_info, _sub_sprite_info);
    } else
        play_collectible_animation();

    sprite_utils::set_visibility(true, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_vertical_flip(false, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_horizontal_flip(false, _main_sprite_info, _sub_sprite_info);
    update_sprites_position();

    // TODO Let's make a function pointer for this, so it wouldn't be updated every frame,
    //  but rather every pickup/leaving item.
//    if (_hold_by_main_dude)
//        sprite_utils::set_priority(OBJPRIORITY_0, _main_sprite_info, _sub_sprite_info);
//    else
//        sprite_utils::set_priority(OBJPRIORITY_1, _main_sprite_info, _sub_sprite_info);

}

//TODO lower chances for good items
void Crate::drop_loot() {

    _dropped_loot = true;

    int r = rand() % 3;
    //drop rope or bomb
    if (r == 0 || r == 1) {

        GotCollectible *g;

        if (r == 0) {
            global::hud->ropes += 4;
            g = new GotCollectible(_x - 12, _y - 20, GotCollectible::Type::ROPE);
        } else {
            global::hud->bombs += 4;
            g = new GotCollectible(_x - 12, _y - 20, GotCollectible::Type::BOMB);
        }

        global::hud->draw_level_hud();

        global::decorations_to_add.push_back(g);
    } else {
        collectibles_utils::spawn_random_item(this->_x, this->_y);
    }

}

void Crate::play_collectible_animation() {

    _anim_frame_timer += *global::timer;

    if (_anim_frame_timer > 75) {
        _anim_frame++;
        _anim_frame_timer = 0;
    }

    if (_anim_frame >= 6) {
        _ready_to_dispose = true;
        sprite_utils::set_visibility(false, _main_sprite_info, _sub_sprite_info);
    } else {
//        u8 *frame_gfx;
//        frame_gfx = sprite_utils::get_frame((u8 *) gfx_spike_collectibles_flameTiles, _sprite_size, 5 + _anim_frame);
//        sprite_utils::update_frame(frame_gfx, _sprite_size, _main_sprite_info, _sub_sprite_info);
    }

}
