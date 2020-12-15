//
// Created by Decision on 2020/11/1.
//

#include <Queue.h>
#include <iostream>

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

PCB *Queue::deleteItem(std::string _pid) {
    PCB *p = _front, *q;
    while ( p -> getNextProcess() != nullptr && p -> getNextProcess() -> getPID() != _pid) {
        p = p -> getNextProcess();
    }
    if (p -> getNextProcess() == nullptr) return nullptr;
    q = p -> getNextProcess();
    p -> setNextProcess(q ->  getNextProcess());
    q -> setNextProcess(nullptr);
    return q;
}

PCB* Queue::searchItem(int _id, int _num) {
    PCB *p = _front -> getNextProcess(), *q = _front;
    while (p != nullptr) {
        if (p -> getResourceNum(_id) <= _num) break;
        q = p;
        p = p -> getNextProcess();
    }
    if (p == nullptr) return nullptr;
    q -> setNextProcess(p -> getNextProcess());
    p -> setNextProcess(nullptr);
    return p;
}

void Queue::listQueue() {
    PCB *p = _front -> getNextProcess();
    if (p != nullptr) std::cout<<p -> getPID();
    if (p == nullptr) {
        std::cout<<std::endl;
        return ;
    }
    p = p -> getNextProcess();
    while (p != nullptr) {
        std::cout<<"-"<<p -> getPID();
        p = p -> getNextProcess();
    }
    std::cout<<std::endl;
}