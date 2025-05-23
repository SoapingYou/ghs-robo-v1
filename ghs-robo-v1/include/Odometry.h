#pragma once
#include "api.h"
#include <iostream>
#include <memory>
#include <numeric>

class Odometry
{
public:
    Odometry(const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
             const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
             const double itrackLength,
             const double iwheelRadius, const double istartingOrient);
    Odometry(const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
             const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
             const std::shared_ptr<pros::v5::Rotation> irotational,
             const double itrackLength,
             const double iwheelRadius, const double irotationRadius,
             const double istartingOrient);

    std::shared_ptr<pros::v5::MotorGroup> leftMotors;
    std::shared_ptr<pros::v5::MotorGroup> rightMotors;
    std::shared_ptr<pros::v5::Rotation> rotational;
    double trackLength, wheelRadius, rotationRadius;
    bool threeSensors;
    double startingOrient;

    struct coords // if i get eigen to work :( ill do that
    {
        double x;
        double y;
    };

    coords absolute_coords;

    double deltaL, deltaR, deltaS, dif;
    double theta;
    double radius;
    coords local_coords;

    double prevL, prevR, prevS, prevTheta;
    double totalL = 0, totalR = 0;
    std::vector<double> prevLeftMotorEncoders, prevRightMotorEncoders;

    void runOdometry(bool debug);
    void deltaLRS(bool debug);
    void getThetaRadius(bool debug);
    void getLocalcoords(bool debug);
};