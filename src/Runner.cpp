//
// Created by gernotohner on 25.08.21.
//

#include "Runner.h"

void Runner::runFile(const std::string &path) {
    std::ifstream is{path};
    // TODO figure out how to make this work for relative paths
    if (!is) std::cout << "could not open file for reading!" << std::endl;
//    hadError = false;

    std::string source((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());

    std::cout << "reading source successful, source is:" << std::endl;
    std::cout << source << std::endl;
}

void Runner::runPrompt() {
    while (true) {
        // TODO figure out how to make std::cin work with whitespace
//        hadError = false;
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command);
        if (command == "stop" || command == "\n") break;
        std::cout << "using input: " << command << std::endl;
        run(command);
    }
}

void Runner::run(std::string source) {
    auto scanner = Scanner{std::move(source)};
    auto tokens = scanner.scanTokens();
    for (const auto &token : tokens) {
        if (auto x = std::get_if<std::monostate>(&token.literal)) {
            std::cout << "printing token: " << magic_enum::enum_name(token.type) << std::endl;
        } else if (auto number = get_if<double>(&token.literal)) {
            std::cout << "printing number: " << magic_enum::enum_name(token.type) << ": " << *number << std::endl;
        } else if (const std::string *string = get_if<std::string>(&token.literal)) {
            std::cout << "printing string: " << magic_enum::enum_name(token.type) << ": " << *string << std::endl;
        } else {
            std::cout << "WHO OR WHAT ARE YOU?" << std::endl;
        }
    }
}

void Runner::error(int line, const std::string &message) {
    report(line, "", message);
}

void Runner::error(Token t, const std::string &message) {
    if (t.type == TokenType::END_OF_FILE) {
        report(t.line, " at end", message);
    } else {
        report(t.line, " at '" + t.lexeme + "'", message);
    }
}


void Runner::report(int line, const std::string &where, const std::string &message) {
    std::cerr << "[line " << line << "] Error " << where << ": " << message << std::endl;
//    Runner::hadError = true;
}