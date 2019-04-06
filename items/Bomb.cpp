//
// Created by xdbeef on 04.04.18.
//

#include <math.h>

#include "Bomb.hpp"
#include "../animations/Flame.hpp"
#include "../decorations/Explosion.h"
#include "../globals/GlobalsDeclarations.hpp"
#include "../memory/SpriteUtils.hpp"
#include "../collisions/Collisions.hpp"
#include "../tiles/LevelRenderingUtils.hpp"

void Bomb::update_item_specific() {

    if (_ready_to_dispose) return;

    if (_activated && !armed) {
        set_sprite_armed();
        armed = true;
        armedTimer = 0;
    }

    if (armed) {

        armedTimer += *global::timer;

        if (armedTimer < ARMED_TIME_BLINK_SLOW) {

            if ((armedTimer) % 250 < 125)
                set_sprite_disarmed();
            else
                set_sprite_armed();

        } else if (armedTimer < ARMED_TIME_BLINK_FAST) {

            if ((armedTimer) % 120 < 60)
                set_sprite_disarmed();
            else
                set_sprite_armed();

        } else {
            explode();
            global::camera->shake();
            _ready_to_dispose = true;
        }
    }

    update_sprites_position();
    kill_creatures_if_have_speed(1);
}


void Bomb::set_sprite_armed() {
//    u8 *frame_gfx = sprite_utils::get_frame((u8 *) gfx_bombTiles, _sprite_size, 1);
//    sprite_utils::update_frame(frame_gfx, _sprite_size, _main_sprite_info, _sub_sprite_info);
}

void Bomb::set_sprite_disarmed() {
//    u8 *frame_gfx = sprite_utils::get_frame((u8 *) gfx_bombTiles, _sprite_size, 0);
//    sprite_utils::update_frame(frame_gfx, _sprite_size, _main_sprite_info, _sub_sprite_info);
}

void Bomb::init_sprites() {

    delete_sprites();

//    _sub_sprite_info = global::sub_oam_manager->initSprite(gfx_bombPal, gfx_bombPalLen,
//                                                           nullptr, _sprite_size, ObjSize::OBJSIZE_8,
//                                                           BOMB, true, false, LAYER_LEVEL::MIDDLE_TOP);
//    _main_sprite_info = global::main_oam_manager->initSprite(gfx_bombPal, gfx_bombPalLen,
//                                                             nullptr, _sprite_size, ObjSize::OBJSIZE_8,
//                                                             BOMB, true, false, LAYER_LEVEL::MIDDLE_TOP);
    if (armed) {
        if (armedTimer < ARMED_TIME_BLINK_SLOW) {
            if ((armedTimer) % 250 < 125)
                set_sprite_disarmed();
            else
                set_sprite_armed();
        } else if (armedTimer < ARMED_TIME_BLINK_FAST) {
            if ((armedTimer) % 120 < 60)
                set_sprite_disarmed();
            else
                set_sprite_armed();
        }
    } else set_sprite_disarmed();

    update_sprites_position();

    sprite_utils::set_vertical_flip(false, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_horizontal_flip(false, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_visibility(true, _main_sprite_info, _sub_sprite_info);
//    sprite_utils::set_priority(OBJPRIORITY_0, _main_sprite_info, _sub_sprite_info);
}

void Bomb::explode() {

    for (int a = 0; a < 4; a++) {
        auto *flame = new Flame(_x, _y);
        if (a % 2 == 0)
            flame->_x_speed = (1.3 / a);
        else
            flame->_x_speed = (-1.3 / a);

        flame->_y_speed = (-2 / a);
        global::creatures_to_add.push_back(flame);
    }

    mmEffect(SFX_XEXPLOSION);

    int xx = floor_div(this->_x + 0.5 * _sprite_width, TILE_W);
    int yy = floor_div(this->_y + 0.5 * _sprite_height, TILE_H);

    Collisions::bombNeighboringTiles(global::current_level->map_tiles, xx, yy);
    global::game_state->bombed = true;

    auto *explosion = new Explosion(_x - 32, _y - 32);
    global::decorations_to_add.push_back(explosion);

    sprite_utils::set_visibility(false, _main_sprite_info, _sub_sprite_info);
}
