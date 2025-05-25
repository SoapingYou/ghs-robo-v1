#pragma once
// #include "eigen-3.4.0/Eigen/Dense"
#include "api.h"
#include <iostream>
#include <memory>
#include <math.h>

class GHSChassis
{
public:
    GHSChassis(const std::shared_ptr<pros::Controller> icontroller,
               const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
               const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
               const int irpm);

    GHSChassis(const std::shared_ptr<pros::Controller> icontroller,
               const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
               const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
               const int irpm, const double ipolyParams);
    // Velocities(double inputx, double inputy)
    std::shared_ptr<pros::Controller> controller;
    std::shared_ptr<pros::MotorGroup> leftMotors;
    std::shared_ptr<pros::MotorGroup> rightMotors;
    int rpm;

    int typeOfScale;
    double polyParams;            // 1.0 - 5.0 recommended.
    std::array<double, 2> inputs; // speed, direction from controllers

    void runDrivetrain(bool debug);

private:
    std::array<double, 2> scaledInputs; // scaled inputs

    std::array<double, 2> motorScaled;
    void getInputs(bool debug);
    void scaleInputs(bool debug);
    void motorScale(bool debug);
    void scalePolys();
    double scalePoly(double input);
    void setDrivetrains(bool debug);
};
