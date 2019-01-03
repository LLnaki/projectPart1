//
// Created by Dorin Keshales on 2018-12-20.
//

#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression *first, Expression *second) : first(first), second(second) {}

Expression *BinaryExpression::getFirst() const {
    return this->first;
}

Expression *BinaryExpression::getSecond() const {
    return this->second;
}
BinaryExpression::~BinaryExpression() {
    if (this->first != nullptr) {
        delete this->first;
    }
    if (this->second != nullptr) {
        delete this->second;
    }
}
