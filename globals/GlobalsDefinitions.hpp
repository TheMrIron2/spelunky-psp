//
// Created by xdbeef on 06.05.18.
//

#ifndef SPELUNKYDS_GLOBALS_DEFINITIONS_H
#define SPELUNKYDS_GLOBALS_DEFINITIONS_H

#include "../input/InputHandler.h"

namespace global {
    float *timer;
    InputHandler *input_handler;

    //https://softwareengineering.stackexchange.com/questions/245236/is-heap-fragmentation-a-problem-in-bare-metal-arm-with-g
    void init_globals() {
        input_handler = new InputHandler();
        timer = new float;
    }

}
#endif //SPELUNKYDS_GLOBALS_DEFINITIONS_H
