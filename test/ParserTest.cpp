//
// Created by gernotohner on 23.08.21.
//

#include <queue>
#include "catch.hpp"
#include "../src/model/Token.h"
#include "../src/model/Expr.h"
#include "../src/Parser.h"
#include "../src/visitors/PrettyPrintVisitor.h"


TEST_CASE("minimal equality example") {
    // given
    std::vector<Token> input{
            Token{.type = TokenType::STRING, .lexeme = "lex", .literal="lex", .line = 1},
            Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "==", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::STRING, .lexeme = "lix", .literal="lix", .line = 1},
            Token{.type = TokenType::END_OF_FILE, .lexeme = "", .line = 1},
    };

    auto eq = Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "==", .literal=std::monostate(), .line = 1};
    auto expectedAst = Binary(Literal("lex"), eq, Literal("lix"));

    // when
    Parser parser{input};
    auto actualAst = parser.expression();


    PrettyPrintVisitor p{};
    auto actualString = p.visitExpr(actualAst);
    auto expectedString = p.visitExpr(expectedAst);

    // then
    REQUIRE(actualString == expectedString);
}

TEST_CASE("minimal example") {
    // given
    std::vector<Token> input{
            Token{.type = TokenType::NUMBER, .lexeme = "10", .literal=10.0, .line = 1},
            Token{.type = TokenType::LESS, .lexeme = "<", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::NUMBER, .lexeme = "15", .literal=15.0, .line = 1},
            Token{.type = TokenType::END_OF_FILE, .lexeme = "", .line = 1},
    };

    auto less = Token{.type = TokenType::LESS, .lexeme = "<", .literal=std::monostate(), .line = 1};
    auto expectedAst = Binary(Literal(10.0), less, Literal(15.0));

    // when
    Parser parser{input};
    auto actualAst = parser.expression();

    PrettyPrintVisitor p{};
    auto actualString = p.visitExpr(actualAst);
    auto expectedString = p.visitExpr(expectedAst);

    // then
    REQUIRE(actualString == expectedString);
}

TEST_CASE("can parse a correct stream of numeric tokens") {
    // given
    std::vector<Token> input{
            Token{.type = TokenType::NUMBER, .lexeme = "1", .literal=10.0, .line = 1},
            Token{.type = TokenType::LESS, .lexeme = "<", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::NUMBER, .lexeme = "1", .literal=15.0, .line = 1},

            Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "==", .literal=std::monostate(), .line = 1},

            Token{.type = TokenType::STRING, .lexeme = "\"lox\"", .literal="lox", .line = 1},
            Token{.type = TokenType::PLUS, .lexeme = "+", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::STRING, .lexeme = "\"lix\"", .literal="lix", .line = 1},

            Token{.type = TokenType::END_OF_FILE, .lexeme = "", .line = 1},
    };

    auto less = Token{.type = TokenType::LESS, .lexeme = "<", .literal=std::monostate(), .line = 1};
    auto plus = Token{.type = TokenType::PLUS, .lexeme = "+", .literal=std::monostate(), .line = 1};
    auto eq = Token{.type = TokenType::EQUAL_EQUAL, .lexeme = "==", .literal=std::monostate(), .line = 1};

    auto lessComparion = Binary(Literal(10.0), less, Literal(15.0));
    auto neqComparison = Binary(Literal("lox"), plus, Literal("lix"));
    std::any expectedAst = Binary(lessComparion, eq, neqComparison);

    // when
    Parser parser{input};
    std::any actualAst = parser.expression();

    PrettyPrintVisitor p{};
    auto actualString = p.visitExpr(actualAst);
    auto expectedString = p.visitExpr(expectedAst);

    // This works around all the problems std::any introduces for now,
    //   but I imagine evaluating expressions is going to be a nightmare again?
    //   or it could be fine, because I use a visitor pattern again.
    REQUIRE(actualString == expectedString);
}
