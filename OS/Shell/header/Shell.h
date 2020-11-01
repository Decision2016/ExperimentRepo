//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H

#include <string>
#include <Queue.h>
#include <Process.h>

class Shell {
private:
    Queue *readySystemQueue, *readyUserQueue, *readyInitQueue;
    Queue *blockQueue[4];
    Process *runningProcess;
    int countResource[4] = {1, 2, 3, 4};

    void processCreate(const std::string &_pid, Priorities _priority);
    void processDelete(std::string _pid);
    void requireSource(std::string _name, int _count);
    void releaseSource(std::string _name);
    void listReadyProcess();
    void listBlockProcess();
    void listResource();
    void timeout();
    void scheduler();

    void readyQueueInsert(Process *_process, Priorities _priority);
    int getResourceId(const std::string &_name);
    Process* getPriorityProcess();

    void CommandRender(std::string command, int length, std::string _args[]);

    static Priorities getPriority(const std::string &_pri);
    static void printError(std::string errMsg);
public:
    void CommandAnalyze(std::string command_line);
    Shell();
    ~Shell();
};


#endif //SHELL_SHELL_H
