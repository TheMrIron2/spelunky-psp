//
// Created by xdbeef on 01.06.18.
//

#ifndef SPELUNKYDS_FALL_BLOOP_H
#define SPELUNKYDS_FALL_BLOOP_H

#include "../_common/Orientation.hpp"
#include "../creatures/_BaseCreature.h"
#include "../memory/SpriteInfo.h"

#define FALL_POOF_SPRITE_HEIGHT 8
#define FALL_POOF_SPRITE_WIDTH 8
#define FALL_POOF_SPRITE_SIZE FALL_POOF_SPRITE_WIDTH * FALL_POOF_SPRITE_HEIGHT

#define FALL_POOF_PHYSICAL_HEIGHT 8
#define FALL_POOF_PHYSICAL_WIDTH 8

#define MAX_X_SPEED_FALL_POOF 4
#define MAX_Y_SPEED_FALL_POOF 4

class FallPoof : public BaseCreature {

public:

    static constexpr u8 fall_poof_sprite_width = 16;
    static constexpr u8 fall_poof_sprite_height = 16;
    static constexpr u16 fall_poof_physical_width = 8;
    static constexpr u16 fall_poof_physical_height = 8;
    static constexpr SpritesheetType fall_poof_spritesheet_type = SpritesheetType::BLOOD_ROCK_ROPE_POOF;

    FallPoof(int x, int y) : BaseCreature(
            x,
            y,
            fall_poof_sprite_width,
            fall_poof_sprite_height,
            fall_poof_spritesheet_type,
            fall_poof_physical_width,
            fall_poof_physical_height,
            CreatureType::FALL_POOF
    ) {
        init_sprites();
    }

    // Base creature overrides

    void update_creature_specific() override;

    void introduce_yourself() override { printf("WHIP\n"); };

    void apply_dmg(int dmg_to_apply) override {};

    bool can_update_collidable() const override { return false; }

    // IRenderable overrides

    void init_sprites() override;

    void delete_sprites() override;

    void update_sprites_position() override;

    // ICollidable overrides

    bool can_apply_friction() const override { return false; }

    bool can_apply_gravity() const override { return false; }

    // Other, creature specific
    
    double animFrameTimer{};
    int animFrame{};
    double pos_inc_timer{};
    SpriteInfo *mainSpriteInfo{};
    SpriteInfo *subSpriteInfo{};
    u8 *frameGfx{};
    bool gravity{};
    void match_animation();
};


#endif //SPELUNKYDS_FALL_BLOOP_H
