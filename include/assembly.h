#pragma once

#include "vex.h"

using namespace vex;

class Assembly {
public:
    // Constructor: pass in all motors and pistons
    Assembly(
        mik::motor intake_motor,
        mik::motor lever_motor,
        mik::piston matchhloader_piston,
        mik::piston doinker_piston,
        mik::piston flap,
        mik::piston lift_piston_left,
        mik::piston lift_piston_right
    );

    // Optional initialization
    void init();

    // Main control loop (call inside usercontrol)
    void control();

    // ----------------------
    // MOTOR CONTROLS
    // ----------------------
    void intake_motor_control();
    void lever_motor_control();

    // ----------------------
    // PISTON CONTROLS
    // ----------------------
    void matchhloader_piston_control();
    void doinker_piston_control();
    void flap_control();

    void lift_piston_left_control();
    void lift_piston_right_control();

    // Lift helpers
    void lift_toggle();
    void lift_extend();
    void lift_retract();

    // ----------------------
    // DEVICE MEMBERS
    // ----------------------
    mik::motor intake_motor;
    mik::motor lever_motor;

    mik::piston matchhloader_piston;
    mik::piston doinker_piston;
    mik::piston flap;

    mik::piston lift_piston_left;
    mik::piston lift_piston_right;
};
