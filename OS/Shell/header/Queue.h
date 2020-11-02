//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_QUEUE_H
#define SHELL_QUEUE_H


#include "PCB.h"

class Queue {
private:
    PCB*_front;

public:
    void insert(PCB *_process);
    PCB *front();
    bool deleteItem(std::string _pid);
    void pop();

    Queue();
    ~Queue();
};


#endif //SHELL_QUEUE_H
