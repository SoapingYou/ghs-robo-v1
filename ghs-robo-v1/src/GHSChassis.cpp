#include "GHSChassis.h"

GHSChassis::GHSChassis(const std::shared_ptr<pros::Controller> icontroller,
                       const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
                       const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
                       const int irpm)
    : controller(icontroller), leftMotors(ileftMotors), rightMotors(irightMotors),
      rpm(irpm)
{
    controller = icontroller;
    leftMotors = ileftMotors;
    rightMotors = irightMotors;
    // inputAxisSpeed = iinputAxisSpeed;
    //  inputAxisDirection = iinputAxisDirection;
    typeOfScale = 0;
}
GHSChassis::GHSChassis(const std::shared_ptr<pros::Controller> icontroller,
                       const std::shared_ptr<pros::v5::MotorGroup> ileftMotors,
                       const std::shared_ptr<pros::v5::MotorGroup> irightMotors,
                       const int irpm, const double ipolyParams)
    : controller(icontroller), leftMotors(ileftMotors), rightMotors(irightMotors),
      rpm(irpm), polyParams(ipolyParams)
{
    controller = icontroller;
    leftMotors = ileftMotors;
    rightMotors = irightMotors;
    // inputAxisSpeed = iinputAxisSpeed;
    //  inputAxisDirection = iinputAxisDirection;
    typeOfScale = 1;
}

void GHSChassis::runDrivetrain(bool debug)
{
    getInputs(debug);
    scaleInputs(debug);
    motorScale(debug);
    setDrivetrains(debug);
}
void GHSChassis::getInputs(bool debug)
{
    inputs[0] = controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);  // Gets amount forward/backward from left joystick, axis 4
    inputs[1] = controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // Gets the turn left/right from right joystick, axis 2
    if (debug)
    {
        std::cout << "inputs: " << inputs[0] << ", " << inputs[1] << std::endl;
    }
}
void GHSChassis::scaleInputs(bool debug)
{
    switch (typeOfScale)
    {
    case 0:
        scaledInputs[0] = inputs[0];
        scaledInputs[1] = inputs[1];
        break;

    case 1:
        scalePolys();
        break;
    }
    if (debug)
    {
        std::cout << "typeOfScale: " << typeOfScale << std::endl;
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
        std::cout << ";  rightmotor_vel" << std::to_string(rightMotors->get_actual_velocity());
        std::cout << std::endl;
    }
}