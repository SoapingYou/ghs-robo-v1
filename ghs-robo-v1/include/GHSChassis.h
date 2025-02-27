#pragma once
#include "eigen-3.4.0/Eigen/Dense"
#include <iostream>

class GHSChassis
{
public:
    GHSChassis(const int itypeOfScale);
    // Velocities(double inputx, double inputy)
    int typeOfScale;
    double linear_vel;  // final
    double angular_vel; // final
    int inputx;
    int inputy;
    void LinearScale(int a, int b);
    std::pair<int, int> scale(std::vector<double> parameters);
    std::pair<int, int> motors();
};
