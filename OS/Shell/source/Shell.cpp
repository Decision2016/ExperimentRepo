//
// Created by Decision on 2020/11/1.
//

#include <Shell.h>
#include <Utils.h>

Shell::Shell() {
    for (auto &item : readyQueue) item = new Queue();

    for (auto &item : blockQueue) item = new Queue();

    runningProcess = nullptr;
}

Shell::~Shell() {
    for (auto &item : readyQueue) {
        delete item;
        item = nullptr;
    }

    for (auto &item : blockQueue) {
        delete item;
        item = nullptr;
    }

    delete runningProcess;
    runningProcess = nullptr;
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

void Shell::CommandRender(std::string command, int length, std::vector<std::string> _args) {
    if (command == CREATE) {
        // todo : printError
        processCreate(_args[0], getPriority(_args[1]));
    }
    else if (command == DELETE) {
        processDelete(_args[0]);
    }
    else if (command == REQUIRE) {
        int num = Utils::castString2Int(_args[1]);
        requireSource(_args[0], num);
    }
    else if (command == RELEASE) {
        releaseSource(_args[0]);
    }
    else if (command == TIMEOUT) {
        timeout();
    }
    else if (command == LIST) {
        if (_args[0] == LIST_BLOCK) listBlockProcess();
        else if (_args[0] == LIST_READY) listReadyProcess();
        else if (_args[0] == LIST_RES) listResource();
        else {
            // todo : print error
        }
    }
    else {
        // todo : print error
    }

}

void Shell::processCreate(const std::string &_pid, Priorities _priority) {
    auto *process = new PCB(_pid, _priority);
    readyQueueInsert(process, _priority);
    scheduler();
}

void Shell::releaseProcess(PCB *_process) {
    for(int i = 0; i < RESOURCE_NUM; i++) {
        if (_process -> getResourceNum(i) > 0) {
            countResource[i] += _process -> getResourceNum(i);
            _process -> releaseResource(i);
        }
    }
    delete _process;
}

void Shell::processDelete(std::string _pid) {
    if (runningProcess -> getPID() == _pid) {
        releaseProcess(runningProcess);
        runningProcess = nullptr;
        scheduler();
    }
    else {
        bool res;
        for (auto &item : readyQueue) {
            res = item ->deleteItem(_pid);
            if (res) return;;
        }

        for (auto & i : blockQueue) {
            res = i->deleteItem(_pid);
            if (res) return ;
        }
    }
}

int Shell::getResourceId(const std::string &_name) {
    if (_name == "R1") return 0;
    else if (_name == "R2") return 1;
    else if (_name == "R3") return 2;
    else if (_name == "R4") return 3;
    return -1;
}

void Shell::releaseSource(std::string _name) {
    int resourceId = getResourceId(_name);
    if (runningProcess -> getResourceNum(resourceId) == 0) {
        // todo:Print error
        return ;
    }
    countResource[resourceId] += runningProcess -> getResourceNum(resourceId);
    runningProcess -> releaseResource(resourceId);
}

void Shell::requireSource(std::string _name, int _count) {
    int resourceId = getResourceId(_name);
    if (countResource[resourceId] >= _count) {
        countResource[resourceId] -= _count;
        runningProcess->getResource(resourceId, _count);
    }
    else {
        runningProcess -> requireResource(resourceId, _count);
        runningProcess -> setStatus(Type::BLOCK);
        blockQueue[resourceId] -> insert(runningProcess);
        runningProcess = nullptr;
        scheduler();
    }
}

void Shell::timeout() {
    int idx = runningProcess -> getPriorityId();
    runningProcess -> setStatus(Type::READY);
    readyQueue[idx] -> insert(runningProcess);
    runningProcess = nullptr;
    scheduler();
}

void Shell::scheduler() {
    if (runningProcess != nullptr) return ;
    for (int i = READY_QUEUE_NUM - 1; i >= 0; i--) {
        if (readyQueue[i]->front() != nullptr) {
            PCB *p = readyQueue[i] -> front();
            readyQueue[i] -> pop();
            p -> setStatus(Type::RUNNING);
            runningProcess = p;
        }
    }
}

void Shell::listReadyProcess() {
    for (int i = 0; i < READY_QUEUE_NUM; i++) {
        printf("%d: ", i);
        readyQueue[i] -> listQueue();
        printf("\n");
    }
}

void Shell::listBlockProcess() {
    for (int i = 0; i < RESOURCE_NUM; i++) {
        printf("R%d: ", i);
        blockQueue[i] -> listQueue();
        printf("\n");
    }
}

void Shell::listResource() {
    for (int i = 0; i < RESOURCE_NUM; i++) {
        printf("R%d %d\n", i, countResource[i]);
    }
}

void Shell::readyQueueInsert(PCB *_process, Priorities _priority) {
    readyQueue[_priority] -> insert(_process);
}

int Shell::CommandAnalyze(std::string command_line) {
    std::stringstream command_input(command_line);
    std::string tmp, command;
    std::vector<std::string> v_string;
    int length = 0;
    while (command_input >> tmp) {
        if (length == 0) {
            command = tmp;
            length ++;
            continue;
        }
        v_string.push_back(tmp);
    }
    if (command == EXIT) return -1;
    CommandRender(command, length - 1, v_string);
    return 0;
}