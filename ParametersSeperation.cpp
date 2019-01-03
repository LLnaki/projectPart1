#include <utility>

//
// Created by Dorin Keshales on 2018-12-24.
//

#include "ParametersSeperation.h"
#include <iostream>
vector<vector<string>> ParametersSeperation::SplitToParameters(vector<string> v, int numOfParameters) {
    vector<vector<string>> parameters;
    int i = 0;
    vector <string>:: iterator currentStart = v.begin();
    vector<string>:: iterator currentEnd;
    while(i < numOfParameters && currentStart != v.end()) {
        currentEnd = this->getEndIteratorOfFirstDetectedExpr(currentStart, v.end());
        parameters.push_back(vector<string>(currentStart, currentEnd + 1));

        currentStart = currentEnd + 1;
        if (currentStart != v.end() && *currentStart == ",") {
            ++currentStart;
        }
        ++i;
    }

    if ( i != numOfParameters) {
        throw "There are not enough expressions in v. Less then a required number of parameters. ";
    }
    return parameters;
}




inline bool ParametersSeperation:: isOperator(string c) {

    return c == "=" || c == "+" || c == "-" || c == "*" || c == "/" || c == "<" || c == ">" || c == "{" || c == "}" ||



           c == "(" || c == ")" || c == ",";

}



inline bool ParametersSeperation:: isMathemeticalOperation(string s) {

    return s == "+" || s == "-" || s == "*" || s == "/";

}



/*

 * The function creates a string from all strings in vector of strings that are located between it1

 * and it2(including it1 and including i2)

 */

string  ParametersSeperation:: joinStrsInRangeinVectorToSingleStr (vector<string>::iterator it1, vector<string>::iterator it2) {

    string result;

    while (it1 != it2) {

        result += *it1;

        ++it1;

    }

    result+= *it2;

    return result;

}

int i = 0;

/**
 *
 * The function returns an iterator that points to the end of first detected expression in vector of strings.

 * That is, an expression is  all between first iterator(argument it) and between return iterator(including the first

 * iterator and the return iterator.

 * Arguments:

 * vector<string>::iterator it - iterator that points to the first element in vector of strings where we seach for first

 * expression.

 * vector<string>::iterator end- an end point of the vector of strings where we search for the expression.

 * bool - whether in scopes. Users should always sent false as a value of its argument(the function uses recursive call

 * and therefore sometimes needs to change its value in a recursive tree).

 * If there is some syntax error - an exception is thrown.

 */
vector<string>::iterator ParametersSeperation:: getEndIteratorOfFirstDetectedExpr(vector<string>::iterator it
        , vector<string>::iterator end ,const bool whetherInScopes) {
    //untill the loop, these are checks for first word in in a passed range of the script. Its rules
    //differs from the rulles of checking starting from the second word in the range.
    if (!whetherInScopes && this->isOperator(*it) && !this->isMathemeticalOperation(*it)
    && *it != "(" && *it != ")") {
        return it;
    } else if (it == end && whetherInScopes) {

        throw "SYNTAX ERROR!";

    } else if(it == end && !whetherInScopes ) {

        return it - 1;


    //',' char is an explicit seperator between to word in a script.
    }else if( (it + 1  == end || *(it + 1) == ",") && !this->isOperator(*it) && !whetherInScopes) {

        return it;

    } else if ( (*it == "-" && (!this->isOperator(*(it + 1)) || *(it + 1) == "("))

                || (!this->isOperator(*it)) ){

        ++it;

    } else if (*it == "(") {

        ++i;

        vector<string>::iterator it2 = getEndIteratorOfFirstDetectedExpr(it+1, end, true);

        it = it2 + 1;

    } else {

        throw "SYNTAX ERROR!";

    }
    //this loop checks a script for an expression, starting at least from the second word in script.
    while (it != end) {

        if (*it == "," && whetherInScopes) {

            throw "SYNTAX ERROR!";

        } else if(*it == ",") {

            return it - 1;

        } else if (!this->isOperator(*it) && this->isMathemeticalOperation(*(it - 1))) {

            ++it;

        } else if (!this->isOperator(*it) && whetherInScopes) {

            throw "SYNTAX ERROR!";

        } else if (!this->isOperator(*it) && !whetherInScopes) {

            return it - 1;

        } else if (this->isMathemeticalOperation(*it) && (!this->isOperator(*(it - 1)) || *(it - 1) == ")")) {

            ++it;

        } else if (this->isMathemeticalOperation((*it))) {

            throw "SYNTAX ERROR!";

        } else if (*it == "(" && this->isMathemeticalOperation(*(it - 1))) {

            ++i;

            vector<string>::iterator it2 = this->getEndIteratorOfFirstDetectedExpr(it + 1, end, true);

            it = it2 + 1;

        } else if (*it == "(" && whetherInScopes) {

            throw "SYNTAX ERROR!";

        } else if (*it == "(") {

            return it - 1;

        } else if (*it == ")" && (!this->isOperator(*(it - 1)) || *(it - 1) == ")") && whetherInScopes) {

            return it;

        } else if (*it == ")") {

            throw "SYNTAX ERROR!";

        } else if (this->isOperator(*it) && (!this->isOperator(*(it - 1)) || *(it - 1) == ")")) {

            return it - 1;

        }

    }

    if (whetherInScopes) {

        throw "SYNTAX ERROR!";

    }

    return it - 1;

}

inline vector<string>::iterator ParametersSeperation:: getEndIteratorOfFirstDetectedExpr(vector<string>::iterator it
        , vector<string>::iterator end) {
    this->getEndIteratorOfFirstDetectedExpr(it, end, false);

}

int ParametersSeperation:: getNumOfWordsInExpressions(vector<vector<string>> expressions) {
    int retValue = 0;
    for (int i = 0; i < expressions.size(); ++i) {
        retValue += expressions[i].size();
    }
    return retValue;
}
/*
int main(int argc, const char *argv[]) {
    ParametersSeperation p;
    vector<string> v;
    string input;
    cin >> input;
    while(input != "END") {
        v.push_back(input);
        cin >> input;
    }
    int numArgs;
    cin >> numArgs;
    vector<vector<string>> seperatedV = p.SplitToParameters(v, numArgs);
    return 0;

}

*/