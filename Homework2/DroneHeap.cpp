#include "DroneHeap.h"

// Custom swap function template
template <typename T>
void swapItems(T &a, T &b) 
{
    T temp = a;
    a = b;
    b = temp;
}

DroneHeap::DroneHeap() : size(0) {}

// Copy Constructor
DroneHeap::DroneHeap(const DroneHeap& other) 
{
    size = other.size;
    for (int i = 0; i < size; i++) 
    {
        heap[i] = other.heap[i];
    }
}

// Assignment Operator
DroneHeap& DroneHeap::operator=(const DroneHeap& other) 
{
    if (this != &other) 
    { 
        size = other.size;
        for (int i = 0; i < size; i++) 
        {
            heap[i] = other.heap[i];
        }
    }
    return *this;
}

// Swap Function
void DroneHeap::swap(DroneHeap& other) 
{
    swapItems(size, other.size);
    for (int i = 0; i < (size > other.size ? size : other.size); i++) 
    {
        swapItems(heap[i], other.heap[i]);
    }
}

bool DroneHeap::insert(const Drone& drone) 
{
    if (size >= MAX_HEAP_SIZE) return false;
    heap[size] = drone;
    heapifyUp(size);
    size++;
    return true;
}

Drone DroneHeap::extract() 
{
    if (size == 0) return Drone();
    Drone topDrone = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return topDrone;
}

Drone DroneHeap::peek() const 
{
    return size > 0 ? heap[0] : Drone();
}

bool DroneHeap::isEmpty() const 
{
    return size == 0;
}

int DroneHeap::getSize() const 
{
    return size;
}

void DroneHeap::heapifyUp(int index) 
{
    while (index > 0) 
    {
        int parent = (index - 1) / 2;
        if (heap[index].batteryLife > heap[parent].batteryLife || (heap[index].batteryLife == heap[parent].batteryLife && heap[index].id < heap[parent].id)) 
        {
            swapItems(heap[index], heap[parent]);
            index = parent;
        } 
        else 
        {
            break;
        }
    }
}

void DroneHeap::heapifyDown(int index) 
{
    while (true) 
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < size && (heap[leftChild].batteryLife > heap[largest].batteryLife || (heap[leftChild].batteryLife == heap[largest].batteryLife && heap[leftChild].id < heap[largest].id))) 
        {
            largest = leftChild;
        }
        
        if (rightChild < size && (heap[rightChild].batteryLife > heap[largest].batteryLife || (heap[rightChild].batteryLife == heap[largest].batteryLife && heap[rightChild].id < heap[largest].id))) 
        {
            largest = rightChild;
        }

        if (largest != index) 
        {
            swapItems(heap[index], heap[largest]);
            index = largest;
        } 
        else 
        {
            break;
        }
    }
}
