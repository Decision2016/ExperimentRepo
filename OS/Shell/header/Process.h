//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_PROCESS_H
#define SHELL_PROCESS_H

#include <string>
#include "contants.h"
#include "PCB.h"

class Process {
private:
    PCB *pcb;
    Process *_next;

public:
    Process();
    ~Process();
    Process(const std::string _pid, Priorities _priority);
    void setNextProcess(Process *_next);
    Process *getNextProcess();
    std::string getPID();
};


#endif //SHELL_PROCESS_H
