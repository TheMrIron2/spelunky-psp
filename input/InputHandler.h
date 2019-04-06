//
// Created by dbeef on 2/23/19.
//

#ifndef SPELUNKY_PSP_INPUTHANDLER_H
#define SPELUNKY_PSP_INPUTHANDLER_H

#include <pspctrl.h>

/**
 * This class has identical public interface as the SpelunkyDS one.
 * For keeping codebase coherent, I didn't change 'x' buttons to 'triangle' buttons etc.,
 * so use this mapping for a reference:
 *
 * X -> triangle
 * Y -> square
 * A -> circle
 * B -> cross
 *
 * keysDown - recently pressed keys
 * keysHeld - keys that are currently hold
 *
 * Didn't figure out how to read down/held keys differently, so for now all
 * keys hold value of held keys.
 */

class InputHandler {
public:

    InputHandler();

    void updateInput();

    int keys_held{};
    int keys_down{};
    bool stop_handling{};

    bool left_key_held{};
    bool right_key_held{};
    bool down_key_held{};
    bool up_key_held{};
    bool b_key_held{};
    bool y_key_held{};
    bool l_bumper_held{};
    bool r_bumper_held{};
    bool r_bumper_down{};
    bool l_bumper_down{};
    bool x_key_down{};
    bool y_key_down{};
    bool a_key_down{};
    bool b_key_down{};

private:
    SceCtrlData pad{};

};

#endif //SPELUNKY_PSP_INPUTHANDLER_H
