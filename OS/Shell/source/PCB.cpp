//
// Created by Decision on 2020/11/1.
//

#include <PCB.h>

PCB::PCB() {
    type = Type::BLOCK;
    priority = Priorities::INITIAL;
}

PCB::PCB(const std::string &_pid, Priorities _priority) {
    PID = std::string(_pid);
    type = Type::READY;
    priority = _priority;
}

std::string PCB::getPID() {
    return std::string(PID);
}

void PCB::setStatus(Type _type) {
    type = _type;
}

void PCB::setNextProcess(PCB *pcb) {
    nextProcess = pcb;
}

int PCB::getPriorityId() {
    return priority;
}

PCB* PCB::getNextProcess() {
    return nextProcess;
}

void PCB::requireResource(int _id, int num) {
    required[_id] += num;
}

void PCB::getResource(int _id, int num) {
    required[_id] -= num;
    resource[_id] += num;
}

void PCB::releaseResource(int _id) {
    resource[_id] = 0;
}

int PCB::getResourceNum(int _id) {
    return resource[_id];
}

int PCB::getRequireResource(int _id) {
    return required[_id];
}
