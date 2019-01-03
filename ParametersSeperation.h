//
// Created by Dorin Keshales on 2018-12-24.
//

#ifndef FIRSTMILESTONE_PARAMETERSSEPERATION_H
#define FIRSTMILESTONE_PARAMETERSSEPERATION_H


//#include "CommandsInterpreter.h"
#include <string>
#include <vector>

using namespace std;


/**
 * This class provides with an ability to separate and detect a sequence
 * of words in the script that represent a well-defined mathematical
 * expression.
 */
class ParametersSeperation {
private:
    /**
     * The function finds and returns an iterator that points to to the last word in first
     * detected math expression in a range of a script between it to end.
     * @param it start of range where we search for end of first detected expression
     * @param end - end of the range where we search.
     * @param whetherInScopes - if the range starts already in some scopes(curly brackets)
     * @return  an iterator that points to to the last word in first
     * detected math expression in a range of a script between it to end.
     */
    vector<string>::iterator getEndIteratorOfFirstDetectedExpr(vector<string>::iterator it
            , vector<string>::iterator end ,const bool whetherInScopes);
public:
    /**
     * THe function searchs for "numOfParameters" first detected expressions and returns them.
     * If there is a syntax error, an exception is thrown.
     * @param v - vectior of script.
     * @param numOfParameters number of first detected math expressions to cut and put in vector.
     * @return the numOfParameters first detected math expresions. Each expression is a sequence of words
     * which is also a vector. Therefore we return vector<vector<string>>.
     */
    vector<vector<string>> SplitToParameters(vector<string> v,int numOfParameters);
    vector<string>::iterator getEndIteratorOfFirstDetectedExpr(vector<string>::iterator it
            , vector<string>::iterator end);

    /**
     * The function creates a string from all strings in vector of strings that are located between it1
     * and it2(including it1 and including i2)
     * */
    string joinStrsInRangeinVectorToSingleStr (
            vector<string>::iterator it1, vector<string>::iterator it2);
    //Checks whether s is a script operator.
    inline bool isOperator(string s);
    //Checks whether s is a mathematical operator.
    inline bool isMathemeticalOperation(string s);
    //Computes a num of words in provided vectors of expressions.
    int getNumOfWordsInExpressions(vector<vector<string>> expressions);



};

#endif //FIRSTMILESTONE_PARAMETERSSEPERATION_H
