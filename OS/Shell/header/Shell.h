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

    void processCreate(const std::string &_pid,
            Priorities _priority);                              // 进程块创建
    void processDelete(std::string _pid);                       // 进程块删除
    void requireSource(std::string _name, int _count);          // 资源申请调用
    void releaseSource(std::string _name);                      // 资源释放调用
    void listReadyProcess();                                    // 列表，显示就绪队列状态
    void listBlockProcess();
    void listResource();
    void timeout();                                             // 超时
    void scheduler();                                           // 任务调度函数

    void block2ready(int resId);
    void releaseProcess(PCB *_process);                         // 释放进程块
    void readyQueueInsert(PCB *_process, Priorities _priority); // 添加进程块到就绪队列
    bool checkReadyQueue();                                     // 检查就绪队列是否为空
    static int getResourceId(const std::string &_name);         // 静态函数，通过输入的字符串判断资源编号

    void CommandRender(std::string command, int length,
            std::vector<std::string> _args);                    // 命令执行函数

    static Priorities getPriority(const std::string &_pri);
    static void printError();
public:
    int CommandAnalyze(std::string command_line);               // 输入任务分析，Shell入口
    Shell();                                                    // 构造函数，用于创建队列
    ~Shell();
};


#endif //SHELL_SHELL_H
