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

PSP_MODULE_INFO("Spelunky", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);


static Camera *camera = new Camera();
static Level *level = new Level(camera);


static
void reshape(int w, int h) {
    GLCHK(glViewport(0, 0, w, h));
    GLCHK(glMatrixMode(GL_PROJECTION));
    dumpmat(GL_PROJECTION_MATRIX, "fresh proj");
    GLCHK(glLoadIdentity());
    dumpmat(GL_PROJECTION_MATRIX, "ident proj");
    // 480 / 272 = ~1.7
    GLCHK(glOrtho(-8 * 1.7, 8 * 1.7, 8, -8, -8, 8));
    dumpmat(GL_PROJECTION_MATRIX, "ortho proj");
    GLCHK(glMatrixMode(GL_MODELVIEW));
    GLCHK(glLoadIdentity());
    dumpmat(GL_MODELVIEW_MATRIX, "ident modelview");
    dumpmat(GL_PROJECTION_MATRIX, "non-current proj");
    gluLookAt(camera->x, camera->y, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    dumpmat(GL_MODELVIEW_MATRIX, "lookat modelview");
    glLoadIdentity();
}


#define NTEX    1
static GLuint texture_indexes[NTEX];

static void display() {

    time_utils::update_ms_since_last_frame();

    GLCHK(glShadeModel(GL_SMOOTH));
    GLCHK(glClear(GL_COLOR_BUFFER_BIT));
    GLCHK(glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE));
    GLCHK(glEnable(GL_BLEND));
    GLCHK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    global::input_handler->updateInput();
    level->write_tiles_to_map();
    glutSwapBuffers();
    glutPostRedisplay();

    if(global::input_handler->a_key_down) camera->x += 1.0 / 16;
    if(global::input_handler->y_key_down) camera->x -= 1.0 / 16;
    if(global::input_handler->x_key_down) camera->y -= 1.0 / 16;
    if(global::input_handler->b_key_down) camera->y += 1.0 / 16;

}


int main(int argc, char *argv[]) {

    level->init_map_tiles();
    level->generate_frame();
    generate_new_level_layout(level);
    level->initialise_tiles_from_room_layout();
//    level->initialise_tiles_from_splash_screen(MAIN_MENU_UPPER);
//    level->initialise_tiles_from_splash_screen(MAIN_MENU_LOWER);

    global::init_globals();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutReshapeFunc(reshape);
    int window = glutCreateWindow(__FILE__);
    glutDisplayFunc(display);

    GLCHK(glGenTextures(NTEX, texture_indexes));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCHK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCHK(glEnable(GL_TEXTURE_2D));

    eglSwapInterval(reinterpret_cast<void *>(window), 1);
    level->upload_tilesheet();
    time_utils::start();
    glutMainLoop();
    time_utils::stop();
    return 0;
}

