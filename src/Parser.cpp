//
// Created by gernotohner on 23.08.21.
//

#include <list>
#include <queue>
#include <memory>
#include "Parser.h"
#include "Runner.h"

expr_t Parser::expression() {
    return equality();
}

expr_t Parser::equality() {

    expr_t expr = comparison();
    std::vector<expr_t> exprs {};
    exprs.push_back(expr);
    while (match(std::vector<TokenType>{
            TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        Token op = previous();
        expr_t right = comparison();
        exprs.emplace_back(Binary(expr, op, right));
    }

    return exprs.back();
}


expr_t Parser::comparison() {
    expr_t expr = term();

    std::vector<expr_t> exprs {};
    exprs.push_back(expr);
    while (match(std::vector<TokenType>{
            TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        Token op = previous();
        expr_t right = term();
        exprs.emplace_back(Binary(expr, op, right));
    }

    return expr;
}

expr_t Parser::term() {
    expr_t expr = factor();
    std::vector<expr_t> exprs {};
    exprs.push_back(expr);
    while (match(std::vector<TokenType>{
        TokenType::PLUS, TokenType::MINUS})) {
        Token op = previous();
        expr_t right = factor();
        exprs.emplace_back(Binary(expr, op, right));
    }
    return expr;
}

expr_t Parser::factor() {
    expr_t expr = unary();
    std::vector<expr_t> exprs {};
    exprs.push_back(expr);
    while (match(std::vector<TokenType>{
        TokenType::STAR, TokenType::SLASH})) {
        Token op = previous();
        expr_t right = unary();
        exprs.emplace_back(Binary(expr, op, right));
    }
    return expr;
}

expr_t Parser::unary() {
    if (match(std::vector<TokenType>{TokenType::MINUS, TokenType::BANG})) {
        Token op = previous();
        expr_t right = unary();
        return Unary(op, right);
    }
    return primary();
}

//primary        → NUMBER | STRING | "true" | "false" | "nil"
//| "(" expression ")" ;
expr_t Parser::primary() {
    if (match(TokenType::TRUE)) return true;
    else if (match(TokenType::FALSE)) return false;
    else if (match(TokenType::NIL)) return Literal(std::monostate());
    else if (match(std::vector<TokenType>{TokenType::NUMBER, TokenType::STRING}))
        return Literal(previous().literal);
    else if (match(TokenType::LEFT_PAREN)) {
        expr_t expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");

        return Grouping(expr);
    }

    // TODO this is hacky
    return Literal(std::monostate());
}


// private
bool Parser::match(const std::vector<TokenType> &tokenTypes) {
    auto matches = std::any_of(tokenTypes.begin(),
                               tokenTypes.end(),
                               [this](TokenType t) { return check(t); });
    if (matches) advance();
    return matches;
}
bool Parser::match(const TokenType &tokenType) {
    return match(std::vector<TokenType>{tokenType});
}

bool Parser::check(const TokenType &type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::peek() const {
    return tokens.at(current);
}

Token Parser::previous() const {
    return tokens.at(current - 1);
}

bool Parser::isAtEnd() const {
    return peek().type >= TokenType::END_OF_FILE;
}

Token Parser::consume(TokenType tokenType, std::string message) {
    if (check(tokenType)) {
        return advance();
    }

//    error(peek(), message);
    Runner::error(peek(), message);
    throw ParserError{};
}

void Parser::error(Token token, std::string message) {
    Runner::error(token, message);
    throw ParserError{};
}




