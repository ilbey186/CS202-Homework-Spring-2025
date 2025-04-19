#ifndef PACKAGEHEAP_H
#define PACKAGEHEAP_H

#include "Package.h"
#include "Drone.h"

const int MAX_PACKAGE_HEAP_SIZE = 100;

class PackageHeap 
{
private:
    Package heap[MAX_PACKAGE_HEAP_SIZE];
    int size;

    void heapifyUp(int index, const Drone& drone);
    void heapifyDown(int index, const Drone& drone);
    double calculateCompletionTime(const Package& package, const Drone& drone);

public:
    PackageHeap();

    bool insert(const Package& package, const Drone& drone);
    Package extract(const Drone& drone);
    Package peek() const;
    bool isEmpty() const;
    int getSize() const;
    void rebuildHeap(const Drone& drone); //function to rebuild heap based on drone's position
};

#endif // PACKAGEHEAP_H
