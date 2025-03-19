#pragma once
// #include "eigen-3.4.0/Eigen/Dense"
#include "api.h"
#include <iostream>
#include <memory>

class GHSChassis
{
public:
    GHSChassis(const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
               const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
               const int irpm);
    // Velocities(double inputx, double inputy)
    std::shared_ptr<pros::MotorGroup> leftMotors;
    std::shared_ptr<pros::MotorGroup> rightMotors;
    int rpm;

    int typeOfScale;
    std::vector<int> exp_params;
    std::vector<int> poly_params;

    std::array<double, 2> inputs;       // speed, direction from controllers
    std::array<double, 2> scaledInputs; // scaled inputs
    std::array<double, 2> motorScaled;

    void runDrivetrain();

    void scaleInputs();
    void motorScale();
    void setDrivetrains();
};
