#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <GLES/egl.h>

#include "tiles/LevelGenerator.hpp"
#include "tiles/Level.hpp"
#include "rooms/ExitRooms.hpp"
#include "tiles/MapTileType.h"

// FIXME Probably shoudln't do this manually
#define SYS 1
#define LOGME 0

#include "glchk.h"
#include "input/InputHandler.h"
#include "time/TimeUtils.h"
#include "utils/Consts.h"
#include "tiles/LevelRenderingUtils.hpp"

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <pspgum.h>
#include <stdio.h>
#include <pspsystimer.h>
#include <time.h>
#include <angelscript.h>

#include "globals/GlobalsDefinitions.hpp"
#include "globals/GlobalsDeclarations.hpp"
#include "GameLoop.hpp"

PSP_MODULE_INFO("Spelunky", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static
void reshape(int w, int h) {
    GLCHK(glViewport(0, 0, w, h));
    GLCHK(glMatrixMode(GL_PROJECTION));
    dumpmat(GL_PROJECTION_MATRIX, "fresh proj");
    GLCHK(glLoadIdentity());
    dumpmat(GL_PROJECTION_MATRIX, "ident proj");
    // 480 / 272 = ~1.7
    GLCHK(glOrtho(-8.45f * 1.7647058823529411f, 8.45f * 1.7647058823529411f, 8.45f, -8.45f, -8.45f, 8.45f));
    dumpmat(GL_PROJECTION_MATRIX, "ortho proj");
    GLCHK(glMatrixMode(GL_MODELVIEW));
    GLCHK(glLoadIdentity());
    dumpmat(GL_MODELVIEW_MATRIX, "ident modelview");
    dumpmat(GL_PROJECTION_MATRIX, "non-current proj");
    gluLookAt(global::camera->x, global::camera->y, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    dumpmat(GL_MODELVIEW_MATRIX, "lookat modelview");
    glLoadIdentity();
}


#define NTEX 8
static GLuint texture_indexes[NTEX];

int main(int argc, char *argv[]) {

    global::init_globals();

    global::current_level->init_map_tiles();
    global::current_level->initialise_tiles_from_splash_screen(MAIN_MENU);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutReshapeFunc(reshape);
    int window = glutCreateWindow(__FILE__);
    glutDisplayFunc(gameloop::run);

    GLCHK(glGenTextures(NTEX, texture_indexes));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCHK(glEnable(GL_TEXTURE_2D));

    eglSwapInterval(reinterpret_cast<void *>(window), 1);

    global::current_level->upload_tilesheet();

    GLint max;
    // 512
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
    printf("Max texture size: %i\n", max);

    // upload spelunker spritesheet
    extern unsigned char gfx_spelunker_start[];
    global::oam_manager->initTexture(&gfx_spelunker_start[0], 64, 512, SpritesheetType::MAIN_DUDE);
    //
    global::main_dude = new MainDude(static_cast<int>(global::camera->x + 10), static_cast<int>(global::camera->y + 200));

    global::game_state->reset_main_dude();

    time_utils::start();
    glutMainLoop();
    return 0;
}

