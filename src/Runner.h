//
// Created by gernotohner on 25.08.21.
//

#ifndef CPPLOX_RUNNER_H
#define CPPLOX_RUNNER_H

#include <iostream>
#include <fstream>
#include "Scanner.h"
#include "Runner.h"


class Runner {
public:
    void runPrompt();
    void runFile(const std::string& path);
    void run(std::string source);

    static void error(int line, const std::string& message);
    static void error(Token, const std::string& message);

private:
    static void report(int line, const std::string& where, const std::string& message);

    // TODO this error stuff doesn't work yet
    //   leave it aside for now and fix it later
    static bool hadError;

};


#endif //CPPLOX_RUNNER_H
