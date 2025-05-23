#include "Odometry.h"

Odometry::Odometry(const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
                   const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
                   const double itrackLength,
                   const double iwheelRadius,
                   const double istartingOrient) : leftMotors(ileftMotors), rightMotors(irightMotors),
                                                   trackLength(itrackLength), wheelRadius(iwheelRadius),
                                                   startingOrient(istartingOrient)
{
    threeSensors = false;
    leftMotors->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
    rightMotors->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
}

Odometry::Odometry(const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
                   const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
                   const std::shared_ptr<pros::v5::Rotation> irotational,
                   const double itrackLength,
                   const double iwheelRadius, const double irotationRadius,
                   const double istartingOrient) : leftMotors(ileftMotors), rightMotors(irightMotors),
                                                   rotational(irotational), trackLength(itrackLength),
                                                   wheelRadius(iwheelRadius), rotationRadius(irotationRadius),
                                                   startingOrient(istartingOrient)
{
    threeSensors = true;
    leftMotors->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
    rightMotors->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
}

void Odometry::runOdometry(bool debug)
{
    if (debug)
    {
        deltaLRS(true);
        // getThetaRadius(true);
        // getLocalcoords(true);
    }
    else
    {
        deltaLRS(false);
        // getThetaRadius(false);
        // getLocalcoords(false);
    }
}
void Odometry::deltaLRS(bool debug)
{
    std::vector<double> leftMotorEncoders = leftMotors->get_position_all();
    std::vector<double> rightMotorEncoders = rightMotors->get_position_all();
    double total_left_encoder_avg, total_right_encoder_avg;
    double left_encoder_avg, right_encoder_avg;

    // for (int i = 0; i < leftMotorEncoders.size(); i++)
    //{
    //      if (debug)
    //          std::cout << "left motor encoder: " << leftMotorEncoders[i] - prevLeftMotorEncoders[i] << std::endl;
    //      left_encoder_avg += leftMotorEncoders[i] - prevLeftMotorEncoders[i];
    //      // total_left_encoder_avg += leftMotorEncoders[i];
    //}
    // for (auto i : rightMotorEncoders)
    // {
    //     if (debug)
    //         std::cout << "right motor encoder: " << rightMotorEncoders[i] - prevRightMotorEncoders[i] << std::endl;
    //     right_encoder_avg += rightMotorEncoders[i] - prevRightMotorEncoders[i];
    //     // total_right_encoder_avg += rightMotorEncoders[i];
    // }

    // prevLeftMotorEncoders = leftMotorEncoders;
    // prevRightMotorEncoders = rightMotorEncoders;

    // left_encoder_avg /= leftMotorEncoders.size();
    // right_encoder_avg /= rightMotorEncoders.size();
    // total_left_encoder_avg /= leftMotorEncoders.size();
    // total_right_encoder_avg /= rightMotorEncoders.size();

    // if (debug)
    // {
    //     std::cout << "left motor encoder change avg, degrees supposedly: " << left_encoder_avg << std::endl;
    //     std::cout << "right motor encoder change avg, degrees supposedly: " << right_encoder_avg << std::endl;
    // }

    // deltaL = left_encoder_avg / 360. * (wheelRadius * 2.0 * M_PI);
    // deltaR = right_encoder_avg / 360. * (wheelRadius * 2.0 * M_PI);
    // totalL = total_left_encoder_avg / 360. * (wheelRadius * 2.0 * M_PI);
    // totalR = total_right_encoder_avg / 360. * (wheelRadius * 2.0 * M_PI);

    // if (debug)
    // {
    //     std::cout << "left dist change:" << deltaL << std::endl;
    //     std::cout << "right dist change:" << deltaR << std::endl;
    //     std::cout << "left dist tot:" << totalL << std::endl;
    //     std::cout << "right dist tot:" << totalR << std::endl;
    // }

    // if (threeSensors)
    // {
    //     int S = rotational->get_position(); // centidegrees
    //     deltaS = S - prevS;
    //     prevS = S;

    //     deltaS = deltaS / 36000. * (wheelRadius * 2.0 * M_PI);
    // }

    return;
}
