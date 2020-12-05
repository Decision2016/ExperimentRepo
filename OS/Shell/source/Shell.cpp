//
// Created by Decision on 2020/11/1.
//

#include <Shell.h>
#include <Utils.h>
#include <iostream>

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
    else {
        return Priorities ::PRI_ERROR;
    }
}

void Shell::CommandRender(std::string command, int length, std::vector<std::string> _args) {
    if (command == CREATE) {
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
            printError();
        }
    }
    else if (command == INIT) {
        printf("init process is running\n");
    }
    else {
        printError();
    }

}

void Shell::processCreate(const std::string &_pid, Priorities _priority) {
    auto *process = new PCB(_pid, _priority);
    readyQueueInsert(process, _priority);
    scheduler();
    std::cout<<"process "<<runningProcess->getPID()<<" is running."<<std::endl;
}

void Shell::releaseProcess(PCB *_process) {
    for(int i = 0; i < RESOURCE_NUM; i++) {
        if (_process -> getResourceNum(i) > 0) {
            countResource[i] += _process -> getResourceNum(i);
            _process -> releaseResource(i);
            printf("release source R%d, wake up process ", i + 1);
            block2ready(i);
        }
    }
    printf("process %s was deleted.\n", _process->getPID().c_str());
    delete _process;
}

void Shell::processDelete(std::string _pid) {
    if (runningProcess -> getPID() == _pid) {
        releaseProcess(runningProcess);
        runningProcess = nullptr;
        scheduler();
    }
    else {
        PCB *res;
        for (auto &item : readyQueue) {
            res = item ->deleteItem(_pid);
            if (res != nullptr) {
                releaseProcess(res);
                break;
            }
        }
        for (auto & i : blockQueue) {
            res = i->deleteItem(_pid);
            if (res != nullptr) {
                releaseProcess(res);
                break;
            }
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

// running process release source
void Shell::releaseSource(std::string _name) {
    int resourceId = getResourceId(_name);
    if (runningProcess -> getResourceNum(resourceId) == 0) {
        printError();
        return ;
    }
    countResource[resourceId] += runningProcess -> getResourceNum(resourceId);
    runningProcess -> releaseResource(resourceId);
    printf("release source R%d, wake up process ", resourceId + 1);
    block2ready(resourceId);
}

void Shell::requireSource(std::string _name, int _count) {
    int resourceId = getResourceId(_name);
    if (countResource[resourceId] >= _count) {
        countResource[resourceId] -= _count;
        runningProcess->getResource(resourceId, _count);
        printf("process %s requests %d R%d.\n", runningProcess -> getPID() .c_str(), _count, resourceId + 1);
    }
    else {
        PCB *p = runningProcess;
        runningProcess -> requireResource(resourceId, _count);
        runningProcess -> setStatus(Type::BLOCK);
        blockQueue[resourceId] -> insert(runningProcess);
        runningProcess = nullptr;
        scheduler();
        printf("process %s is running. process %s is blocked.\n", runningProcess->getPID().c_str() ,p->getPID().c_str());
    }
}

void Shell::timeout() {
<<<<<<< HEAD
    if (checkReadyQueue()) {
        int idx = runningProcess -> getPriorityId();
        PCB *p = runningProcess;
        runningProcess -> setStatus(Type::READY);
        runningProcess -> setPriority();
        readyQueue[idx] -> insert(runningProcess);
        runningProcess = nullptr;
        scheduler();
        std::cout<<"process "<<runningProcess -> getPID()<<" is running. process "<<
                 p -> getPID()<<" is ready"<<std::endl;
    }
    else  std::cout<<"process "<<runningProcess -> getPID()<<" is running."<<std::endl;

=======
    int idx = runningProcess -> getPriorityId();
    PCB *p = runningProcess;
    runningProcess -> setStatus(Type::READY);
    readyQueue[idx] -> insert(runningProcess);
    runningProcess = nullptr;
    scheduler();
    std::cout<<"process "<<runningProcess -> getPID()<<" is running. process "<<
        p -> getPID()<<" is ready"<<std::endl;
>>>>>>> f9faa44e09744d09bf755b073e02e5ee2d177306
}

void Shell::scheduler() {
    if (runningProcess != nullptr) return ;
    for (int i = READY_QUEUE_NUM - 1; i >= 0; i--) {
        if (readyQueue[i]->front() != nullptr) {
            PCB *p = readyQueue[i] -> front();
            readyQueue[i] -> pop();
            p -> setStatus(Type::RUNNING);
            p -> setNextProcess(nullptr);
            runningProcess = p;
            return ;
        }
    }
}

bool Shell::checkReadyQueue() {
    for (int i = READY_QUEUE_NUM - 1; i > 0; i--) {
        if (readyQueue[i]->front() != nullptr) return true;
    }
    return false;
}

void Shell::listReadyProcess() {
    for (int i = READY_QUEUE_NUM - 1; i >= 0; i--) {
        printf("%d: ", i);
        if (i == 0) printf("init\n");
        else {
            readyQueue[i] -> listQueue();
        }
    }
}

void Shell::listBlockProcess() {
    for (int i = 0; i < RESOURCE_NUM; i++) {
        printf("R%d: ", i);
        blockQueue[i] -> listQueue();
    }
}

void Shell::listResource() {
    for (int i = 0; i < RESOURCE_NUM; i++) {
        printf("R%d %d\n", i + 1, countResource[i]);
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

void Shell::block2ready(int resId) {
    PCB *p = nullptr;
    p = blockQueue[resId] -> searchItem(resId, countResource[resId]);
    while (p != nullptr) {
        int num = p -> getRequireResource(resId);
        p -> getResource(resId, num);
        p -> setStatus(Type::READY);
        std::cout<<p -> getPID()<<" ";
        readyQueue[p -> getPriorityId()]->insert(p);
        p = blockQueue[resId] -> searchItem(resId, countResource[resId]);
    }
    std::cout<<std::endl;
}

void Shell::printError() {
    printf("Command error\n");
}