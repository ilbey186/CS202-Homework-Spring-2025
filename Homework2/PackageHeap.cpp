#include "PackageHeap.h"
#include <cmath>
#include "Drone.h"

#define MAX_PACKAGE_WEIGHT 10.0
#define WEIGHT_FACTOR 0.2
#define BATTERY_FACTOR 0.3
#define COOLDOWN_PERIOD 5
#define MAX_BATTERY 300.0

PackageHeap::PackageHeap() : size(0) {}

bool PackageHeap::insert(const Package& package, const Drone& drone) 
{
    if (size >= MAX_PACKAGE_HEAP_SIZE) return false;
    heap[size] = package;
    heapifyUp(size, drone); // Use drone to determine completion time
    size++;
    return true;
}

Package PackageHeap::extract(const Drone& drone) 
{
    if (size == 0) return Package();
    Package topPackage = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0, drone); //Use drone to determine completion time
    return topPackage;
}

Package PackageHeap::peek() const 
{
    return size > 0 ? heap[0] : Package();
}

bool PackageHeap::isEmpty() const 
{
    return size == 0;
}

int PackageHeap::getSize() const 
{
    return size;
}

// Calculate Estimated Completion Time
double PackageHeap::calculateCompletionTime(const Package& package, const Drone& drone) 
{
    double dx = package.x - drone.x;
    double dy = package.y - drone.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    distance = std::floor(distance * 10.0) / 10.0;
    if (distance < 0.1) distance = 0.1;

    double weightFactor = 1 - (WEIGHT_FACTOR * (package.weight / MAX_PACKAGE_WEIGHT));
    double batteryFactor = 1 - (BATTERY_FACTOR * (1 - (drone.batteryLife / MAX_BATTERY)));
    double effectiveSpeed = drone.speed * weightFactor * batteryFactor;
    effectiveSpeed = std::floor(effectiveSpeed * 10.0) / 10.0;
    if (effectiveSpeed <= 0.1) effectiveSpeed = 0.1;

    double timeRequired = distance / effectiveSpeed;
    return std::floor(timeRequired * 10.0) / 10.0;
}

void PackageHeap::heapifyUp(int index, const Drone& drone) 
{
    while (index > 0) 
    {
        int parent = (index - 1) / 2;

        double timeIndex = calculateCompletionTime(heap[index], drone);
        double timeParent = calculateCompletionTime(heap[parent], drone);

        if (heap[index].priority > heap[parent].priority || (heap[index].priority == heap[parent].priority && timeIndex < timeParent) || (heap[index].priority == heap[parent].priority && timeIndex == timeParent && heap[index].id < heap[parent].id)) 
        {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } 
        else 
        {
            break;
        }
    }
}

void PackageHeap::heapifyDown(int index, const Drone& drone) 
{
    while (true) 
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int best = index;

        double timeCurrent = calculateCompletionTime(heap[index], drone);
        double timeLeft = leftChild < size ? calculateCompletionTime(heap[leftChild], drone) : 1e9;
        double timeRight = rightChild < size ? calculateCompletionTime(heap[rightChild], drone) : 1e9;

        if (leftChild < size && (heap[leftChild].priority > heap[best].priority || (heap[leftChild].priority == heap[best].priority && timeLeft < timeCurrent) || (heap[leftChild].priority == heap[best].priority && timeLeft == timeCurrent && heap[leftChild].id < heap[best].id)))
        {
            best = leftChild;
        }

        if (rightChild < size && (heap[rightChild].priority > heap[best].priority || (heap[rightChild].priority == heap[best].priority && timeRight < timeLeft) || (heap[rightChild].priority == heap[best].priority && timeRight == timeLeft && heap[rightChild].id < heap[best].id)))
        {
            best = rightChild;
        }

        if (best != index) 
        {
            std::swap(heap[index], heap[best]);
            index = best;
        } 
        else 
        {
            break;
        }
    }
}

void PackageHeap::rebuildHeap(const Drone& drone) 
{
    for (int i = size / 2 - 1; i >= 0; i--) 
    {
        heapifyDown(i, drone); // Ensure sorting is updated
    }
}