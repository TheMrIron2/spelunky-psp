//
// Created by dbeef on 2/23/19.
//

#include "InputHandler.h"

#include <pspctrl.h>

void InputHandler::updateInput() {
    {
        sceCtrlReadBufferPositive(&pad, 1);
        if (pad.Buttons != 0) {
            y_key_down = static_cast<bool>(pad.Buttons & PSP_CTRL_SQUARE);
            y_key_held = static_cast<bool>(pad.Buttons & PSP_CTRL_SQUARE);
            x_key_down = static_cast<bool>(pad.Buttons & PSP_CTRL_TRIANGLE);
            a_key_down = static_cast<bool>(pad.Buttons & PSP_CTRL_CIRCLE);
            b_key_down = static_cast<bool>(pad.Buttons & PSP_CTRL_CROSS);
            b_key_held = static_cast<bool>(pad.Buttons & PSP_CTRL_CROSS);
            up_key_held = static_cast<bool>(pad.Buttons & PSP_CTRL_UP);
            down_key_held = static_cast<bool>(pad.Buttons & PSP_CTRL_DOWN);
            left_key_held = static_cast<bool>(pad.Buttons & PSP_CTRL_LEFT);
            right_key_held = static_cast<bool>(pad.Buttons & PSP_CTRL_RIGHT);
            l_bumper_down = static_cast<bool>(pad.Buttons & PSP_CTRL_LTRIGGER);
            l_bumper_held = static_cast<bool>(pad.Buttons & PSP_CTRL_LTRIGGER);
            r_bumper_down = static_cast<bool>(pad.Buttons & PSP_CTRL_RTRIGGER);
            r_bumper_down = static_cast<bool>(pad.Buttons & PSP_CTRL_RTRIGGER);
        } else {
            y_key_down = false;
            y_key_held = false;
            x_key_down = false;
            a_key_down = false;
            b_key_down = false;
            b_key_held = false;
            up_key_held = false;
            down_key_held = false;
            left_key_held = false;
            right_key_held = false;
            l_bumper_down = false;
            l_bumper_held = false;
            r_bumper_down = false;
            r_bumper_down = false;
        }
    }
}

InputHandler::InputHandler() {
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}
