//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_MUL_H
#define FIRSTMILESTONE_MUL_H


#include "Expression.h"
#include "BinaryExpression.h"

class Mul : public BinaryExpression {
public:
    Mul(Expression *first, Expression *second);

    double calculate() override;
};


#endif //FIRSTMILESTONE_MUL_H
