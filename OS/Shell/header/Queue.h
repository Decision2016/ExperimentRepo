//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_QUEUE_H
#define SHELL_QUEUE_H


#include "Process.h"

class Queue {
private:
    Process *_front;

public:
    void insert(Process *_process);
    Process *front();
    bool deleteItem(std::string _pid);
    void pop();

    Queue();
    ~Queue();
};


#endif //SHELL_QUEUE_H
