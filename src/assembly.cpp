#include "vex.h"

using namespace vex;

// Constructor
Assembly::Assembly(
    mik::motor intake_motor,
    mik::motor lever_motor,
    mik::piston matchhloader_piston,
    mik::piston doinker_piston,
    mik::piston flap,
    mik::piston lift_piston_left,
    mik::piston lift_piston_right
) :
    intake_motor(intake_motor),
    lever_motor(lever_motor),
    matchhloader_piston(matchhloader_piston),
    doinker_piston(doinker_piston),
    flap(flap),
    lift_piston_left(lift_piston_left),
    lift_piston_right(lift_piston_right)
{}

// Optional initialization
void Assembly::init() {}

// Main control loop
void Assembly::control() {
    intake_motor_control();
    lever_motor_control();
    matchhloader_piston_control();
    doinker_piston_control();
    flap_control();
    lift_piston_left_control();
    lift_piston_right_control();

    // ONE BUTTON controls BOTH lift pistons
    if (btnX_new_press(Controller.ButtonX.pressing())) {
        lift_toggle();
    }
}

// ----------------------
// PISTON CONTROLS
// ----------------------

void Assembly::matchhloader_piston_control() {
    if (btnA_new_press(Controller.ButtonA.pressing())) {
        matchhloader_piston.toggle();
    }
}

void Assembly::doinker_piston_control() {
    if (btnB_new_press(Controller.ButtonB.pressing())) {
        doinker_piston.toggle();
    }
}

void Assembly::flap_control() {
    if (btnUp_new_press(Controller.ButtonUp.pressing())) {
        flap.toggle();
    }
}

void Assembly::lift_piston_left_control() {
    // Add logic if needed
}

void Assembly::lift_piston_right_control() {
    // Add logic if needed
}

void Assembly::lift_toggle() {
    lift_piston_left.toggle();
    lift_piston_right.toggle();
}

void Assembly::lift_extend() {
    lift_piston_left.set(true);
    lift_piston_right.set(true);
}

void Assembly::lift_retract() {
    lift_piston_left.set(false);
    lift_piston_right.set(false);
}

// ----------------------
// MOTOR CONTROLS
// ----------------------

void Assembly::lever_motor_control() {
    if (Controller.ButtonUp.pressing()) {
        lever_motor.spin(fwd, 8, volt);
    } else {
        lever_motor.stop();
    }
}

void Assembly::intake_motor_control() {
    if (Controller.ButtonL1.pressing()) {
        intake_motor.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
        intake_motor.spin(fwd, -12, volt);
    } else {
        intake_motor.stop();
    }
}