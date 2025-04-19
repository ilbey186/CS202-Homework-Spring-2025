#ifndef PACKAGE_H
#define PACKAGE_H

class Package 
{
public:
    int id;
    double x, y; // Destination coordinates
    double weight;
    int priority;

    // Default constructor
    Package();

    // Parameterized constructor
    Package(int id, double x, double y, double weight, int priority);

    // Comparator for heap (prioritize higher priority, then lower ID
    static bool compare(const Package& p1, const Package& p2);

    // Calculates distance from the hub 0,0
    double getDistance() const;

    double getDistance(int droneX, int droneY) const;
};

#endif // PACKAGE_H
