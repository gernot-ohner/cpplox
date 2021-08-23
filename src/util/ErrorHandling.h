//
// Created by gernotohner on 17.08.21.
//

#ifndef CPPLOX_ERRORHANDLING_H
#define CPPLOX_ERRORHANDLING_H


#include <string>

class ErrorHandling {
public:
    static void error(int line, const std::string& message);
};


#endif //CPPLOX_ERRORHANDLING_H
