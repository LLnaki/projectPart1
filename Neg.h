//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_NEG_H
#define FIRSTMILESTONE_NEG_H


#include "UnaryExpression.h"

class Neg : public UnaryExpression {
public:
    Neg(Expression *expression);

    double calculate() override;
};


#endif //FIRSTMILESTONE_NEG_H
