//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_NUMBER_H
#define FIRSTMILESTONE_NUMBER_H


#include "Expression.h"

class Number : public Expression {
private:
    double number;
public:
    Number(double number);

    double calculate();
    ~Number() = default;
};


#endif //FIRSTMILESTONE_NUMBER_H
