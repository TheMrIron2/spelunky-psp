//
// Created by xdbeef on 22.07.18.
//
#ifndef SPELUNKYDS_SKELETON_H
#define SPELUNKYDS_SKELETON_H

#include "_BaseCreature.h"
#include "../_common/Orientation.hpp"
#include "../memory/SpriteInfo.h"

//http://spelunky.wikia.com/wiki/Skeleton
class Skeleton : public BaseCreature {

public:

    static constexpr u8 skeleton_sprite_width = 16;
    static constexpr u8 skeleton_sprite_height = 16;
    static constexpr u16 skeleton_physical_width = 16;
    static constexpr u16 skeleton_physical_height = 16;
    static constexpr SpritesheetType skeleton_spritesheet_type = SpritesheetType::SKELETON_SPIDER;

    Skeleton(int x, int y) : BaseCreature(
            x,
            y,
            skeleton_sprite_width,
            skeleton_sprite_height,
            skeleton_spritesheet_type,
            skeleton_physical_width,
            skeleton_physical_height,
            CreatureType::SKELETON
    ) {
        hitpoints = 1;
        sprite_state = Orientation::LEFT;
        init_sprites();
    }

    // Base creature overrides

    void update_creature_specific() override;

    void introduce_yourself() override { printf("WHIP\n"); };

    void apply_dmg(int dmg_to_apply) override;

    bool can_update_collidable() const override { return !_ready_to_dispose; }

    // IRenderable overrides

    void init_sprites() override;

    void delete_sprites() override;

    void update_sprites_position() override;

    // ICollidable overrides

    bool can_apply_friction() const override { return true; }

    bool can_apply_gravity() const override { return true; }

    // Other, creature specific

    void set_sprite_walking();

    void set_sprite_summoning();

    void check_if_can_be_summoned();

    void set_sprite_pile_of_bones();

    void match_animation();

    void spawn_remnants();
    
    bool death_speed{};
    double pos_inc_timer{};
    SpriteInfo *mainSpriteInfo{};
    SpriteInfo *subSpriteInfo{};
    u8 *frameGfx{};
    double change_turn_timer{};
    double summoning_delay_timer{};
    int anim_frame_counter{};
    double anim_frame_timer{};
    bool set_up{};
    bool summoned{};
    bool can_be_summoned{};
    Orientation main_dude_orientation_at_summoning_moment{};
    
};


#endif //SPELUNKYDS_SKELETON_H
