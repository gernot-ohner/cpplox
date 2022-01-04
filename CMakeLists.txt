cmake_minimum_required(VERSION 3.20)
project(cpplox)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpplox
        src/main.cpp
        src/Scanner.cpp
        src/Scanner.h
        src/model/Token.cpp
        src/model/Token.h
        src/util/magic_enum.hpp
        src/Parser.cpp
        src/Parser.h
        src/visitors/PrettyPrintVisitor.cpp
        src/visitors/PrettyPrintVisitor.h
        src/visitors/PrettyPrintVisitor.cpp
        src/visitors/PrettyPrintVisitor.h
        src/model/Expr.h
        src/Parser.cpp
        src/Parser.h
        src/Runner.cpp
        src/Runner.h
        src/visitors/EvaluationVisitor.cpp src/visitors/EvaluationVisitor.h)

add_executable(cpplox_tests
        test/test.cpp
        test/catch.hpp
        test/ScannerTest.cpp
        test/ExprTest.cpp
        test/ParserTest.cpp

        src/Scanner.cpp
        src/Scanner.h
        src/model/Token.cpp
        src/model/Token.h
        src/util/magic_enum.hpp
        src/Parser.cpp
        src/Parser.h
        src/visitors/PrettyPrintVisitor.cpp
        src/visitors/PrettyPrintVisitor.h
        src/model/Expr.h
        src/Parser.cpp
        src/Parser.h
        src/Runner.cpp
        src/Runner.h
        src/visitors/EvaluationVisitor.cpp src/visitors/EvaluationVisitor.h test/EvaluationTest.cpp)