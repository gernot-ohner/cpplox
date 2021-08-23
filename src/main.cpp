#include <iostream>
#include <fstream>
#include "Scanner.h"

void runPrompt();
void runFile(const std::string& path);
void run(std::string source);

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hi, I'm "  << argv[0] << ", I'll be your program today." << std::endl;
    if (argc == 1) {
        std::cout << "starting interactive mode!" << std::endl;
        runPrompt();
    } else if (argc == 2) {
        std::cout << "command line argument was " << argv[1] << std::endl;
        runFile(argv[1]);
    } else {
        std::cout << "Usage: cpplox <input_file>" << std::endl;
        std::exit(65);
    }

    return 0;
}

void runFile(const std::string& path) {
    std::ifstream is {path};
    // TODO figure out how to make this work for relative paths
    if (!is) std::cout << "could not open file for reading!" << std::endl;

    std::string source((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());

    std::cout << "reading source successful, source is:" << std::endl;
    std::cout << source << std::endl;
}

void runPrompt() {
    while(true) {
        // TODO figure out how to make std::cin work with whitespace
        std::string command;
        std::cout << "> ";
        std::getline(std::cin,command);
        if (command == "stop" || command == "\n") break;
        std::cout << "using input: " << command << std::endl;
        run(command);
    }
}

void run(std::string source) {
    auto scanner = Scanner { std::move(source) };
    auto tokens = scanner.scanTokens();
    for (const auto &token : tokens) {
        if (auto x = std::get_if<std::monostate>(&token.literal)) {
            std::cout << "printing token: " << magic_enum::enum_name(token.type) << std::endl;
        } else if (auto number = get_if<double>(&token.literal)) {
            std::cout << "printing number: " << magic_enum::enum_name(token.type) << ": " << *number << std::endl;
        } else if (const std::string* string = get_if<std::string>(&token.literal)) {
            std::cout << "printing string: " << magic_enum::enum_name(token.type) << ": " << *string << std::endl;
        } else {
            std::cout << "WHO OR WHAT ARE YOU?" << std::endl;
        }
    }
}


