#include "GHSChassis.h"

GHSChassis::GHSChassis(const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
                       const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
                       const int irpm)
    : leftMotors(ileftMotors), rightMotors(irightMotors),
      rpm(irpm)
{
    // controller = icontroller;
    leftMotors = ileftMotors;
    rightMotors = irightMotors;
    // inputAxisSpeed = iinputAxisSpeed;
    //  inputAxisDirection = iinputAxisDirection;
    typeOfScale = 0;
}

GHSChassis::GHSChassis(const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
                       const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
                       const int irpm, const double ipolyParams)
    : leftMotors(ileftMotors), rightMotors(irightMotors),
      rpm(irpm), polyParams(ipolyParams)
{
    // controller = icontroller;
    leftMotors = ileftMotors;
    rightMotors = irightMotors;
    // inputAxisSpeed = iinputAxisSpeed;
    //  inputAxisDirection = iinputAxisDirection;
    typeOfScale = 1;
}

void GHSChassis::runDrivetrain(bool debug)
{
    scaleInputs(debug);
    motorScale(debug);
    setDrivetrains(debug);
}
void GHSChassis::scaleInputs(bool debug)
{
    switch (typeOfScale)
    {
    case 0:
        scaledInputs = inputs;

    case 1:
        scalePolys();
    }
    if (debug)
    {
        std::cout << "scaled inputs: " << scaledInputs[0] << ", " << scaledInputs[1] << std::endl;
    }
}

void GHSChassis::scalePolys()
{
    for (int i = 0; i < inputs.size(); i++)
    {
        if (inputs[i] >= 0)
            scaledInputs[i] = scalePoly(inputs[i]);
        else
            scaledInputs[i] = -scalePoly(-inputs[i]);
    }
}
double GHSChassis::scalePoly(double input)
{
    return (100 / pow(100, polyParams)) * pow(input, polyParams);
}
void GHSChassis::motorScale(bool debug)
{
    motorScaled[0] = ((scaledInputs[0] / 2) + (scaledInputs[1] / 2)) * rpm / 100;
    motorScaled[1] = ((scaledInputs[0] / 2) - (scaledInputs[1] / 2)) * rpm / 100;
    if (debug)
    {
        std::cout << "motor scaled: " << motorScaled[0] << ", " << motorScaled[1] << std::endl;
    }
}

void GHSChassis::setDrivetrains(bool debug)
{
    leftMotors->move_velocity(motorScaled[0]);
    rightMotors->move_velocity(motorScaled[1]);
    if (debug)
    {
        std::cout << "leftmotor_vel" << std::to_string(leftMotors->get_actual_velocity());
        std::cout << "rightmotor_vel" << std::to_string(rightMotors->get_actual_velocity());
    }
}