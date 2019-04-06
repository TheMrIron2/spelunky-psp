//
// Created by xdbeef on 15.05.18.
//

#ifndef SPELUNKYDS_SPIKES_H
#define SPELUNKYDS_SPIKES_H

#include "_BaseCreature.h"

//http://spelunky.wikia.com/wiki/Spikes
class Spikes : public BaseCreature {
    
    static constexpr u8 spikes_sprite_width = 16;
    static constexpr u8 spikes_sprite_height = 16;
    static constexpr u8 spikes_physical_width = 16;
    static constexpr u8 spikes_physical_height = 13;
    static constexpr SpritesheetType spikes_spritesheet_type = SpritesheetType::SPIKES_COLLECTIBLES;

public:

    Spikes(int x, int y) : BaseCreature(
            x,
            y,
            spikes_sprite_width,
            spikes_sprite_height,
            spikes_spritesheet_type,
            spikes_physical_width,
            spikes_physical_height,
            CreatureType::SPIKES
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

    // Spikes are completely static.
    bool can_apply_friction() const override { return false; }
    bool can_apply_gravity() const override { return false; }

    // Other, creature specific

    // True, if spikes killed anything.
    // Then, graphical representation of spikes becomes red.
    bool _blood{};
    SpriteInfo *_main_sprite_info{};
    SpriteInfo *_sub_sprite_info{};

};


#endif //SPELUNKYDS_SPIKES_H
