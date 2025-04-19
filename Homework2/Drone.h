#ifndef DRONE_H
#define DRONE_H

#include "Package.h"

#include <iostream>

class Drone 
{
public:
    int id;
    double batteryLife;
    double speed;
    Package failedPackage;
    int cooldownTicks; // Number of ticks before the drone becomes available again
    double x, y;  // Drone's current location

    Drone(); 
    Drone(int id, double batteryLife, double speed, double x = 0.0, double y = 0.0);

    // Custom comparator for heap 
    static bool compare(const Drone& d1, const Drone& d2);

    void resetBattery();  // Resets battery to full after cooldown
};

#endif
