#pragma once

#include "vex.h"

using namespace vex;



class Assembly {
public:
    Assembly(
        mik::motor lower_middle_intake_motor,
        mik::motor upper_intake_motor, 
        mik::piston matchhloader_piston,
        mik::piston doinker_piston,
    );
    
    void init();
    void control();

    void lower_middle_intake_motor_control();
    void upper_intake_motor_control();
    void matchhloader_piston_control();
    void doinker_piston_control();

    
    mik::motor lower_middle_intake_motor;
    mik::motor upper_intake_motor;
    mik::piston matchhloader_piston;
    mik::piston doinker_piston;
};