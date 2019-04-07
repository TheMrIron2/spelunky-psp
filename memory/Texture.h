//
// Created by dbeef on 4/7/19.
//

#ifndef SPELUNKYPSP_TEXTURE_H
#define SPELUNKYPSP_TEXTURE_H


struct Texture{
    // for every palette type load texture here
    SpritesheetType type;
    unsigned int id;
    int width;
    int height;
    const unsigned char * imagePtr;
};

#endif //SPELUNKYPSP_TEXTURE_H
