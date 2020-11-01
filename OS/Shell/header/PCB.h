//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_PCB_H
#define SHELL_PCB_H

#include <PCB.h>
#include <Resource.h>
#include <string>
#include <Process.h>
#include <LinkList.h>
#include <contants.h>

class PCB {
private:
    std::string PID;
    Resource *res;
    Process *parent;
    Type type;
    LinkList *children;
    Priorities priority;
};

#endif //SHELL_PCB_H
