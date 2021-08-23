//
// Created by gernotohner on 19.08.21.
//

#include <iostream>
#include "../src/Scanner.h"
#include "catch.hpp"

TEST_CASE("Scanner can scan single character tokens") {
    // given
    Scanner s{",.()[]*+-;/"};
    std::vector<Token> expected{
            Token{.type = TokenType::COMMA, .lexeme = ",", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::DOT, .lexeme = ".", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::LEFT_PAREN, .lexeme = "(", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::RIGHT_PAREN, .lexeme = ")", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::LEFT_BRACE, .lexeme = "[", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::RIGHT_BRACE, .lexeme = "]", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::STAR, .lexeme = "*", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::PLUS, .lexeme = "+", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::MINUS, .lexeme = "-", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::SEMICOLON, .lexeme = ";", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::SLASH, .lexeme = "/", .literal=std::monostate(), .line = 1},
            Token{.type = TokenType::END_OF_FILE, .lexeme = "", .line = 1},
    };

    // when
    auto actual = s.scanTokens();

    // then
    REQUIRE(actual == expected);
}

TEST_CASE("Scanner can scan assignment") {
    // given
    Scanner s{"var language = \"lox\""};
    std::vector<Token> expected{
        Token{.type = TokenType::VAR, .lexeme = "var", .literal=std::monostate(), .line = 1},
        Token{.type = TokenType::IDENTIFIER, .lexeme = "language", .literal="language", .line = 1},
        Token{.type = TokenType::EQUAL, .lexeme = "=", .literal=std::monostate(), .line = 1},
        Token{.type = TokenType::STRING, .lexeme = "\"lox\"", .literal="lox", .line = 1},
        Token{.type = TokenType::END_OF_FILE, .lexeme = "", .line = 1},
        };

    // when
    auto actual = s.scanTokens();

    // then
    REQUIRE(actual == expected);
}

