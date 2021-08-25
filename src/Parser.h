//
// Created by gernotohner on 23.08.21.
//

#ifndef CPPLOX_PARSER_H
#define CPPLOX_PARSER_H

#include <vector>
#include "model/Expr.h"

class Parser {
    struct ParserError : std::exception {
        // TODO shouldn't this do something at some point?
    };

public:
    explicit Parser(std::vector<Token>& tokens): tokens(tokens) {}

    expr_t expression();
    expr_t equality();
    expr_t comparison();
    expr_t term();
    expr_t factor();
    expr_t unary();
    expr_t primary();

private:
    bool match(const std::vector<TokenType>& tokenTypes);
    bool match(const TokenType& tokenType);
    [[nodiscard]] bool check(const TokenType& type) const;
    Token advance();
    [[nodiscard]] Token peek() const;
    [[nodiscard]] Token previous() const;
    [[nodiscard]] bool isAtEnd() const;
    Token consume(TokenType, std::string message);

private:
    std::vector<Token> tokens;
    int current = 0;

    static void error(Token token, std::string message);
};


#endif //CPPLOX_PARSER_H
