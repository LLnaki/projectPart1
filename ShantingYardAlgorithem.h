//
// Created by Dorin Keshales on 2018-12-22.
//

#ifndef FIRSTMILESTONE_SHANTINGYARDALGORITHEM_H
#define FIRSTMILESTONE_SHANTINGYARDALGORITHEM_H


#include "Expression.h"
#include <string>
#include "SymbolTable.h"
using namespace std;
/**
 * This class provides with a range of tools to perform a shuting yard algorithm on math
 * expressions.
 */
class ShantingYardAlgorithem {
private:
	/*
	*A variables of a programm where the algorithm is used.
	*It will be used to calculate expessions not only with number, but also
	*with program variables. 
	*/
    SymbolTable* symbolTable;
public:
    ShantingYardAlgorithem(SymbolTable* sT): symbolTable(sT) {}
	/**
	*This function checks whether a token is a legal expression operator.
	*/
    bool isOperator(const string &token);
	/**
	*The function returns a precedence of recieved expression operator. 
	*Each operator has its precendce according to which an order of calculatinng
	*of sub expressions is defined.
	*/
    int Precedence(string op);
	/**
	*The function gets a vector of tokens of an expression in order of this expression
	*and evaluates the expression which 'tokens' represent.
	*@param tokens - vector of tokens which represents an expression.
	*/
    double evaluate(vector<string> tokens);
	/**
	*The function gets seperated components of basic expressions(without sub-expressions in it)
	*and transforms these components to an expression and returns it.
	*/
    Expression *ExpressionFactory(double left, char op, double right);
	/**
	*The function gets a vector of strings which represents a math expression
	*in the form of Reversed Polish notation, calculates it and returns a result
	*of calculation.
	*/
    double RPNtoDouble(std::vector<std::string> tokens);

};


#endif //FIRSTMILESTONE_SHANTINGYARDALGORITHEM_H
