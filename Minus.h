//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_MINUS_H
#define FIRSTMILESTONE_MINUS_H


#include "BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus(Expression *first, Expression *second);

    double calculate() override;
};


#endif //FIRSTMILESTONE_MINUS_H
