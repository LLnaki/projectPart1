//
// Created by Dorin Keshales on 2018-12-20.
//

#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(Expression *expression) : expression(expression) {}

Expression *UnaryExpression::getExpression() const {
    return this->expression;
}
UnaryExpression::~UnaryExpression() {
    if (this->expression != nullptr) {
        delete this->expression;
    }
}
