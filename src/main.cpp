#include <iostream>
#include <fstream>
#include "Scanner.h"
#include "Runner.h"


int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "starting interactive mode!" << std::endl;
        Runner r{};
        r.runPrompt();
    } else if (argc == 2) {
        std::cout << "command line argument was " << argv[1] << std::endl;
        Runner r{};
        r.runFile(argv[1]);
    } else {
        std::cout << "Usage: cpplox <input_file>" << std::endl;
        std::exit(65);
    }
    return 0;
}


