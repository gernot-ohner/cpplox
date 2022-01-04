//
// Created by gernotohner on 23.08.21.
//

#include <iostream>
#include "catch.hpp"
#include "../src/model/Token.h"
#include "../src/visitors/PrettyPrintVisitor.h"

class value;

TEST_CASE("AST: can pretty print a subtraction") {
    // given
    Token minus{.type = TokenType::MINUS, .lexeme = "-", .line = 0 };
    expr_t just123 = Literal(123.0);
    expr_t minus123 = Unary(minus, just123);
    expr_t binary = Binary(minus123, minus, just123);
    std::string expected = "(- (- 123) 123)";

    // when
    PrettyPrintVisitor p{};
    auto actual = p.visitExpr(binary);
    std::cout << actual << std::endl;

    // then
    REQUIRE(actual == expected);
}


TEST_CASE("AST: can pretty print (* (- 123) (group 45.67))") {
    // given
    Token times {.type = TokenType::STAR, .lexeme = "*", .line = 0};
    Token minus {.type = TokenType::MINUS, .lexeme = "-", .line = 0};

    expr_t just123 = Literal(123.0);
    expr_t minus123 = Unary(minus, just123);
    expr_t just45_67 = Literal(45.67);
//    expr_t group_45_67 = Grouping(just45_67);
    expr_t binary = Binary(minus123, times, just45_67);

    // -123 * (45.67)
    std::string expected = "(* (- 123) 45.67)";

    // when
    PrettyPrintVisitor p{};
    auto actual = p.visitExpr(binary);
    std::cout << actual << std::endl;

    // then
    REQUIRE(actual == expected);
}
