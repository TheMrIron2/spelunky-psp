//
// Created by xdbeef on 19.05.18.
//


#include "SpringShoes.hpp"
#include "Mitt.hpp"
#include "../memory/SpriteUtils.hpp"
#include "../decorations/GotCollectible.hpp"
#include "../globals/GlobalsDeclarations.hpp"


void Mitt::update_item_specific() {

    if (_ready_to_dispose) return;

    sprite_utils::set_vertical_flip(false, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_horizontal_flip(false, _main_sprite_info, _sub_sprite_info);
    update_anim_icon(_x, _y, _physical_width);

    if (collected) return;

    if (_bought && check_if_can_be_equipped())
        equip();
    else if (!_bought && !_hold_by_main_dude)
        check_if_can_be_pickuped();

    if (_hold_by_main_dude) {
        if (shopping_transaction(this)) {
            collected = true;
            equip();
        }
    }

    update_sprites_position();
}

void Mitt::init_sprites() {

    delete_sprites();

//    _sub_sprite_info = global::sub_oam_manager->initSprite(gfx_saleablePal, gfx_saleablePalLen,
//                                                        nullptr, _sprite_size, ObjSize::OBJSIZE_16,
//                                                        _spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);
//    _main_sprite_info = global::main_oam_manager->initSprite(gfx_saleablePal, gfx_saleablePalLen,
//                                                          nullptr, _sprite_size, ObjSize::OBJSIZE_16,
//                                                          _spritesheet_type, true, false, LAYER_LEVEL::MIDDLE_TOP);

    sprite_utils::set_visibility(true, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_vertical_flip(false, _main_sprite_info, _sub_sprite_info);
    sprite_utils::set_horizontal_flip(false, _main_sprite_info, _sub_sprite_info);
    update_sprites_position();
    match_animation();
}

void Mitt::equip() {
    collected = true;

    auto *g = new GotCollectible(_x - 12, _y - 20, GotCollectible::Type::ITEM);
    global::decorations_to_add.push_back(g);

    if (!global::main_dude->carrying_mitt) {
        global::main_dude->carrying_mitt = true;
        update_sprites_position();
        _x = HUD_ITEMS_ROW_X;
        _y = global::hud->items_offset_y;
        global::hud->increment_offset_on_grabbed_item();
    } else {
        sprite_utils::set_visibility(false, _main_sprite_info, _sub_sprite_info);
        _ready_to_dispose = true;
    }

}

void Mitt::match_animation() {
//    u8 *frame_gfx = sprite_utils::get_frame((u8 *) gfx_saleableTiles, _sprite_size, 0);
//    sprite_utils::update_frame(frame_gfx, _sprite_size, _main_sprite_info, _sub_sprite_info);
}

