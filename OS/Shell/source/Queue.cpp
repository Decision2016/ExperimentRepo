//
// Created by Decision on 2020/11/1.
//

#include <Queue.h>

Queue::Queue() {
    Process *nullProcess = new Process();
    _front = nullProcess;
}

void Queue::insert(Process *_process) {
    Process *p = _front;
    while (p->getNextProcess() != nullptr) {
        p = p->getNextProcess();
    }
    p -> setNextProcess(_process);
}

void Queue::pop() {
    Process *p;
    p = _front -> getNextProcess();
    if (p == nullptr) return ;
    _front -> setNextProcess(p -> getNextProcess());
    delete p;
}

Process* Queue::front() {
    Process *p;
    p = _front -> getNextProcess();
    return p;
}

Queue::~Queue() {
    Process *p = _front, *q;
    while (p->getNextProcess() != nullptr) {
        q = p;
        p = p -> getNextProcess();
        delete q;
    }
    delete p;
}