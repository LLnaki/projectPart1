//
// Created by Dorin Keshales on 2018-12-20.
//

#include "Neg.h"

Neg::Neg(Expression *expression) : UnaryExpression(expression) {}

double Neg::calculate() {
    return (-1) * this->getExpression()->calculate();
}