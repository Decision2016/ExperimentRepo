#include <iostream>
#include <Shell.h>
#include <string>

int main() {
    Shell shell = Shell();
    std::string command_line;
    while (true) {
        std::cout<<"shell> ";
        getline(std::cin, command_line);
        int exit = shell.CommandAnalyze(command_line);
        if (exit == -1) break;
    }
    return 0;
}