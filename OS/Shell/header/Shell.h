//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H

#include <string>
#include <Queue.h>
#include <vector>
#include <sstream>
#include "Utils.h"

class Shell {
private:
    Queue *readyQueue[READY_QUEUE_NUM];
    Queue *blockQueue[RESOURCE_NUM];
    PCB *runningProcess;
    int countResource[RESOURCE_NUM] = {1, 2, 3, 4};

    void processCreate(const std::string &_pid, Priorities _priority);
    void processDelete(std::string _pid);
    void requireSource(std::string _name, int _count);
    void releaseSource(std::string _name);
    void listReadyProcess();
    void listBlockProcess();
    void listResource();
    void timeout();
    void scheduler();

    void releaseProcess(PCB *_process);
    void readyQueueInsert(PCB *_process, Priorities _priority);
    static int getResourceId(const std::string &_name);

    void CommandRender(std::string command, int length, std::vector<std::string> _args);

    static Priorities getPriority(const std::string &_pri);
    static void printError(std::string errMsg);
public:
    int CommandAnalyze(std::string command_line);
    Shell();
    ~Shell();
};


#endif //SHELL_SHELL_H
