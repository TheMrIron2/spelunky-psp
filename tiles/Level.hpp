//
// Created by xdbeef on 04.03.18.
//

#ifndef SPELUNKYDS_LEVELGENERATOR_H
#define SPELUNKYDS_LEVELGENERATOR_H

#include "MapTile.hpp"
#include "Direction.hpp"
#include "SplashScreenType.hpp"
#include "../rooms/RoomType.hpp"
#include "../camera/Camera.h"
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>

//TODO Move from macros to constexpr in other classes too.

const int ROOMS_X = 3;
const int ROOMS_Y = 3;

const int SPLASH_SCREEN_WIDTH = 30;
const int SPLASH_SCREEN_HEIGHT = 17;

const int ROOM_TILE_WIDTH_SPLASH_SCREEN = 16;
const int ROOM_TILE_HEIGHT_SPLASH_SCREEN = 12;

const int ROOM_TILE_WIDTH_GAME = 10;
const int ROOM_TILE_HEIGHT_GAME = 10;

const int MAP_GAME_HEIGHT_TILES = 32;
const int MAP_GAME_WIDTH_TILES = 32;

const int LINE_WIDTH = 64;
const int OFFSET_X = 2; //Offset of 2 tiles, 8 px each
const int OFFSET_Y = 128; //Offset of 128 tiles, 8px  each (2 lines, 64 each)

class Level {

public:

    Level(Camera *c) : camera(c), map_tiles(), layout(), layout_room_ids() {
        //
    }

    Camera *camera;

    //I allocate these tiles on heap on game start, never delete them later. That helps memory fragmentation a lot.
    //Before, I allocated/deallocated them on every level and It caused crashes on malloc after some time (~40 levels).
    MapTile *map_tiles[32][32];

    //holds information on what room type is at specific array index
    RoomType layout[ROOMS_X][ROOMS_Y];

    //holds information on specific variation of room type, that is given from 'layout' array
    //i.e, we have 6 possible 'closed' rooms declared in the closed_rooms.hpp,
    //so this array lets us know, that we have a 'closed' room number 3 (for example) at some place.
    int layout_room_ids[ROOMS_X][ROOMS_Y];

    std::vector<GLfloat> batch;
    float coordinates[4][2];

    //sets all tiles to !existing
    void clean_map_layout();

    void init_map_tiles();

    void set_texture_pointer_to_tile(int type);

    void update_level();

    void write_tiles_to_map();

    void generate_frame();

    void initialise_tiles_from_room_layout();

    void initialise_tiles_from_splash_screen(SplashScreenType splashScreenType);

    void get_first_tile_of_given_type(MapTileType mapTileType, MapTile *&m);

    void upload_tilesheet();

};

#endif //SPELUNKYDS_LEVELGENERATOR_H

