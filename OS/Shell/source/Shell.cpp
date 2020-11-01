//
// Created by Decision on 2020/11/1.
//

#include <Shell.h>

Shell::Shell() {
    readyInitQueue = new Queue();
    readyUserQueue = new Queue();
    readySystemQueue = new Queue();

    for (int i = 0; i < RESOURCE_NUM; i++) {
        blockQueue[i] = new Queue();
    }

    runningProcess = nullptr;
}

Shell::~Shell() {
    delete readySystemQueue;
    delete readyUserQueue;
    delete readyInitQueue;

    for (int i = 0; i < RESOURCE_NUM; i++) {
        if (blockQueue[i] == nullptr) continue;
        delete blockQueue[i];
    }

    if (runningProcess != nullptr) {
        delete runningProcess;
        runningProcess = nullptr;
    }
}

Priorities Shell::getPriority(const std::string &_pri) {
    if (_pri == std::string("2")) {
        return Priorities::SYSTEM;
    }
    else if (_pri == std::string("1")) {
        return Priorities::USER;
    }
    else if (_pri == std::string("0")) {
        return Priorities::INITIAL;
    }
}

void Shell::CommandRender(std::string command, int length, std::string _args[]) {
    if (command == CREATE) {
        // todo : printError
        processCreate(_args[0], getPriority(_args[1]));
    }
    else if (command == DELETE) {
        processDelete(_args[0]);
    }
    else if (command == REQUIRE) {

    }
    else if (command == RELEASE) {

    }
    else if (command == TIMEOUT) {

    }
    else if (command == LIST) {

    }
    else {
        // todo : print error
    }

}

void Shell::processCreate(const std::string &_pid, Priorities _priority) {
    auto *process = new Process(_pid, _priority);
    if (runningProcess == nullptr) {
        runningProcess = process;
    }
    else {
        readyQueueInsert(process, _priority);
    }
}

void Shell::processDelete(std::string _pid) {
    if (runningProcess -> getPID() == _pid) {
        delete runningProcess;
        runningProcess = getPriorityProcess();
    }
    else {
        bool res = false;
        res = readySystemQueue->deleteItem(_pid);
        if (res) return ;

        res = readyUserQueue->deleteItem(_pid);
        if (res) return ;

        res = readyInitQueue->deleteItem(_pid);
        if (res) return ;

        for (int i = 0; i < RESOURCE_NUM; i++) {
            res = blockQueue[i]->deleteItem(_pid);
            if (res) return ;
        }
    }
}