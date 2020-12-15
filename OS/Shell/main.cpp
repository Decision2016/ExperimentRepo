#include <iostream>
#include <Shell.h>
#include <string>
#include <fstream>

int main(int argc, char* argv[]) {
    Shell shell = Shell();
    std::string command_line;
    if (argc == 1) {                                             // 如果参数为0，通过终端接收命令
        while (true) {
            std::cout<<"shell> ";
            getline(std::cin, command_line);
            int exit = shell.CommandAnalyze(command_line);
            if (exit == -1) break;
        }
    }
    else {                                                       // 如果参数为1，通过文件接收命令
        if (argc != 2) {
            printf("Wrong number of parameters.\n");
            return 0;
        }
        std::ifstream infile(argv[1]);
        while (getline(infile, command_line)) {
            int exit = shell.CommandAnalyze(command_line);
            if (exit == -1) break;
        }
    }

    return 0;
}