//
// Created by xdbeef on 28.04.18.
//

#ifndef SPELUNKYDS_BLOOD_H
#define SPELUNKYDS_BLOOD_H

#define BLOOD_ANIM_FRAME_DELTA 90

#include <vector>
#include "../creatures/_BaseCreature.h"
#include "BloodElement.hpp"
#include "../memory/SpriteInfo.h"

//blood trail animation:
//spawn 3-4 entities with sBlood animation (3 frames)
//every of them spawn every .5 second animation sBloodTrail, every one of them should be one frame in forward, comprared to the latter
//if spawned 6 of them, then the sBlood animation entities should finish with sBloodTrail animation

class Blood : public BaseCreature {

public:

    Blood(int x, int y) : BaseCreature(
            x,
            y,
            blood_sprite_width,
            blood_sprite_height,
            blood_spritesheet_type,
            blood_physical_width,
            blood_physical_height,
            CreatureType::BLOOD
    ) {
        _pos_update_delta = 30;
        init_sprites();
    }

    // Base creature overrides

    void update_creature_specific() override;

    void introduce_yourself() override { printf("WHIP\n"); };

    void apply_dmg(int dmg_to_apply) override {};

    bool can_update_collidable() const override { return !finished; }

    // IRenderable overrides

    void init_sprites() override;

    void delete_sprites() override;

    void update_sprites_position() override;

    // ICollidable overrides

    bool can_apply_friction() const override { return true; }

    bool can_apply_gravity() const override { return true; }

    // Other, creature specific

    void spawn_blood();

    void match_animation();

    double *timer {};
    double pos_inc_timer{};
    SpriteInfo *mainSpriteInfo {};
    SpriteInfo *subSpriteInfo {};
    u8 *frameGfx{};
    bool finished{};
    int currentFrame{};
    double animFrameTimer{};
    std::vector<BloodElement *> bloodTrail;
    double living_timer{};
    double time_since_last_spawn{};

};



#endif //SPELUNKYDS_BLOOD_H
