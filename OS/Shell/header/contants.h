//
// Created by Decision on 2020/11/1.
//

#ifndef SHELL_CONTANTS_H
#define SHELL_CONTANTS_H

enum Priorities {
    SYSTEM = 2,
    USER = 1,
    INITIAL = 0
};

enum Type {
    RUNNING,
    READY,
    BLOCK
};

const std::string CREATE = "cr";
const std::string DELETE = "de";
const std::string REQUIRE = "req";
const std::string RELEASE = "rel";
const std::string TIMEOUT = "to";
const std::string LIST = "list";
const std::string LIST_BLOCK = "block";
const std::string LIST_READY = "ready";
const std::string LIST_RES = "res";
const std::string EXIT = "exit";

const int RESOURCE_NUM = 4;
const int READY_QUEUE_NUM = 3;

#endif //SHELL_CONTANTS_H
