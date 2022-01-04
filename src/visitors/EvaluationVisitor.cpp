//
// Created by gernotohner on 25.08.21.
//

#include <iostream>
#include "EvaluationVisitor.h"

double toD(expr_t expr) {
    try {
        return get<double>(std::any_cast<literal_t>(expr));
    } catch (...) {
        return std::any_cast<double>(expr);
    }
}

std::string toS(expr_t expr) {
    return get<std::string>(std::any_cast<literal_t>(expr));
}

bool isD(const expr_t& expr) {
    return expr.type() == typeid(double);
}

bool isB(const expr_t& expr) {
    return expr.type() == typeid(bool);
}

expr_t EvaluationVisitor::visitBinaryExpr(Binary expr) {
    auto left = evaluate(expr.left);
    auto right = evaluate(expr.right);

    switch (expr.op.type) {
        case TokenType::MINUS: return toD(left) - toD(right);
        case TokenType::STAR: return toD(left) * toD(right);
        case TokenType::SLASH: return toD(left) / toD(right);
        case TokenType::PLUS:
            if (isD(right) && isD(left)) return toD(left) + toD(right);
            else return toS(left) + toS(right);
        case TokenType::LESS:
            return toD(left) < toD(right);
        case TokenType::LESS_EQUAL:
            return toD(left) <= toD(right);
        case TokenType::GREATER:
            return toD(left) > toD(right);
        case TokenType::GREATER_EQUAL:
            return toD(left) >= toD(right);
        case TokenType::EQUAL_EQUAL:
            if (isD(right) && isD(left)) return toD(left) == toD(right);
            else if (isB(right) && isB(left)) return std::any_cast<bool>(left) == std::any_cast<bool>(right);
            else return toS(left) == toS(right);
        case TokenType::BANG_EQUAL:
            if (isD(right) && isD(left)) return toD(left) != toD(right);
            else if (isB(right) && isB(left)) return std::any_cast<bool>(left) != std::any_cast<bool>(right);
            else return toS(left) != toS(right);

        default:
            throw std::domain_error("op needs to be one of '+', '-', '*' or '/'.");

    }
}

expr_t EvaluationVisitor::visitUnaryExpr(Unary expr) {
    auto right = evaluate(expr.expression);
    if (expr.op.type == TokenType::MINUS) {
        return -toD(right);
    } else if (expr.op.type == TokenType::BANG) {
        return !std::any_cast<bool>(right);
    } else {
        throw std::invalid_argument("Unary operator is neither '!' (BANG) nor '-' (MINUS)");
    }
}

expr_t EvaluationVisitor::visitLiteralExpr(Literal expr) {
    return expr.value;
}

expr_t EvaluationVisitor::visitExpr(expr_t expr) {
    auto& type = expr.type();
    bool isBinary = type == typeid(Binary);
    if (isBinary) {
        auto binaryExpr = any_cast<Binary>(expr);
        return visitBinaryExpr(binaryExpr);
    }
    else if (expr.type() == typeid(Unary)) return visitUnaryExpr(any_cast<Unary>(expr));
    else if (expr.type() == typeid(Literal)) return visitLiteralExpr(any_cast<Literal>(expr));
    throw std::invalid_argument(
            "Expr needs to be one of the following types, but isn't: Binary, Unary, Grouping, Literal");
}

expr_t EvaluationVisitor::evaluate(expr_t expr) {
    if (expr.type() == typeid(Binary)) return any_cast<Binary>(expr).accept(*this);
    else if (expr.type() == typeid(Unary)) return any_cast<Unary>(expr).accept(*this);
    else if (expr.type() == typeid(Literal)) return any_cast<Literal>(expr).accept(*this);
    else if (expr.type() == typeid(bool)) return std::any_cast<bool>(expr);
    throw std::invalid_argument(
            "Expr needs to be one of the following types, but isn't: Binary, Unary, Grouping, Literal");
}
