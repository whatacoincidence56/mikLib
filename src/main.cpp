#include "vex.h"


using namespace vex;
using namespace mik;

task UI;

static int run_UI() {
    UI_init();
    UI_controller_auton_selector();
    UI_render();
    return 0;
}

void pre_auton() {
    assembly.matchhloader_piston.set(false);
    assembly.doinker_piston.set(false);
    init();
    default_constants();
    UI = task(run_UI);
}

void auton(void) {
    UI.stop();
    auton_scr->start_auton();
}

void user_control(void) {
    while (calibrating) { task::sleep(50); }

    // How you want your drivetrain to stop during driver
    chassis.set_brake_type(brakeType::coast);
    
    assembly.init();

    while (true) {
        if (!control_disabled()) {
            // Add your user control code here
            chassis.control(drive_mode::SPLIT_ARCADE_CURVED);
            assembly.control();
        }
        task::sleep(5);
    }
}
const float wheel_diameter_inch = 3.25; // Diameter of the wheels used
const float drivetrain_gear_ratio = 36.0 / 48.0; // Gear ratio of the drivetrain (output speed / input speed)

bool in_motion = true;

void drive_motor_encoders(float inches_to_travel, float voltage) {
    chassis.left_drive.spin(fwd, voltage, volt);

    chassis.right_drive.spin(fwd, voltage, volt);
     while (in_motion) {
     float drivetrain_position = (chassis.left_drive.position(deg) + chassis.right_drive.position(deg)) / 2.0;
     float drivetrain_position_in_inches = (drivetrain_position * drivetrain_gear_ratio * 3.14 * wheel_diameter_inch) / 360.0;

     if (drivetrain_position_in_inches >= inches_to_travel) {
        in_motion = false;
        chassis.left_drive.stop(hold);
        chassis.right_drive.stop(hold);
      }
   }  
}


int main() {
    Competition.autonomous(auton);
    Competition.drivercontrol(user_control);

    pre_auton();

    while (true) {
        task::sleep(100);
    }
}
