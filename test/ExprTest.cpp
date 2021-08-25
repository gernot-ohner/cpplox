//
// Created by gernotohner on 23.08.21.
//

#include <iostream>
#include "catch.hpp"
#include "../src/model/Token.h"
#include "../src/visitors/PrettyPrintVisitor.h"

class value;

TEST_CASE("can pretty print a subtraction") {
    // given
    Token minus{.type = TokenType::MINUS, .lexeme = "-", .line = 0 };
    expr_t just123 = Literal(123.0);
    expr_t minus123 = Unary(minus, just123);
    expr_t binary = Binary(minus123, minus, just123);
    std::cout << "Binary is copy_constructible: " << std::is_copy_constructible_v<Binary> << std::endl;
    std::cout << "Unary is copy_constructible: " << std::is_copy_constructible_v<Unary> << std::endl;
    std::cout << "Grouping is copy_constructible: " << std::is_copy_constructible_v<Grouping> << std::endl;
    std::cout << "Literal is copy_constructible: " << std::is_copy_constructible_v<Literal> << std::endl;
    std::cout << "expr_t is copy_constructible: " << std::is_copy_constructible_v<expr_t> << std::endl;

    std::cout << "Binary is copy_assignable: " << std::is_copy_assignable_v<Binary> << std::endl;
    std::cout << "Unary is copy_assignable: " << std::is_copy_assignable_v<Unary> << std::endl;
    std::cout << "Grouping is copy_assignable: " << std::is_copy_assignable_v<Grouping> << std::endl;
    std::cout << "Literal is copy_assignable: " << std::is_copy_assignable_v<Literal> << std::endl;
    std::cout << "expr_t is copy_assignable: " << std::is_copy_assignable_v<expr_t> << std::endl;
    std::string expected = "(- (- 123) 123)";

    // when
    PrettyPrintVisitor p{};
    auto actual = p.visitExpr(binary);
    std::cout << actual << std::endl;

    // then
    REQUIRE(actual == expected);
}


TEST_CASE("can pretty print (* (- 123) (group 45.67))") {
    // given
    Token times {.type = TokenType::STAR, .lexeme = "*", .line = 0};
    Token minus {.type = TokenType::MINUS, .lexeme = "-", .line = 0};

    expr_t just123 = Literal(123.0);
    expr_t minus123 = Unary(minus, just123);
    expr_t just45_67 = Literal(45.67);
    expr_t group_45_67 = Grouping(just45_67);
    expr_t binary = Binary(minus123, times, group_45_67);

    // -123 * (45.67)
    std::string expected = "(* (- 123) (group 45.67))";

    // when
    PrettyPrintVisitor p{};
    auto actual = p.visitExpr(binary);
    std::cout << actual << std::endl;

    // then
    REQUIRE(actual == expected);
}
