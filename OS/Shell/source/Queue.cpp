//
// Created by Decision on 2020/11/1.
//

#include <Queue.h>

Queue::Queue() {
    PCB *nullProcess = new PCB();
    _front = nullProcess;
}

void Queue::insert(PCB *_process) {
    PCB *p = _front;
    while (p->getNextProcess() != nullptr) {
        p = p->getNextProcess();
    }
    p -> setNextProcess(_process);
}

void Queue::pop() {
    PCB *p;
    p = _front -> getNextProcess();
    if (p == nullptr) return ;
    _front -> setNextProcess(p -> getNextProcess());
    delete p;
}

PCB* Queue::front() {
    PCB *p;
    p = _front -> getNextProcess();
    return p;
}

Queue::~Queue() {
    PCB *p = _front, *q;
    while (p->getNextProcess() != nullptr) {
        q = p;
        p = p -> getNextProcess();
        delete q;
    }
    delete p;
}