#include "Package.h"
#include <cmath>

// Default constructor
Package::Package() : id(-1), x(0), y(0), weight(0), priority(0) {}

Package::Package(int id, double x, double y, double weight, int priority)
    : id(id), x(x), y(y), weight(weight), priority(priority) {}

bool Package::compare(const Package& p1, const Package& p2) 
{
    if (p1.priority == p2.priority) 
    {
        return p1.id > p2.id; // Lower ID gets priority if priorities are equal
    }
    return p1.priority < p2.priority; // Higher priority comes first
}

double Package::getDistance() const 
{
    return sqrt(x * x + y * y); // distance from hub (0,0)
}

double Package::getDistance(int droneX, int droneY) const
{
    return sqrt((x - droneX) * (x - droneX) + (y - droneY) * (y - droneY));
}

