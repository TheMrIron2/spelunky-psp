//
// Created by xdbeef on 02.06.18.
//

#include <cstdio>
#include "SpikeShoes.hpp"
#include "../memory/SpriteUtils.hpp"
#include "../decorations/GotCollectible.hpp"
#include "../globals/GlobalsDeclarations.hpp"

void SpikeShoes::update_item_specific() {
    if (_ready_to_dispose) return;

    update_anim_icon(_x, _y, _physical_width);

    if (_render_in_hud) return;

    if (_bought && check_if_can_be_equipped())
        equip();
    else if (!_bought && !_hold_by_main_dude)
        check_if_can_be_pickuped();

    if (_hold_by_main_dude) {

        if (_bought || shopping_transaction(this)) {
            _render_in_hud = true;
            equip();
        }

    }

    update_sprites_position();
}

void SpikeShoes::init_sprites() {

    delete_sprites();
//
//    _sub_sprite_info = global::sub_oam_manager->initSprite(gfx_saleablePal, gfx_saleablePalLen,
//                                                           nullptr, _sprite_size, ObjSize::OBJSIZE_16,
//                                                           _spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);
//    _main_sprite_info = global::main_oam_manager->initSprite(gfx_saleablePal, gfx_saleablePalLen,
//                                                             nullptr, _sprite_size, ObjSize::OBJSIZE_16,
//                                                             _spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);

//    u8 *frame_gfx = sprite_utils::get_frame((u8 *) gfx_saleableTiles, _sprite_size, 12);
//    sprite_utils::update_frame(frame_gfx, _sprite_size, _main_sprite_info, _sub_sprite_info);

    update_sprites_position();
    sprite_utils::set_vertical_flip(false, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_horizontal_flip(false, _main_sprite_info, _sub_sprite_info);

    if (_render_in_hud) {
//        _main_sprite_info->priority = OBJPRIORITY_0;
        _sub_sprite_info->isHidden = true;
        _main_sprite_info->isHidden = false;
    } else
        sprite_utils::set_visibility(true, _main_sprite_info, _sub_sprite_info);

}

void SpikeShoes::equip() {

    _render_in_hud = true;

    auto *g = new GotCollectible(_x - 12, _y - 20, GotCollectible::Type::ITEM);
    global::decorations_to_add.push_back(g);

    if (!global::main_dude->carrying_spike_shoes) {

        global::main_dude->carrying_spike_shoes = true;

        _x = HUD_ITEMS_ROW_X;
        _y = global::hud->items_offset_y;
        global::hud->increment_offset_on_grabbed_item();

        _sub_sprite_info->isHidden = true;
        _main_sprite_info->isHidden = false;
//        _main_sprite_info->priority = OBJPRIORITY_0;
        update_sprites_position();

    } else {
        sprite_utils::set_visibility(false, _main_sprite_info, _sub_sprite_info);
        _ready_to_dispose = true;
    }

}
