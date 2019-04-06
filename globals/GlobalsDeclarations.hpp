//
// Created by xdbeef on 24.02.18.
//

#ifndef SPELUNKYDS_CONSTS_H
#define SPELUNKYDS_CONSTS_H

#include "../input/InputHandler.h"

#define GRAVITY_DELTA_SPEED 0.22 //FIXME isn't it mob-specific?
#define DEFAULT_DMA_CHANNEL 3

//https://stackoverflow.com/questions/21505021/extern-and-global-same-variable-in-same-file
//https://stackoverflow.com/questions/37323227/benefits-of-using-extern-declaration-in-same-file-as-definition
namespace global {
    extern float *timer;
    extern InputHandler *input_handler;
}

#endif //SPELUNKYDS_CONSTS_H
