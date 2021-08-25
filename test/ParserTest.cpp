//
// Created by gernotohner on 23.08.21.
//

#include <queue>
#include <iostream>
#include "catch.hpp"
#include "../src/model/Token.h"
#include "../src/model/Expr.h"
#include "../src/Parser.h"
#include "../src/visitors/PrettyPrintVisitor.h"


TEST_CASE("can parse a correct stream of numeric tokens") {
    std::vector<Token> input{

        Token{.type = TokenType::NUMBER, .lexeme = "1", .literal=10.0, .line = 1},
          Token{.type = TokenType::LESS, .lexeme = "language", .literal=std::monostate(), .line = 1},
        Token{.type = TokenType::NUMBER, .lexeme = "1", .literal=15.0, .line = 1},

            Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "=", .literal=std::monostate(), .line = 1},

        Token{.type = TokenType::STRING, .lexeme = "\"lox\"", .literal="lox", .line = 1},
          Token{.type = TokenType::BANG_EQUAL, .lexeme = "!=", .literal=std::monostate(), .line = 1},
        Token{.type = TokenType::STRING, .lexeme = "\"lix\"", .literal="lix", .line = 1},

        Token{.type = TokenType::END_OF_FILE, .lexeme = "", .line = 1},
        };

    Parser parser {input};
    auto result = parser.expression();

    PrettyPrintVisitor p{};
    auto actual = p.visitExpr(result);
    std::cout << actual << std::endl;

    std::cout << "made it here!" << std::endl;





}
