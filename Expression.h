//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_EXPRESSION_H
#define FIRSTMILESTONE_EXPRESSION_H


class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() = default;
};

#endif //FIRSTMILESTONE_EXPRESSION_H
