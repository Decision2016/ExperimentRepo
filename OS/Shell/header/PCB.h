//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_PCB_H
#define SHELL_PCB_H

#include <PCB.h>
#include <string>
#include <Process.h>
#include <LinkList.h>
#include <contants.h>

class PCB {
private:
    std::string PID;
    int resource[RESOURCE_NUM] = {0, 0, 0, 0};
    int required[RESOURCE_NUM] = {0, 0, 0, 0};
    PCB *parent = nullptr, *nextProcess = nullptr;
    Type type;
    LinkList *children = nullptr;
    Priorities priority;

public:
    PCB();
    PCB(const std::string &_pid, Priorities _priority);
    std::string getPID();
    void setStatus(Type _type);
    void setNextProcess(PCB *pcb);
    int getPriorityId();
    PCB *getNextProcess();

    void requireResource(int _id, int num);
    void getResource(int _id, int num);
    void releaseResource(int _id);
    int getResourceNum(int _id);
};

#endif //SHELL_PCB_H
