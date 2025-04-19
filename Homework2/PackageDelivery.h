#ifndef PACKAGEDELIVERY_H
#define PACKAGEDELIVERY_H

#include <string>
#include "DroneHeap.h"
#include "PackageHeap.h"
#include "Drone.h"
#include "Package.h"

class PackageDelivery 
{
private:
    DroneHeap droneHeap;      // Minheap for available drones
    PackageHeap packageHeap;  // Maxheap for packages sorted by priority
    DroneHeap cooldownHeap;   // Heap for drones in cooldown

    void processCooldown(int tick); // Handles cooldown updates
    void executeTask(Drone& drone, Package& package, int tick);  // Assigns tasks based on priority

public:
    PackageDelivery(const std::string droneFile, const std::string packageFile);
    void simulation(); // Runs the simulation
};

#endif // PACKAGEDELIVERY_H
