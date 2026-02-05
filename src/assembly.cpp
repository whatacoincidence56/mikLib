#include "vex.h"

using namespace vex;

// Pass in the devices we want to use
Assembly::Assembly(
    mik::motor lower_middle_intake_motor,
    mik::motor upper_intake_motor, 
    mik::piston matchhloader_piston,
    mik::piston doinker_piston
    mik::piston flap
) :
    // Assign the ports to the devices
    lower_middle_intake_motor(lower_middle_intake_motor),
    upper_intake_motor(upper_intake_motor),
    matchhloader_piston(matchhloader_piston),
    doinker_piston(doinker_piston)
    flap(flap_piston)
{};

void Assembly::init() {
    // Any initialization code for the assembly can go here
}

// You want to put this function inside the user control loop in main.
void Assembly::control() {
    lower_middle_intake_motor_control();
    upper_intake_motor_control();
    matchhloader_piston_control();
    doinker_piston_control();
    flap_piston_control()
}


// // Spins lower_middle_intake forward if L1 is being held, reverse if L2 is being held; stops otherwise (You can swap the buttons as needed)
// void Assembly::lower_middle_intake_motor_control() {
//     if (Controller.ButtonL1.pressing()) {
//         lower_middle_intake_motor.spin(fwd, 12, volt);
//     } else if (Controller.ButtonL2.pressing()) {
//         lower_middle_intake_motor.spin(fwd, -12, volt);
//     } else {
//         lower_middle_intake_motor.stop();
//     }
//}
// Spins upper_intake forward if R1 is being held, reverse if R2 is being held; stops otherwise (You can swap the buttons as needed)
// void Assembly::upper_intake_motor_control() {
//     if (Controller.ButtonR1.pressing()) {
//         upper_intake_motor.spin(fwd, 12, volt);
//     } else if (Controller.ButtonR2.pressing()) {
//         upper_intake_motor.spin(fwd, -12, volt);
//     } else {
//         upper_intake_motor.stop();
//     }
// }

// Extends or retracts matchhloader_piston when button A is pressed, can only extend or retract again until button A is released and pressed again
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
void Assembly::flap_piston_control() {
    if (btnUp_new_press(Controller.ButtonUp.pressing())){
        flap_piston.toggle();
    }
}
