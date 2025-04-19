#ifndef DRONEHEAP_H
#define DRONEHEAP_H

#include "Drone.h"

const int MAX_HEAP_SIZE = 100;

class DroneHeap 
{
private:
    Drone heap[MAX_HEAP_SIZE];
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    DroneHeap(); // Constructor
    DroneHeap(const DroneHeap& other); // Copy Constructor
    DroneHeap& operator=(const DroneHeap& other); // Assignment Operator
    void swap(DroneHeap& other); // Swap function

    bool insert(const Drone& drone);
    Drone extract();
    Drone peek() const;
    bool isEmpty() const;
    int getSize() const;
};

#endif // DRONEHEAP_H