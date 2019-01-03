//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_UNARYEXPRESSION_H
#define FIRSTMILESTONE_UNARYEXPRESSION_H


#include "Expression.h"

class UnaryExpression : public Expression {
private:
    Expression *expression;
public:
    explicit UnaryExpression(Expression *expression);

    virtual double calculate() = 0;

    Expression *getExpression() const;
    ~UnaryExpression();
};


#endif //FIRSTMILESTONE_UNARYEXPRESSION_H
