//
// Created by Dorin Keshales on 2018-12-20.
//

#include "Minus.h"

Minus::Minus(Expression *first, Expression *second) : BinaryExpression(first, second) {}

double Minus::calculate() {
    return this->getFirst()->calculate() - this->getSecond()->calculate();
}

