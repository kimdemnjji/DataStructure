#pragma once
#include "Customer.h"
#include <cstdio> 
#include <cstdlib>
#define MAX_QUEUE_SIZE 100
inline void error(const char* str) {
	printf("%s", str); 
	exit(1);
}
class CustomerQueue {
protected:
    int front;               // front at
    int rear;                // rear at
    Customer data[MAX_QUEUE_SIZE];
    int currentSize;         // Track the current size of the queue

public:
    CustomerQueue() : front(0), rear(0), currentSize(0) {}

    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue(Customer val) {
        if (isFull()) {
            error("Error  : 포화상태입니다.");
        }
        else {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
            currentSize++;
        }
    }

    Customer dequeue() {
        if (isEmpty()) {
            error("Error  : 공백상태입니다.");
        }
        else {
            front = (front + 1) % MAX_QUEUE_SIZE;
            currentSize--;
            return data[front];
        }
    }

    Customer peek() {
        if (isEmpty()) {
            error("Error  : 공백상태입니다.");
        }
        else {
            return data[(front + 1) % MAX_QUEUE_SIZE];
        }
    }

    int size() {
        return currentSize;
    }
};

