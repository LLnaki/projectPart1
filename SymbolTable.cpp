//
// Created by Dorin Keshales on 2018-12-22.
//

#include "SymbolTable.h"
#include <iostream>
#define VAR_VALUE_FILE "./VariablesValues.txt"
#define LINK_INDICATOR_IN_FILE "Link:"
#define PATH_WORD_FOR_LINK_WITHOUT_PATH "-withoutPath-"
#define VALUE_WORD_FOR_LINK_WITHOUT_VALUE "-withoutVal-"
/**
 * function which similar to the stoi function of string in java.
 *
 * @param s the requested string ti split.
 * @param delim delimiter.
 * @return a vector which holds the substrings which the comma was in between.
 */
vector<string> SymbolTable::split(string s) {
    stringstream ss(s);
    string item;
    char p = ',';
    vector<string> words;
    while (getline(ss, item, p)) {
        words.push_back(item);
    }
    return words;
}

bool SymbolTable:: isDouble(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;

}



/*map<string, double> SymbolTable::GetSymbolTable() {
    return this->varStringToItsValue;
}*/

/*void SymbolTable::setValue(string var, double value) {
    this->varStringToItsValue[var] = value;
}*/
/**
 * The function returns symbolTable, not including variables of links that have not
 * values.
 * @return
 */
map<string, double> SymbolTable::GetSymbolTable() {
    map<string, double> returnMap;
    //The loop that goes through each key in varStringToItsValue(each list of vars that are bounded)
    for (auto itInSymbolTable = this->varStringToItsValue.begin();
         itInSymbolTable != this->varStringToItsValue.end(); ++itInSymbolTable) {
        //The loop goes through each vector of bound values to the same path.
        for (auto itInBoundVars = itInSymbolTable->first.begin();
             itInBoundVars != itInSymbolTable->first.end(); ++itInBoundVars) {
            /*
             *
             * return map consists of all variables that are in the data base(each variable in
             * each list of bound variables to its common value). That is, this map
             * maps each variable to its double type value.
            */
            returnMap[*itInBoundVars] = itInSymbolTable->second;
        }
    }
    return returnMap;
}

/**
 * I should send to Dorin this function. It sets a value only if such var exist.
 */
void SymbolTable::setValue(string var, double value) {
    pthread_mutex_lock(this->mutex);
    bool isFoundAmongExistedVariables = false;

    for (auto it = this->varStringToItsValue.begin(); it != this->varStringToItsValue.end(); ++it) {
        if (find(it->first.begin(), it->first.end(), var) != it->first.end()) {
            it->second = value;
            isFoundAmongExistedVariables = true;
            break;
        }
    }
    vector<vector<string>> :: iterator* itOfFound = nullptr;
    for (auto it = this->linksWithoutValues.begin(); !isFoundAmongExistedVariables && it != this->linksWithoutValues.end(); ++it) {
        if (find(it->begin(), it->end(), var) != it->end()) {
            this->varStringToItsValue[*it] = value;
            itOfFound = new vector<vector<string>>::iterator(it);
            break;
        }
    }
    if ( itOfFound != nullptr) {
        this->linksWithoutValues.erase(*itOfFound);
        delete itOfFound;
    }
    cout<<"in SymbolTable.cpp in setValue function." << endl;
    pthread_mutex_unlock(this->mutex);
}

void SymbolTable:: sendToServer(string var) {
    if (!this->isConnectedToServer) {
        return;
    }
    if (!this->isVarExist(var)) {
        throw invalid_argument("Cannot send to the server a value of a non-existing variable.");
    }
    for (auto it = this->varStringToItsValue.begin(); it != this->varStringToItsValue.end(); ++it) {
        if (find(it->first.begin(), it->first.end(), var) != it->first.end() && this->paths.isPathExist(it->first[0])) {
            this->dataClientOfSymbolTable->send(this->paths.GetPath(it->first[0]), it->second);
        }
    }
}

double SymbolTable::getValue(string var) {

    for (auto it = this->varStringToItsValue.begin(); it != this->varStringToItsValue.end(); ++it) {
        if (find(it->first.begin(), it->first.end(), var) != it->first.end()) {
            return it->second;
        }
    }
    for (auto &it: this->linksWithoutValues) {
        if (find(it.begin(), it.end(), var) != it.end()) {
            throw "This variable was not initialized with some value yet";
        }
    }
    throw "Var was not found - can't get the value of a non existing var";
}

bool SymbolTable::isVarExist(string var) {
    for (auto it = this->varStringToItsValue.begin(); it != this->varStringToItsValue.end(); ++it) {
        if (find(it->first.begin(), it->first.end(), var) != it->first.end()) {
            return true;
        }
    }
    for (auto it = this->linksWithoutValues.begin(); it != this->linksWithoutValues.end(); ++it) {
        if (find(it->begin(), it->end(), var) != it->end()) {
            return true;
        }
    }

    return false;
}


void SymbolTable::loadMap() {
    ifstream variablesVal;
    // Opening the VAR_VALUE_FILE file.
    variablesVal.open(VAR_VALUE_FILE, ios::in);

    string line;
    string path;
    double value;
    vector<string> *variablesInLink = new vector<string>;
    string linkIndicator = LINK_INDICATOR_IN_FILE;
    string indicatingLine = linkIndicator + ":" + "(\\w+)" + "," + "(\\w+)";
    string pathAndValue;
    vector<string> pathAndValueVector;
    regex linkIndicatingLineFormat(indicatingLine);

    getline(variablesVal, line);
    pathAndValue = line.substr(linkIndicator.length(), line.length() - linkIndicator.length());
    pathAndValueVector = split(pathAndValue);
    path = pathAndValueVector[0];
    value = stod(pathAndValueVector[1]);

    // As long as we still have lines to read from the file.
    while (getline(variablesVal, line)) {
        // Splitting the line into the variable's name and it's value.
        if (regex_match(line, linkIndicatingLineFormat)) {
            this->varStringToItsValue[*variablesInLink] = value;
            if (path != PATH_WORD_FOR_LINK_WITHOUT_PATH) {
                this->paths.SetPath((*variablesInLink)[0], path);
            }
            pathAndValue = line.substr(linkIndicator.length(), line.length() - linkIndicator.length());
            pathAndValueVector = split(pathAndValue);
            path = pathAndValueVector[0];
            value = stod(pathAndValueVector[1]);
            delete variablesInLink;
            variablesInLink = new vector<string>;

        } else {
            variablesInLink->push_back(line);
        }
    }
    delete variablesInLink;
    // Closing the VAR_VALUE_FILE file.
    variablesVal.close();
}

void SymbolTable::saveMap() {
    ofstream variablesVal;
    // Opening the VAR_VALUE_FILE file.
    variablesVal.open(VAR_VALUE_FILE, ios::trunc);    // delete all file content

    // Saving all the variables and their values to the DB file.
    for (auto &itMap: this->varStringToItsValue) {
        string path = "";
        try {
            path = this->paths.GetPath(itMap.first[0]);
            //if a link has no path.
        } catch (exception& noPathException) {
            path = PATH_WORD_FOR_LINK_WITHOUT_PATH;
        }
        /*
         * Each link path and value goes in the same line where the first word is link indicator word.
         * After link-indicator word, go path and link value in the format "path,value".
         */
        variablesVal << LINK_INDICATOR_IN_FILE << path << "," <<
                     to_string(itMap.second) << endl;

        for (auto &variableInLink: itMap.first) {
            //After link declaration line, next lines are variables, until new link-line.
            variablesVal << variableInLink << endl;
        }
    }
    for (auto &it: this->linksWithoutValues) {
        string path = "";
        try {
            path = this->paths.GetPath(it[0]);
            //if a link has no path.
        } catch (exception& noPathException) {
            path = PATH_WORD_FOR_LINK_WITHOUT_PATH;
        }
        variablesVal << LINK_INDICATOR_IN_FILE << path << "," <<
        VALUE_WORD_FOR_LINK_WITHOUT_VALUE << endl;
        for (auto &variableInLink: it) {
            //After link declaration line, next lines are variables, until new link-line.
            variablesVal << variableInLink << endl;
        }
    }

    // Closing the VAR_VALUE_FILE file.
    variablesVal.close();
}
/*void SymbolTable::loadMap() {
    ifstream variablesVal;
    // Opening the VAR_VALUE_FILE file.
    variablesVal.open(VAR_VALUE_FILE, ios::in);
    string line, varName;
    double value;

    // As long as we still have lines to read from the file.
    while (getline(variablesVal, line)) {
        // Splitting the line into the variable's name and it's value.
        auto v = split(line);
        varName = v[0];
        value = stod(v[1]);

        this->varStringToItsValue[varName] = value;
    }

    // Closing the VAR_VALUE_FILE file.
    variablesVal.close();
}*/

/*void SymbolTable::saveMap() {
    ofstream variablesVal;
    // Opening the VAR_VALUE_FILE file.
    variablesVal.open(VAR_VALUE_FILE, ios::trunc);    // delete all file content

    // Saving all the variables and their values to the DB file.
    for (auto &v: this->varStringToItsValue) {
        variablesVal << v.first << "," << to_string(v.second) << endl;
    }

    // Closing the VAR_VALUE_FILE file.
    variablesVal.close();
}*/


void SymbolTable::bindNewVarToExistingLink(string newVar, string anotherVarInThisLink) {
    if (this->isVarExist(newVar)) {
        throw "Error. Trying to bind already existing variable as a new variable.";
    }
    vector<string> variablesInThisLink;
    //We make a copy in order to iterate with an ability to change map key/value.
    map<vector<string>, double> copyOfVarStringToItsValue(this->varStringToItsValue);

    for (map<vector<string>, double>::iterator iteratorOfLink = copyOfVarStringToItsValue.begin();
         iteratorOfLink != copyOfVarStringToItsValue.end(); ++iteratorOfLink) {

        if (find(iteratorOfLink->first.begin(), iteratorOfLink->first.end(), anotherVarInThisLink)
            != iteratorOfLink->first.end()) {

            vector<string> updatedLink(iteratorOfLink->first);
            updatedLink.push_back(newVar);
            double value = iteratorOfLink->second;

            this->varStringToItsValue.erase(iteratorOfLink->first);
            this->varStringToItsValue[updatedLink] = value;

            /*
           * We know that each var is saved only ones in varStringToItsValue. Therefore, if we found it,
           * we won't find it any more(and only double value of the link to which "var" belongs
           * will be updated by "value".
           */
            return;
        }
    }
    for (auto it = this->linksWithoutValues.begin(); it != this->linksWithoutValues.end(); ++it) {
        if (find(it->begin(), it->end(),anotherVarInThisLink) != it->end()) {
            it->push_back(newVar);
            return;
        }
    }
    throw "Error. Cannot bind a new variable to non-existing variable with bindNewVarToExistingLink function.";

}

void SymbolTable::createNewLinkWithNewVar(string newVar, string pathToWhichWeBind) {
    if (this->isVarExist(newVar)) {
        throw "createNewLinkWithNewVar cannot create new link with already existing variable.";
    }
    this->paths.SetPath(newVar, pathToWhichWeBind);
    vector<string> newLinkVariables;
    newLinkVariables.push_back(newVar);
    this->linksWithoutValues.push_back(newLinkVariables);

}
/**
 * This function creates a new link without path. That is variable can be
 * binded to this variable in the future but they haven't path. A common value
 * is only thing that defines them.
 * @param newVar - new var.
 * @param value  - value of new var.
 */
void SymbolTable::createNewLinkWithNewVar(string newVar, double value) {
    if (this->isVarExist(newVar)) {
        throw "createNewLinkWithNewVar cannot create new link with already existing variable.";
    }
    vector<string> newLinkVariables;
    newLinkVariables.push_back(newVar);
    this->varStringToItsValue[newLinkVariables] = value;
}
void SymbolTable::createNewLinkWithNewVar(string newVar) {
    if (this->isVarExist(newVar)) {
        throw "createNewLinkWithNewVar cannot create a new link with already existing variable.";
    }
    vector<string> newLinkVariables;
    newLinkVariables.push_back(newVar);
    this->linksWithoutValues.push_back(newLinkVariables);
}

/**
 * The binding.
 * @param newVar
 * @param keeper
 */
void SymbolTable::bind(string newVar, string keeper) {
    regex pathFormat("\"(.+)\"");
    if (regex_match(keeper, pathFormat)) {
        string pathToWhichWeBind = keeper.substr(1, keeper.length() - 2);
        /*
         * Because the Binder always saves only representatives of each link to varValuesPaths, the varValuesPaths represents
         * a bijective function. That is, each representative is saved once(key) and has a unique path(value).
         * The Binder works with SymbolTable which's varValuesPath is bijective.Otherwise, an exception is thrown.
         * Therefore this vector must have only key-value pair(else, we throw an exception).
         */
        vector<string> vectorWithVarsOfThisPath = this->getVarValuesPaths()->getVariablesOfPath(
                pathToWhichWeBind);
        if (vectorWithVarsOfThisPath.size() > 1) {
            throw "Error. Binder operates only on SymbolTables with bijective varValuesPaths object.";
        }
        if (vectorWithVarsOfThisPath.size() == 1) {
            //first argument is a new var. Second argument is an existing var.
            this->bindNewVarToExistingLink(newVar, vectorWithVarsOfThisPath[0]);
        } else {
            this->createNewLinkWithNewVar(newVar, pathToWhichWeBind);
        }
    } else if (this->isVarExist(keeper)) {
        this->bindNewVarToExistingLink(newVar, keeper);
    }else if(isDouble(keeper)) {
        this->createNewLinkWithNewVar(newVar, stod(keeper));
    } else {
        throw "Error. The binder cannot bind a new variable to non-existing variable.";
    }

}

void SymbolTable:: establishConnectionToServer(int port, string ip, pthread_mutex_t* mut) {

    if (this->dataClientOfSymbolTable != nullptr) {
        throw "Error. The connection had been established already. Only one connection is possible simultaneously.";
    }
    this->dataClientOfSymbolTable = new DataClient(port, ip, mut);
    this->dataClientOfSymbolTable->connect();
    this->isConnectedToServer = true;
}
void SymbolTable::interruptConnectionToServer() {
    if (this->dataClientOfSymbolTable != nullptr) {
        delete this->dataClientOfSymbolTable;
    }
    this->isConnectedToServer = false;
}
void SymbolTable::tuneForCooperationWithClient(pthread_mutex_t* mut) {
    //this->mutex = mut;
    this->isClientConnectedToSymbolTable = true;
}




