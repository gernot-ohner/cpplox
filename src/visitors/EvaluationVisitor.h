//
// Created by gernotohner on 25.08.21.
//

#ifndef CPPLOX_EVALUATIONVISITOR_H
#define CPPLOX_EVALUATIONVISITOR_H


#include "../model/Expr.h"

class EvaluationVisitor : IVisitor<expr_t> {
public:

    expr_t evaluate(expr_t expr);

    expr_t visitExpr(expr_t expr) override;

    expr_t visitBinaryExpr(Binary expr) override;

    expr_t visitUnaryExpr(Unary expr) override;

//    expr_t visitGroupingExpr(Grouping expr) override;

    expr_t visitLiteralExpr(Literal expr) override;


};


#endif //CPPLOX_EVALUATIONVISITOR_H
