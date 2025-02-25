#include "main.h"

class Velocities
{
public:
    // Velocities(double inputx, double inputy)
    double linear_vel;  // final
    double angular_vel; // final
    int inputx;
    int inputy;
    void solve_velocities(int a, int b); // change the lin/angular
};
