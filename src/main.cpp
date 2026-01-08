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
const float drivetrain_gear_ratio = 36.0 / 60.0; // Gear ratio of the drivetrain (output speed / input speed)


void drive_motor_encoders(float inches_to_travel, float voltage) {
    chassis.left_drive(fwd, voltage, volt);
    chassis.right_drive(fwd, voltage, volt);
}

bool in_motion = true;
while (in_motion) {
    float drivetrain_position = (chassis.left_drive.position(deg) + chassis.right_drive.position(deg)) / 2.0;
    float drivetrain_position_in_inches = (drivetrain_position * drivetrain_gear_ratio * 3.14 * wheel_diameter_inch) / 360.0;

    if (drivetrain_position_in_inches >= inches_to_travel) {
        in_motion = false;
        chassis.left_drive.stop(hold);
        chassis.right_drive.stop(hold);
    }

    task::sleep(20);

    //these lines of code are purely for PID tuning purposes
    void drivetrain_movement_test() {
        lower_middle_intake_motor.spin(fwd, 12, volt);

        // Drive forward 18 inches at 6 volts is what this function call does (you can change the parameters as needed)
        //12 volts is also the max voltage you can give to the motors

        drive_motor_encoders(18, 12);
        
        chassis.drive_distance(18, {.max_voltage = 12});
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
