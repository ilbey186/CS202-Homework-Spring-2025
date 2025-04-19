#include "Drone.h"

Drone::Drone() : id(0), batteryLife(0.0), speed(0.0), cooldownTicks(0), x(0.0), y(0.0) {}

Drone::Drone(int id, double batteryLife, double speed, double x, double y)
    : id(id), batteryLife(batteryLife), speed(speed), cooldownTicks(0), x(x), y(y) {}

bool Drone::compare(const Drone& d1, const Drone& d2) 
{
    if (d1.batteryLife == d2.batteryLife) 
    {
        return d1.id < d2.id; // Lower ID gets priority if battery is the same
    }
    return d1.batteryLife > d2.batteryLife;
}

void Drone::resetBattery() 
{
    batteryLife = 300.0; // Reset to full battery after cooldown
}
