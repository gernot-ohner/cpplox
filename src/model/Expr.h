//
// Created by gernotohner on 23.08.21.
//

#ifndef CPPLOX_EXPR_H
#define CPPLOX_EXPR_H


#include "Token.h"
#include <memory>
#include <any>

typedef std::any expr_t;

template<typename R>
class IVisitor;

class Literal {
public:
    explicit Literal(literal_t value) : value(value) {}

    template<typename R>
    R accept(IVisitor<R> &visitor) {
        visitor.visitLiteralExpr(*this);
    }

public:
    literal_t value;
};


class Grouping {
public:
    Grouping(expr_t expression) : expression(expression) {}

    template<typename R>
    R accept(IVisitor<R> &visitor) {
        visitor.visitGroupingExpr(*this);
    }

public:
    expr_t expression{};
};

class Binary {
public:
    // TODO this probably isn't right. I should pass a pointer to the expr? Or a reference?
    Binary(expr_t left, Token op, expr_t right) : left(left), op(op), right(right) {}

    template<class R>
    R accept(IVisitor<R> &visitor) {
        visitor.visitBinaryExpr(*this);
    }

public:
    expr_t left;
    Token op;
    expr_t right;
};


class Unary {
public:
    Unary(Token op, expr_t expression) : op(op), expression(expression) {}

    template<typename R>
    R accept(IVisitor<R> &visitor) {
        visitor.visitUnaryExpr(*this);
    }

public:
    Token op;
    expr_t expression;
};


template<typename R>
class IVisitor {
public:
    virtual R visitExpr(expr_t expr) = 0;

    virtual R visitBinaryExpr(Binary expr) = 0;

    virtual R visitUnaryExpr(Unary expr) = 0;

    virtual R visitGroupingExpr(Grouping expr) = 0;

    virtual R visitLiteralExpr(Literal expr) = 0;
};

#endif //CPPLOX_EXPR_H

