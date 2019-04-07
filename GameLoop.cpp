
// FIXME Probably shoudln't do this manually
#define SYS 1
#define LOGME 0

#include <cstdlib>
#include <GL/glut.h>
#include "GameLoop.hpp"
#include "tiles/PopulatingUtils.hpp"
#include "time/TimeUtils.h"
#include "memory/OamUtils.hpp"
#include "globals/GlobalsDeclarations.hpp"
#include "glchk.h"

static void update_creatures_to_add() {
    unsigned long size = global::creatures_to_add.size();
    for (unsigned long a = 0; a < size; a++) {
        if (global::creatures_to_add.at(a)) {
            BaseCreature *o = global::creatures_to_add.at(a);
            global::creatures.push_back(o);
        }
    }
    if (size)
        global::creatures_to_add.clear();
}

static void update_decorations_to_add() {
    unsigned long size = global::decorations_to_add.size();
    for (unsigned long a = 0; a < size; a++) {
        if (global::decorations_to_add.at(a)) {
            BaseDecoration *o = global::decorations_to_add.at(a);
            global::decorations.push_back(o);
        }
    }
    if (size)
        global::decorations_to_add.clear();
}

static void update_treasures_to_add() {
    unsigned long size = global::treasures_to_add.size();
    for (unsigned long a = 0; a < size; a++) {
        if (global::treasures_to_add.at(a)) {
            BaseTreasure *o = global::treasures_to_add.at(a);
            global::treasures.push_back(o);
        }
    }
    if (size)
        global::treasures_to_add.clear();
}

static void update_items_to_add() {
    unsigned long size = global::items_to_add.size();
    for (unsigned long a = 0; a < size; a++) {
        if (global::items_to_add.at(a)) {
            BaseItem *o = global::items_to_add.at(a);
            global::items.push_back(o);
        }
    }
    if (size)
        global::items_to_add.clear();
}

void gameloop::run() {

    time_utils::update_ms_since_last_frame();

    global::input_handler->updateInput();
    if (global::input_handler->a_key_down)global::camera->x += 1.0 / 16;
    if (global::input_handler->y_key_down)global::camera->x -= 1.0 / 16;
    if (global::input_handler->x_key_down)global::camera->y -= 1.0 / 16;
    if (global::input_handler->b_key_down)global::camera->y += 1.0 / 16;

//    if (global::input_handler->left_key_held)global::main_dude->_x_speed -= 1;
//    if (global::input_handler->right_key_held)global::main_dude->_x_speed += 1;
//    if (global::input_handler->up_key_held)global::main_dude->_y_speed += 1;
//    if (global::input_handler->down_key_held)global::main_dude->_y_speed -= 1;

    global::main_dude->_y_speed = 0;
    global::main_dude->update();
    global::main_dude->whip->update();
    global::main_dude->handle_key_input();

    GLCHK(glShadeModel(GL_SMOOTH));
    GLCHK(glClear(GL_COLOR_BUFFER_BIT));
    GLCHK(glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE));
    GLCHK(glEnable(GL_BLEND));
    GLCHK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    global::current_level->write_tiles_to_map();
    global::oam_manager->render();

    glutSwapBuffers();
    glutPostRedisplay();

    printf("%i %i\n", global::main_dude->_x, global::main_dude->_y);
//    printf("%f %f\n", global::camera->x, global::camera->y);


//
//
//    //init positions with main menu values:
//    global::camera->x = 0;
//    global::camera->y = 127;
////    global::entities.push_back(global::main_dude);
//
//    global::main_dude = new MainDude(224, 300); //TODO Some constexpr file for xy
//
//    global::hud->init();
//    populate_main_menu(); //TODO Game state function for matching this?
//
//    //the game loop. If exited, SpelunkyDS returns 0 and gets back to the menu
//    while (true) {
//
//        time_utils::update_ms_since_last_frame();
//        global::input_handler->updateInput();
//
//        if (global::game_state->bombed) { //TODO Can't this be done in the Bomb class?
//            global::current_level->update_level();
//            global::game_state->bombed = false;
//            for (auto &creature : global::creatures)
//                (*creature)._bottom_collision = false;
//            for (auto &item : global::items)
//                (*item)._bottom_collision = false;
//            for (auto &treasures : global::treasures)
//                (*treasures)._bottom_collision = false;
//            global::main_dude->_bottom_collision = false;
//        }
//
//        global::camera->update();
//
//        update_creatures_to_add();
//        update_decorations_to_add();
//        update_treasures_to_add();
//        update_items_to_add();
//
//        global::main_dude->update();
//        global::main_dude->whip->update();
//
//        for (auto &creature : global::creatures) {
//            if (creature && !creature->_ready_to_dispose) {
//                creature->update();
//            }
//        }
//
//        for (auto &item : global::items) {
//            if (item && !item->_ready_to_dispose) {
//                item->update();
//            }
//        }
//
//        for (auto &decoration : global::decorations) {
//            if (decoration) {
//                decoration->update();
//            }
//        }
//
//        for (auto &treasure : global::treasures) {
//            if (treasure && !treasure->_ready_to_dispose) {
//                treasure->update();
//            }
//        }
//
//        global::game_state->handle_transition_screen_smooch();
//        global::main_dude->handle_key_input();
//        global::hud->update();
//
////        swiWaitForVBlank();
////        manage_brightness();
//
////        global::camera->write_current_position_to_graphics_engines();
////        global::main_oam_manager->updateOAM();
////        global::sub_oam_manager->updateOAM();
////        oam_utils::clean_unused_oam();
//    }

}
//
////!> this should be done after Vblank (otherwise - crash!)
//void gameloop::manage_brightness() {
//
//    if (global::game_state->just_started_game) {
//        //just started the game, so lowering the brightness to the normal level.
//        //game starts with the maximum brightness, so the transition between DSiMenu++ would look smoother
//        global::game_state->change_brightness_timer += *global::timer;
//
//        if (global::game_state->change_brightness_timer > 100) {
//
//            global::game_state->brightness_level--;
//
//            if (global::game_state->brightness_level == 0)
//                global::game_state->just_started_game = false;
//            else
//                setBrightness(3, global::game_state->brightness_level);
//
//        }
//    }
//
//    if (global::game_state->in_main_menu && global::game_state->exiting_game) {
//        //exiting game, so increasing the brightness to the maximum level so the transition
//        //between the game and DSiMenu++ would be smoother
//        global::game_state->change_brightness_timer += *global::timer;
//
//        if (global::game_state->change_brightness_timer > 100) {
//
//            global::game_state->brightness_level++;
//
//            if (global::game_state->brightness_level > 16)
//                exit(0);
//
//            setBrightness(3, global::game_state->brightness_level);
//
//        }
//    }
//
//}
