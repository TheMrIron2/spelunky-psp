//
// Created by xdbeef on 26.03.18.
//

#define SYS 1
#define LOGME 0

#include <GL/gl.h>
#include <vector>
#include <cmath>
#include "SpriteInfo.h"
#include "../glchk.h"
#include "../tiles/LevelRenderingUtils.hpp"
#include "../globals/GlobalsDeclarations.hpp"



void SpriteInfo::set_texture_pointer_to_tile(int type) {

    int rows = texture->height / 16;
    int columns = texture->width / 16;

    // since coordinates must be normalized (between 0 and 1)
    float x_unit = 1.0f / columns;
    float y_unit = 1.0f / rows;

    float x_offset = 0;
    x_offset += type % 4;
    float y_offset = floor((float) type / 4);

    // now it stores left-upper corner
    x_offset *= x_unit;
    y_offset *= y_unit;

    // left lower  0
    // left upper  1
    // right upper 2
    // right lower 3

    float onePixelX = 1.0f / texture->width;
    float onePixelY = 1.0f / texture->height;

    // right lower
    coordinates[0][0] = x_offset + x_unit - onePixelX; // 1
    coordinates[0][1] = y_offset + onePixelY; // 0

    // right upper
    coordinates[1][0] = x_offset + x_unit - onePixelX; // 1
    coordinates[1][1] = y_offset + y_unit - onePixelY; // 1

    // left upper
    coordinates[2][0] = x_offset + onePixelX; // 0
    coordinates[2][1] = y_offset + y_unit - onePixelY; // 1

    // left lower
    coordinates[3][0] = x_offset + onePixelX; // 0
    coordinates[3][1] = y_offset + onePixelY; // 0

}


void SpriteInfo::updateFrame(u8 *tile, u32 size) {
//    dmaCopyHalfWords(3, tile, &sprite_address[entry->gfxIndex * this->offset_multiplier], size);
}

void SpriteInfo::render() {

    printf("Tile: %i\n", tile);

    GLCHK(glBindTexture(GL_TEXTURE_2D, texture->id));

    set_texture_pointer_to_tile(tile);

    std::vector<GLfloat> batch;

    batch.push_back(coordinates[0][0]);
    batch.push_back(coordinates[0][1]);
    batch.push_back(0 - ((float) x / 16));
    batch.push_back(0 + ((float) y / 16));
    batch.push_back(0);

    batch.push_back(coordinates[1][0]);
    batch.push_back(coordinates[1][1]);
    batch.push_back(0 - ((float) x / 16));
    batch.push_back(1 + ((float) y / 16));
    batch.push_back(0);

    batch.push_back(coordinates[2][0]);
    batch.push_back(coordinates[2][1]);
    batch.push_back(1 - ((float) x / 16));
    batch.push_back(1 + ((float) y / 16));
    batch.push_back(0);

    batch.push_back(coordinates[2][0]);
    batch.push_back(coordinates[2][1]);
    batch.push_back(1 - ((float) x / 16));
    batch.push_back(1 + ((float) y / 16));
    batch.push_back(0);

    batch.push_back(coordinates[3][0]);
    batch.push_back(coordinates[3][1]);
    batch.push_back(1 - ((float) x / 16));
    batch.push_back(0 + ((float) y / 16));
    batch.push_back(0);

    batch.push_back(coordinates[0][0]);
    batch.push_back(coordinates[0][1]);
    batch.push_back(0 - ((float) x / 16));
    batch.push_back(0 + ((float) y / 16));
    batch.push_back(0);

    GLCHK(glMatrixMode(GL_MODELVIEW));
    GLCHK(glLoadIdentity());
    GLCHK(glTranslatef(0, 0, 0));
    dumpmat(GL_PROJECTION_MATRIX, "trans modelview");
    gluLookAt(-global::camera->x, global::camera->y, -1.0f, -global::camera->x, global::camera->y, 0.0f, 0.0f, 1.0f, 0.0f);
    dumpmat(GL_MODELVIEW_MATRIX, "lookat modelview");
    GLCHK(glInterleavedArrays(GL_T2F_V3F, 0, (void *) batch.data()));
    GLCHK(glDrawArrays(GL_TRIANGLES, 0, 6 * 1));

}
