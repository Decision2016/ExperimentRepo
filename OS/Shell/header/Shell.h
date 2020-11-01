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
    Queue *blockQueue;
    Process *runningProcess;
    int countResource[4] = {1, 2, 3, 4};
public:
    void CommandAnalyze(std::string command_line);
    void CommandRender(std::string command, int length, std::string ...);
};


#endif //SHELL_SHELL_H
