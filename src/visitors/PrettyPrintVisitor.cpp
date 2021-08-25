#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by gernotohner on 23.08.21.
//

#include <sstream>
#include "PrettyPrintVisitor.h"

std::string PrettyPrintVisitor::visitBinaryExpr(Binary expr) {
    std::stringstream ss;
    ss << "(";
    ss << expr.op.lexeme << " ";
    ss << PrettyPrintVisitor::visitExpr(expr.left) << " ";
    ss << PrettyPrintVisitor::visitExpr(expr.right);
    ss << ")";
    return ss.str();
}

std::string PrettyPrintVisitor::visitUnaryExpr(Unary expr) {
    std::stringstream ss;
    ss << "(";
    ss << expr.op.lexeme << " ";
    ss << PrettyPrintVisitor::visitExpr(expr.expression);
    ss << ")";
    return ss.str();
}

std::string PrettyPrintVisitor::visitGroupingExpr(Grouping expr) {
    std::stringstream ss;
    ss << "(group ";
    ss << PrettyPrintVisitor::visitExpr(expr.expression);
    ss << ")";
    return ss.str();
}

std::string PrettyPrintVisitor::visitLiteralExpr(Literal expr) {
    std::stringstream ss;
    if (holds_alternative<double>(expr.value)) ss << get<double>(expr.value);
    else if (holds_alternative<std::string>(expr.value)) ss << get<std::string>(expr.value);
    return ss.str();
}

std::string PrettyPrintVisitor::visitExpr(expr_t expr) {
    if (expr.type() == typeid(Binary)) return visitBinaryExpr(any_cast<Binary>(expr));
    else if (expr.type() == typeid(Unary)) return visitUnaryExpr(any_cast<Unary>(expr));
//    else if (expr.type() == typeid(Grouping)) return visitGroupingExpr(any_cast<Grouping>(expr));
    else if (expr.type() == typeid(Literal)) return visitLiteralExpr(any_cast<Literal>(expr));
    throw std::invalid_argument(
            "Expr needs to be one of the following types, but isn't: Binary, Unary, Grouping, Literal");
}

#pragma clang diagnostic pop