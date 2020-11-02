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
    PCB *deleteItem(std::string _pid);

    // return and delete the first process which require <= resourceCount
    // in queue
    PCB *searchItem(int _id, int _num);

    void listQueue();
    void pop();

    Queue();
    ~Queue();
};


#endif //SHELL_QUEUE_H
