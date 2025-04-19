#include "PackageDelivery.h"
#include <string>

using namespace std;

int main()
{
    string droneFile = "drones.txt";  
    string packageFile = "packages.txt"; 

    PackageDelivery simulation(droneFile, packageFile);
    simulation.simulation();
    
    return 0;
}