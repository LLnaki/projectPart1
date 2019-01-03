//
// Created by Dorin Keshales on 2018-12-20.
//

#include "Div.h"

Div::Div(Expression *first, Expression *second) : BinaryExpression(first, second) {}

double Div::calculate() {
    return this->getFirst()->calculate() / this->getSecond()->calculate();
}
