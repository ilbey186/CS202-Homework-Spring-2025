#include "PackageDelivery.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>



#define MAX_PACKAGE_WEIGHT 10.0
#define WEIGHT_FACTOR 0.2
#define BATTERY_FACTOR 0.3
#define COOLDOWN_PERIOD 5
#define MAX_BATTERY 300.0

PackageDelivery::PackageDelivery(const std::string droneFile, const std::string packageFile) 
{
    std::ifstream droneInput(droneFile);
    std::ifstream packageInput(packageFile);

    int numDrones, numPackages;
    droneInput >> numDrones;
    packageInput >> numPackages;

    // Read drones from file and insert into droneHeap
    for (int i = 0; i < numDrones; i++) 
    {
        int id, battery;
        double speed;
        droneInput >> id >> battery >> speed;
        Drone drone(id, battery, speed);
        droneHeap.insert(drone);
    }

    // Read packages from file and insert into packageHeap
    for (int i = 0; i < numPackages; i++) 
    {
        int id, priority;
        double x, y, weight;
        packageInput >> id >> x >> y >> weight >> priority;
        Package package(id, x, y, weight, priority);

        // Pass best available drone for sorting
        if (!droneHeap.isEmpty()) 
        {
            packageHeap.insert(package, droneHeap.peek());
        }
        else 
        {
            packageHeap.insert(package, Drone(0, MAX_BATTERY, 1.0)); // Fallback drone
        }
    }

    droneInput.close();
    packageInput.close();
}

void PackageDelivery::processCooldown(int tick) 
{
    DroneHeap tempHeap;
    while (!cooldownHeap.isEmpty()) 
    {
        Drone drone = cooldownHeap.extract();

        if (drone.cooldownTicks <= tick) 
        {
            drone.resetBattery();

            //now reinsert the failed package into the heap
            if (drone.failedPackage.id != -1) 
            {
                packageHeap.insert(drone.failedPackage, droneHeap.peek());
                drone.failedPackage = Package(); // Clear failed package
            }

            droneHeap.insert(drone);
        } 
        else 
        {
            tempHeap.insert(drone);
        }
    }
    cooldownHeap.swap(tempHeap);
}

void PackageDelivery::simulation() 
{
    int tick = 0;

    while (!packageHeap.isEmpty() || !cooldownHeap.isEmpty()) 
    {
        processCooldown(tick);

        bool taskAssigned = false;

        // Retry failed deliveries first
        if (!cooldownHeap.isEmpty() && !taskAssigned) 
        {
            Drone drone = cooldownHeap.extract();
            if (drone.cooldownTicks == tick) 
            {
                packageHeap.rebuildHeap(drone); // Rebuild package heap based on drone position
                Package package = packageHeap.extract(drone);
                executeTask(drone, package, tick);
                taskAssigned = true;
            } 
            else 
            {
                cooldownHeap.insert(drone);
            }
        }

        // Assign new packages if no failed retry happened
        if (!taskAssigned && !droneHeap.isEmpty() && !packageHeap.isEmpty()) 
        {
            Drone drone = droneHeap.extract();
            packageHeap.rebuildHeap(drone); // Ensure correct sorting
            Package package = packageHeap.extract(drone);
            executeTask(drone, package, tick);
            taskAssigned = true;
        }

        tick++;
    }
}

void PackageDelivery::executeTask(Drone& drone, Package& package, int tick) 
{
    //Calculate Distance from Drone's Current Location to Package Destination
    double dx = package.x - drone.x;
    double dy = package.y - drone.y;
    
    double distance = sqrt(dx * dx + dy * dy);
    distance = std::floor(distance * 10.0) / 10.0;
    if (distance < 0.1) distance = 0.1; 

    // Calculate Effective Speed
    double weightFactor = 1 - (WEIGHT_FACTOR * (package.weight / MAX_PACKAGE_WEIGHT));
    double batteryFactor = 1 - (BATTERY_FACTOR * (1 - (drone.batteryLife / MAX_BATTERY)));
    double effectiveSpeed = drone.speed * weightFactor * batteryFactor;
    effectiveSpeed = std::floor(effectiveSpeed * 10.0) / 10.0;
    if (effectiveSpeed <= 0.1) effectiveSpeed = 0.1;

    //Calculate Time Required
    double timeRequired = distance / effectiveSpeed;
    timeRequired = std::floor(timeRequired * 10.0) / 10.0;

    // Check if Drone Can Deliver
    if (timeRequired > drone.batteryLife) 
    {
        std::cout << "Drone " << drone.id << " Package " << package.id 
                  << " at tick " << tick << " cool down\n";

        drone.cooldownTicks = tick + COOLDOWN_PERIOD;
        drone.x = 0; // Reset drone position to hub
        drone.y = 0;
        drone.batteryLife = MAX_BATTERY;

        //Store the package inside the drone (not in the package heap)
        drone.failedPackage = package;

        cooldownHeap.insert(drone);
    } 
    else 
    {
        // Deduct Battery After Delivery
        drone.batteryLife -= timeRequired; 
        //Update Drone's Position to Package Destination
        drone.x = package.x;
        drone.y = package.y;

        std::cout << "Drone " << drone.id << " Package " << package.id 
                  << " at tick " << tick 
                  << " (delivery time: " << timeRequired << ", battery life: " 
                  << drone.batteryLife << ")\n";

        droneHeap.insert(drone);
    }
}
