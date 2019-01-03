//
// Created by Dorin Keshales on 2018-12-20.
//

#include "Mul.h"

Mul::Mul(Expression *first, Expression *second) : BinaryExpression(first, second) {}

double Mul::calculate() {
    return this->getFirst()->calculate() * this->getSecond()->calculate();
}