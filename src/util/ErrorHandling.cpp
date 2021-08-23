//
// Created by gernotohner on 17.08.21.
//

#include <iostream>
#include "ErrorHandling.h"
void ErrorHandling::error(int line, const std::string& message) {
    // TODO the error reporting in the book also has a "where" argument
    //   don't know what that's for so I skipped it for now
    std::cerr << "[line " << line << "] Error " << message << std::endl;
}
