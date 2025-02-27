#include "GHSChassis.h" //problem> not being included. all variable declarations here are redeclarations.
#include <iostream>

class GHSChassis
{
public:
    GHSChassis::GHSChassis(const int itypeOfScale) : typeOfScale(itypeOfScale)
    {
    }
    // Velocities(double inputx, double inputy)
    int typeOfScale;
    double linear_vel;  // final
    double angular_vel; // final
    int inputx;
    int inputy;
    std::pair<int, int> scale(std::vector<double> parameters)
    {
        switch (typeOfScale)
        {
        case 0:
            return std::make_pair(0, 0);
            break;
        }
    }
    std::pair<int, int> motors()
    {
        return std::make_pair(linear_vel + angular_vel, linear_vel - angular_vel);
    }
};
