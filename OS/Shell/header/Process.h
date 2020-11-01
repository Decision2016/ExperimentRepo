//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_PROCESS_H
#define SHELL_PROCESS_H


#include "PCB.h"

class Process {
private:
    PCB* pcb;

public:
    void linkPcb(PCB *_pcb) {
        pcb = _pcb;
    }
};


#endif //SHELL_PROCESS_H
