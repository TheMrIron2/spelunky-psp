//
// Created by xdbeef on 04.03.18.
//

#ifndef SPELUNKYDS_MAPUTILS_H
#define SPELUNKYDS_MAPUTILS_H


#include <GL/glut.h>
#include <cmath>
#include <GLES/egl.h>

int floor_div(int a, int b);

static void dumpmat(GLenum mat, const char *s) {
    float m[16];
    glGetFloatv(mat, m);
}

void sectorize_map();

#endif //SPELUNKYDS_MAPUTILS_H