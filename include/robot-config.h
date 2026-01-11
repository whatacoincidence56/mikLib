#include "vex.h"

#pragma once

class motor;
class motor_group;
class Assembly;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::competition Competition;

extern bool calibrating;
extern bool force_calibrate_inertial;

extern Assembly assembly;



void init(void);
void calibrate_inertial(void);
void disable_user_control(bool stop_all_motors_ = true);


void enable_user_control(void);
bool control_disabled(void);


