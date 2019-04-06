//
// Created by dbeef on 2/23/19.
//

#ifndef SPELUNKYPSP_CAMERA_H
#define SPELUNKYPSP_CAMERA_H

class Camera {
public:

    Camera();

    void update();

    void apply_map_boundaries();

    void instant_focus();

    void incremental_focus(int camera_speed);

    inline void shake() { shakescreen_duration_timer = 350; }

    bool follow_main_dude{};
    double position_update_timer{};

    float x{};
    float y{};

    double shakescreen_duration_timer{};
    int x_shake_direction{};
    int y_shake_direction{};

private:

    void apply_shaking();

};

#endif //SPELUNKYPSP_CAMERA_H
