
//
// Created by Dorin Keshales on 2018-12-20.
//

#include "Plus.h"

Plus::Plus(Expression *first, Expression *second) : BinaryExpression(first, second) {}

double Plus::calculate() {
    return this->getFirst()->calculate() + this->getSecond()->calculate();
}