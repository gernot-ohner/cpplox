//
// Created by gernotohner on 26.08.21.
//

#include <iostream>
#include "catch.hpp"
#include "../src/model/Token.h"
#include "../src/model/Expr.h"
#include "../src/visitors/EvaluationVisitor.h"

TEST_CASE("Evaluator: minimal equality example") {
    // given
    auto eq = Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "==", .literal=std::monostate(), .line = 1};
    auto input = Binary(Literal("lex"), eq, Literal("lix"));

    // when
    EvaluationVisitor e{};
    auto result = e.visitExpr(input);

    // then
    REQUIRE(std::any_cast<bool>(result) == false);
}


TEST_CASE("Evaluator: string plus is concatenation") {
    // given
    auto plus = Token{.type = TokenType::PLUS, .lexeme = "+", .literal=std::monostate(), .line = 1};
    auto input = Binary(Literal("hello "), plus, Literal("world"));

    // when
    EvaluationVisitor e{};
    auto result = e.visitExpr(input);

    // then
    REQUIRE(std::any_cast<std::string>(result) == "hello world");
}

TEST_CASE("Evaluator: inequality including unary minus") {
    // given
    auto leq = Token{.type = TokenType::LESS_EQUAL, .lexeme = "<=", .literal=std::monostate(), .line = 1};
    auto unary_minus = Token{.type = TokenType::MINUS, .lexeme = "-", .literal=std::monostate(), .line = 1};

    auto unary = Unary(unary_minus, Literal(5.0));
    auto input = Binary(Literal(-10.0), leq, unary);

    // when
    EvaluationVisitor e{};
    auto result = e.visitExpr(input);

    // then
    REQUIRE(std::any_cast<bool>(result) == true);
}


TEST_CASE("Evaluator: equality including literal bool and unary not") {
    // given
    auto eq = Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "==", .literal=std::monostate(), .line = 1};
    auto unary_not = Token{.type = TokenType::BANG, .lexeme = "!", .literal=std::monostate(), .line = 1};

    auto unary = Unary(unary_not, true);
    auto input = Binary(false, eq, unary);

    // when
    EvaluationVisitor e{};
    auto result = e.visitExpr(input);

    // then
    REQUIRE(std::any_cast<bool>(result) == true);
}


TEST_CASE("Evaluator: invalid expression throws exception") {
    // given
    auto eq = Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "==", .literal=std::monostate(), .line = 1};
    auto input = Binary(Literal("lex"), eq, Literal(5.0));

    // when
    EvaluationVisitor e{};

    // then
    REQUIRE_THROWS(e.visitExpr(input));
}

