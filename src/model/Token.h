//
// Created by gernotohner on 17.08.21.
//

#ifndef CPPLOX_TOKEN_H
#define CPPLOX_TOKEN_H

#include <string>
#include <variant>
#include "../util/magic_enum.hpp"

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    END_OF_FILE
};

typedef std::variant<std::string, double, std::monostate> literal_t;

struct Token {
    TokenType type;
    std::string lexeme;
    literal_t literal;
    int line;

    [[nodiscard]] std::string toString() const;
    bool operator==(const Token& other) const;
};
std::ostream& operator <<( std::ostream& os, const Token& token);


#endif //CPPLOX_TOKEN_H
