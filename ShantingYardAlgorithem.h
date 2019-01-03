//
// Created by Dorin Keshales on 2018-12-22.
//

#ifndef FIRSTMILESTONE_SHANTINGYARDALGORITHEM_H
#define FIRSTMILESTONE_SHANTINGYARDALGORITHEM_H


#include "Expression.h"
#include <string>
#include "Commands/SymbolTable.h"
using namespace std;
/**
 * This class provides with a range of tools to perform a shuting yard algorithm on math
 * expressions.
 */
class ShantingYardAlgorithem {
private:
    SymbolTable* symbolTable;
public:
    ShantingYardAlgorithem(SymbolTable* sT): symbolTable(sT) {}
    bool isOperator(const string &token);

    int Precedence(string op);

    double evaluate(vector<string> tokens);

    Expression *ExpressionFactory(double left, char op, double right);

    double RPNtoDouble(std::vector<std::string> tokens);

};


#endif //FIRSTMILESTONE_SHANTINGYARDALGORITHEM_H
