//
// Created by gernotohner on 17.08.21.
//

#ifndef CPPLOX_SCANNER_H
#define CPPLOX_SCANNER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "model/Token.h"

class Scanner {

public:
    explicit Scanner(std::string source);
    std::vector<Token> scanTokens();

private:
    int start = 0;
    int current = 0;
    int line = 1;
    std::string source;
    std::vector<Token> tokens {};

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type, literal_t literal = std::monostate());
    bool match(char expected);
    char peek();
    void string();

    void number();

    char peekNext();

    void identifier();

    std::unordered_map<std::string, TokenType> keywords {
        { "and",    TokenType::AND},
        { "class",  TokenType::CLASS},
        { "else",   TokenType::ELSE},
        { "false",  TokenType::FALSE},
        { "for",    TokenType::FOR},
        { "fun",    TokenType::FUN},
        { "if",     TokenType::IF},
        { "nil",    TokenType::NIL},
        { "or",     TokenType::OR},
        { "print",  TokenType::PRINT},
        { "return", TokenType::RETURN},
        { "super",  TokenType::SUPER},
        { "this",   TokenType::THIS},
        { "true",   TokenType::TRUE},
        { "var",    TokenType::VAR},
        { "while",  TokenType::WHILE},
    };
};


#endif //CPPLOX_SCANNER_H
