//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_BINARYEXPRESSION_H
#define FIRSTMILESTONE_BINARYEXPRESSION_H


#include "Expression.h"
/**
*This class defines expressions which always have two components(expressions), on which
* a calculation of expression is performed.
*/
class BinaryExpression : public Expression {
private:
	//First component.
    Expression *first;
	//Second component.
    Expression *second;
public:
    BinaryExpression(Expression *first, Expression *second);

    virtual double calculate() = 0;

    Expression *getFirst() const;

    Expression *getSecond() const;
    ~BinaryExpression();
};


#endif //FIRSTMILESTONE_BINARYEXPRESSION_H
