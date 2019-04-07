//
// Created by xdbeef on 06.05.18.
//

#include "TimeUtils.h"
#include "../globals/GlobalsDeclarations.hpp"

#include <pspthreadman.h>
#include <pspsystimer.h>
#include <pspdebug.h>
#include <pspuser.h>
#include <cstdlib>
#include <psprtc.h>
#include <stdio.h>

namespace time_utils {

    static u64 *tick_before{};

    void update_ms_since_last_frame() {

        u32 tick_freq = sceRtcGetTickResolution();

        if (*tick_before == 0) {
            sceRtcGetCurrentTick(tick_before);
        } else {
            u64 temp_tick;
            sceRtcGetCurrentTick(&temp_tick);
            u64 diff = temp_tick - *tick_before;
            float delta = ((float) diff / tick_freq);
            *global::timer = delta * 1000;
            *tick_before = temp_tick;

        }
    }

    void stop() {
        delete tick_before;
    }

    void start() {
        tick_before = new u64(0);
    }

}