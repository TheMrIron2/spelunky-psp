//
// Created by xdbeef on 01.04.18.
//
// FIXME Probably shoudln't do this manually
#define SYS 1
#define LOGME 0

#include <assert.h>
#include <cstdio>
#include <GL/gl.h>
#include "OamManager.hpp"
#include "../glchk.h"


#define RGBA4444(r, g, b, a)    ((((r) << 8) & 0xf000) | (((g) << 4) & 0x0f00) | (((b)     ) & 0x00f0) | (((a) >> 4) & 0x000f))

void OAMManager::initTexture(const unsigned char *imagePtr, int file_width, int file_height, SpritesheetType type) {

    GLCHK(glBindTexture(GL_TEXTURE_2D, 2));

    int offset = 0;
    unsigned long index = 0;

    auto tex16 = new unsigned short[file_width * file_height];


    for (int i = 0; i < file_width * file_height; i++) {

        if (imagePtr[((offset + index) * 4) + 0] == 33 && imagePtr[((offset + index) * 4) + 1] == 156 && imagePtr[
        ((offset + index) * 4) + 2] == 0)
        {
            tex16[i] = RGBA4444(0,
                                0,
                                0,
                                0);
        }
        else
        {
            tex16[i] = RGBA4444(imagePtr[((offset + index) * 4) + 0],
                                imagePtr[((offset + index) * 4) + 1],
                                imagePtr[((offset + index) * 4) + 2],
                                imagePtr[((offset + index) * 4) + 3]);

        }

        index++;
    }
    GLCHK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, file_width, file_height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4,
                       &tex16[0]));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

    auto *tex = new Texture();
    tex->id = 2;
    tex->width = file_width;
    tex->height = file_height;
    tex->type = type;
    textures.push_back(tex);

    delete[] tex16;

}

SpriteInfo *OAMManager::initSprite(SpritesheetType type, int width, int height) {

    auto info = new SpriteInfo();

    info->width = width;
    info->height = height;
    info->isHidden = false;
    info->texture = nullptr;

    for (int a = 0; a < textures.size(); a++) {
        if (textures[a] && textures[a]->type == type) {
            info->texture = textures[a];
            break;
        }
    }

    if (!info->texture) assert(false);

    oamTable.push_back(info);

    return info;
}

void OAMManager::render() {
    for (int a = 0; a < oamTable.size(); a++) {
        if (oamTable[a] && !oamTable[a]->isHidden) {
            oamTable[a]->render();
        }
    }
}
