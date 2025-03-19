#include "GHSChassis.h" //problem> not being included. all variable declarations here are redeclarations.

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
void GHSChassis::runDrivetrain()
{
    scaleInputs();
    motorScale();
    setDrivetrains();
}
void GHSChassis::scaleInputs()
{
    switch (typeOfScale)
    {
    case 0:
        scaledInputs = inputs;
    }
}
void GHSChassis::motorScale()
{
    motorScaled[0] = (scaledInputs[0] / 2) + (scaledInputs[1] / 2) * rpm / 100;
    motorScaled[1] = (scaledInputs[0] / 2) - (scaledInputs[1] / 2) * rpm / 100;
}

void GHSChassis::setDrivetrains()
{
    leftMotors->move_velocity(motorScaled[0]);
    rightMotors->move_velocity(motorScaled[1]);
}