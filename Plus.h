//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_PLUS_H
#define FIRSTMILESTONE_PLUS_H


#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
    Plus(Expression *first, Expression *second);

    double calculate() override;
};


#endif //FIRSTMILESTONE_PLUS_H
