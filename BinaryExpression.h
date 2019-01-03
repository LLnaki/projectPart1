//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_BINARYEXPRESSION_H
#define FIRSTMILESTONE_BINARYEXPRESSION_H


#include "Expression.h"

class BinaryExpression : public Expression {
private:
    Expression *first;
    Expression *second;
public:
    BinaryExpression(Expression *first, Expression *second);

    virtual double calculate() = 0;

    Expression *getFirst() const;

    Expression *getSecond() const;
    ~BinaryExpression();
};


#endif //FIRSTMILESTONE_BINARYEXPRESSION_H
