//
// Created by Dorin Keshales on 2018-12-22.
//
#ifndef FIRSTMILESTONE_SHANTINGYARDALGORITHEM_CPP
#define FIRSTMILESTONE_SHANTINGYARDALGORITHEM_CPP
#include <string>
#include <stack>
#include <queue>
#include "Div.h"
#include "Plus.h"
#include "Mul.h"
#include "Minus.h"
#include "Number.h"
#include "Neg.h"
#include "ShantingYardAlgorithem.h"
#include "Commands/SymbolTable.h"
#include <iostream>
#include <cmath>
using namespace std;

// Test if token is an operator
bool ShantingYardAlgorithem::isOperator(const string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int ShantingYardAlgorithem::Precedence(string op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    if (op == "*" || op == "/") {
        return 2;
    }
    return 0;
}

double ShantingYardAlgorithem::evaluate(vector<string> tokens) {
    stack<string> operators;
    queue<string> line;

    for (int i = 0; i < tokens.size(); ++i) {
        if (isdigit(tokens[i][0]) && tokens[i].length() >= 1) {
            for (int j = 0; j < tokens[i].length(); ++j) {
                if (!isdigit(tokens[i][j])) {
                    break;
                }
            }
            line.push(tokens[i]);
        } else if (this->symbolTable->isVarExist(tokens[i])){
            line.push(to_string(this->symbolTable->getValue(tokens[i])));
        } else if (isOperator(tokens[i])) {
                while (!operators.empty()) {
                    if (Precedence(tokens[i]) <= Precedence(operators.top())) {
                        line.push(operators.top());
                        operators.pop();
                    } else {
                        break;
                    }
                }
                operators.push(tokens[i]);
        } else {
            if (tokens[i] == "(") {
                operators.push(tokens[i]);
            } else {
                if (tokens[i] == ")") {
                    while (!operators.empty() && (operators.top() != "(")) {
                        line.push(operators.top());
                        operators.pop();
                    }
                    if (!operators.empty()) {
                        operators.pop();
                    } else {
                        __throw_invalid_argument("Missing parentheses in the expression - unable to calculate.");
                    }
                } else {
                    line.push(tokens[i]);
                }
            }
        }

    }
    while (!operators.empty()) {
        if (operators.top() == "(" || operators.top() == ")") {
            __throw_invalid_argument("Mis-match in parentheses of an expression.");
        }
        line.push(operators.top());
        operators.pop();
    }

    vector<string> ready;

    while (!line.empty()) {
        ready.push_back(line.front());
        line.pop();
    }

    return RPNtoDouble(ready);

}

Expression *ShantingYardAlgorithem::ExpressionFactory(double left, char op, double right) {
    switch (op) {
        case '+':
            return new Plus(new Number(left), new Number(right));
        case '-':
            return new Minus(new Number(left), new Number(right));
        case '*':
            return new Mul(new Number(left), new Number(right));
        case '/':
            return new Div(new Number(left), new Number(right));
        default:
            __throw_invalid_argument("Unable to recognize the operator in the expression.");
    }
    //return nullptr;
}


double ShantingYardAlgorithem::RPNtoDouble(vector<string> tokens) {
    stack<string> s;
    for (int i = 0; i < tokens.size(); ++i) {
        if (!isOperator(tokens[i])) {
            s.push(tokens[i]);
        } else {
            double result = 0;
            double rightElement = strtod(s.top().c_str(), nullptr);
            s.pop();

            if (!s.empty()) {
                double leftElement = strtod(s.top().c_str(), nullptr);
                s.pop();
                Expression* exprResult = ExpressionFactory(leftElement, tokens[i].c_str()[0], rightElement);
                result = exprResult->calculate();
                delete exprResult;
            } else {
                if (tokens[i] == "-") {
                    Expression *neg = new Neg(new Number(rightElement));
                    result = neg->calculate();
                    delete neg;
                } else {
                    Number* numExpr = new Number(rightElement);
                    result = (numExpr)->calculate();
                    delete(numExpr);
                }
            }
            s.push(to_string(result));
        }
    }
    return strtod(s.top().c_str(), nullptr);
}



#endif //FIRSTMILESTONE_SHANTINGYARDALGORITHEM_CPP
































