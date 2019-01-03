//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_DIV_H
#define FIRSTMILESTONE_DIV_H


#include "BinaryExpression.h"

class Div : public BinaryExpression {
public:
    Div(Expression *first, Expression *second);

    double calculate() override;
};


#endif //FIRSTMILESTONE_DIV_H
