//
// Created by Dorin Keshales on 2018-12-15.
//

#include "CommandsInterpreter.h"
#include "iostream"
#include "pthread.h"
CommandsInterpreter::CommandsInterpreter() {
    //Initializing variable data base for a current script.
    this->symbolTable = new SymbolTable();
    this->condVariable = nullptr;
    this->mutex = nullptr;
    this->factory = nullptr;

}

vector<string> CommandsInterpreter::run() {
    string line;
    getline(cin, line);
    return Lexer(line);
}

vector<string> CommandsInterpreter::LexerScript(string filePath) {
    ifstream readScript;
    readScript.open(filePath, ios::in);
    string line;
    vector<string> tokens;
    //Reading each line in script.
    while (getline(readScript, line)) {
        //interpreting each line.
        vector<string> currentLineTokens = Lexer(line);
        //putting all words of interpreted line in return vector.
        tokens.insert(tokens.end(), currentLineTokens.begin(), currentLineTokens.end());
    }
    readScript.close();
    return tokens;
}

//todo var airspeed = bind "/instrumentation/airspeed-indicator/indicated-speed-kt"

vector<string> CommandsInterpreter::Lexer(string buffer) {
    string token;
    int i = 0;
    vector<string> tokens;
    vector<size_t> v;
    string toSearch = "\"";
    size_t pos = buffer.find(toSearch);

    // Repeat till end is reached
    while (pos != std::string::npos) {
        // Add position to the vector
        v.push_back(pos);

        // Get the next occurrence from the current position
        pos = buffer.find(toSearch, pos + toSearch.size());
    }

    size_t size;
    //calculating a size of passed buffer.
    size = !v.empty() ? v[0] : buffer.size();
    //interpreting while we haven't reached yet the end of buffer.
    while (i != size) {
        if (isOperator(buffer[i])) {
            if (!token.empty()) {
                tokens.push_back(token);
                token = "";
            }
            //If we get a comparing operator in script which has two chars.
            if ((buffer[i] == '<' || buffer[i] == '>' || buffer[i] == '!' || buffer[i] == '=') &&
                (buffer[i + 1] == '=')) {
                token += buffer[i];
                token += buffer[i + 1];
                i++;
            } else {
                token.push_back(buffer[i]);
            }
            tokens.push_back(token);
            token = "";
        } else {
            // a space is an indicator for the end of a word. Reaching it, we will add a ready word
            // to tokens.
            if (buffer[i] == ' ') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token = "";
                }
            } else {
                token += buffer[i];
            }
        }
        i++;
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    if (!v.empty()) {
        string h = buffer.substr(v[0], v[1]);
        tokens.push_back(h);
    }
    return tokens;
}

inline bool CommandsInterpreter::isOperator(char c) {
    return c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '{' || c == '}' ||
           c == '(' || c == ')' || c == ',';
}

void CommandsInterpreter::parse(vector<string> script) {
    bool isInitialMutexAndCondWhereInitialized = true;
    bool isFactoryWasInitialized = true;
    /*
     * If the mutex and the cond were not initialized yet. The cond and the mutex
     *always are initilized together, therefore if one of them wasn't initialized,
     * the second also was not.
     */
    if (this->mutex == nullptr) {
        isInitialMutexAndCondWhereInitialized= false;
        this->mutex = new pthread_mutex_t;
        this->condVariable = new pthread_cond_t;
        pthread_mutex_init(this->mutex, nullptr);
        pthread_cond_init(this->condVariable, nullptr);
    }
    //If the factory was not initilized in this interpreter.
    if (this->factory == nullptr) {
        isFactoryWasInitialized = false;
        this->factory = new CommandFromStringFactory(this, this->mutex, this->condVariable);
    }
    //A script vector that starts from the current command key word and ends at the end of the script.
    vector<string>* currentScriptVector = new vector<string>(script);
    //This pointer will be used to delete a previously current script vector at heap, which will not be needed already.
    vector<string>* pToPrevVector = currentScriptVector;
    CommandFromStringFactory factCopy(*this->factory);

    auto it = currentScriptVector->begin();
    while (it != currentScriptVector->end()) {

        currentScriptVector = new vector<string>(it, currentScriptVector->end());
        delete pToPrevVector;
        pToPrevVector = currentScriptVector;
        it = currentScriptVector->begin();

        if (factCopy.whetherWasDataServerThreadOpened()) {
            /*
             * Waiting while the server writes a data in one its iteration.
             * We stop here in order to use synhronized script symbol table.
             */
            pthread_cond_wait(this->condVariable, this->mutex);
        }
        if (factCopy.isCommand(*it, *this->symbolTable)) {

            CommandExpression *expression = factCopy.create(*currentScriptVector, this->symbolTable);
            expression->calculate();
        } else {
            throw "Syntax error! Unknown command.";
        }
        //shifting the iterator to a next command in a script.
        it += factCopy.getValueOfShiftToNextCommand();
        factCopy.deleteLastGeneretedCommandExpression();
    }

    delete currentScriptVector;
    if (!isFactoryWasInitialized) {
        this->factory->closeServerIfWasOpened();
        delete this->factory;
    }
    if (!isInitialMutexAndCondWhereInitialized) {
        pthread_mutex_destroy(this->mutex);
        pthread_cond_destroy(this->condVariable);
        delete this->mutex;
        delete this->condVariable;
    }

}

