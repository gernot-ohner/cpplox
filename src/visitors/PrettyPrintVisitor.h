//
// Created by gernotohner on 23.08.21.
//

#ifndef CPPLOX_PRETTYPRINTVISITOR_H
#define CPPLOX_PRETTYPRINTVISITOR_H


#include "../model/Expr.h"

class PrettyPrintVisitor : public IVisitor<std::string> {
public:

    std::string visitExpr(expr_t expr) override;

    std::string visitBinaryExpr(Binary expr) override;

    std::string visitUnaryExpr(Unary expr) override;

    std::string visitGroupingExpr(Grouping expr) override;

    std::string visitLiteralExpr(Literal expr) override;

};


#endif //CPPLOX_PRETTYPRINTVISITOR_H
