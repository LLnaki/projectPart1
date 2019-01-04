//
// Created by Dorin Keshales on 2018-12-22.
//

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "VarValuesPaths.h"

#define VAR_PATHS_FILE "./VariablesLocationPath.txt"
const string VarValuesPaths::INDICATED_SPEED_KT = "/instrumentation/airspeed-indicator/indicated-speed-kt";
const string VarValuesPaths::ALTIMETER_INDICATED_ALTITUDE_FT = "/instrumentation/altimeter/indicated-altitude-ft";
const string VarValuesPaths::ALTIMETER_PRESSURE_ALT_FT = "/instrumentation/altimeter/pressure-alt-ft";
const string VarValuesPaths::INDICATED_PITCH_DEG = "/instrumentation/attitude-indicator/indicated-pitch-deg";
const string VarValuesPaths::INDICATED_ROLL_DEG = "/instrumentation/attitude-indicator/indicated-roll-deg";
const string VarValuesPaths::INTERNAL_PITCH_DEG = "/instrumentation/attitude-indicator/internal-pitch-deg";
const string VarValuesPaths::INTERNAL_ROLL_DEG = "/instrumentation/attitude-indicator/internal-roll-deg";
const string VarValuesPaths::ENCODER_INDICATED_ALTITUDE_FT = "/instrumentation/encoder/indicated-altitude-ft";
const string VarValuesPaths::ENCODER_PRESSURE_ALT_FT = "/instrumentation/encoder/pressure-alt-ft";
const string VarValuesPaths::GPS_INDICATED_ALTITUDE_FT = "/instrumentation/gps/indicated-altitude-ft";
const string VarValuesPaths::INDICATED_GROUND_SPEED_KT = "/instrumentation/gps/indicated-ground-speed-kt";
const string VarValuesPaths::INDICATED_VERTICAL_STRING = "/instrumentation/gps/indicated-vertical-speed";
const string VarValuesPaths::HEADING_INDICATOR_INDICATED_HEADING_DEG = "/instrumentation/heading-indicator/indicated-heading-deg";
const string VarValuesPaths::MAGNETIC_COMPASS_INDICATED_HEADING_DEG = "/instrumentation/magnetic-compass/indicated-heading-deg";
const string VarValuesPaths::INDICATED_SLIP_SKID = "/instrumentation/slip-skid-ball/indicated-slip-skid";
const string VarValuesPaths::INDICATED_TURN_RATE = "/instrumentation/turn-indicator/indicated-turn-rate";
const string VarValuesPaths::INDICATED_SPEED_FPM = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
const string VarValuesPaths::FLIGHT_AILERON = "/controls/flight/aileron";
const string VarValuesPaths::FLIGHT_ELEVATOR = "/controls/flight/elevator";
const string VarValuesPaths::FLIGHT_RUDDER = "/controls/flight/rudder";
const string VarValuesPaths::FLIGHT_FLAPS = "/controls/flight/flaps";
const string VarValuesPaths::ENGINE_THROTTLE = "/controls/engines/current-engine/throttle";
const string VarValuesPaths::ENGINE_RPM = "/engines/engine/rpm";

/*
 * Generic implementation to search if a given value exists in a map or not.
 * Adds all the keys with given value in the vector
 */
template<typename K, typename V>
bool findByValue(std::vector<K> &vec, std::map<K, V> mapOfElemen, V value) {
    bool bResult = false;
    auto it = mapOfElemen.begin();
    // Iterate through the map
    while (it != mapOfElemen.end()) {
        // Check if value of this entry matches with given value
        if (it->second == value) {
            // Yes found
            bResult = true;
            // Push the key in given map
            vec.push_back(it->first);
        }
        // Go to next entry in map
        it++;
    }
    return bResult;
}

/**
 * function which similar to the stoi function of string in java.
 *
 * @param s the requested string ti split.
 * @param delim delimiter.
 * @return a vector which holds the substrings which the comma was in between.
 */
vector<string>VarValuesPaths::split(string s) {
    stringstream ss(s);
    string item;
    char p = ',';
    vector<string> words;
    while (getline(ss, item, p)) {
        words.push_back(item);
    }
    return words;
}

map<string, string> VarValuesPaths::GetPathsMap() {
    return this->paths;
}

void VarValuesPaths::SetPath(string var, string newPath) {

    this->paths[var] = newPath;

}


string VarValuesPaths::GetPath(string var) {
    std::map<string, string>::iterator it;
    it = this->paths.find(var);
    if (it != this->paths.end()) {
        return this->paths[var];
    } else {
        throw "Var was not found - can't get the location path of a non existing var";
    }
}

bool VarValuesPaths::isPathExist(string var) {
    std::map<string, string>::iterator it;
    it = this->paths.find(var);
    return it != this->paths.end();
}

void VarValuesPaths::AddPathOfNewVar(string var, string path) {
    this->paths[var] = path;
}


void VarValuesPaths::loadMap() {
    ifstream variablesLocationPath;
    // Opening the VAR_PATHS_FILE file.
    variablesLocationPath.open(VAR_PATHS_FILE, ios::in);
    map<string, string> p;
    string line, varName, path;

    // As long as we still have lines to read from the file.
    while (getline(variablesLocationPath, line)) {
        // Splitting the line into the variable's name and it's path.
        auto v = split(line);
        varName = v[0];
        path = v[1];

        this->paths[varName] = path;
    }

    // Closing the VAR_PATHS_FILE file.
    variablesLocationPath.close();
}

void VarValuesPaths::saveMap() {
    ofstream variablesLocationPath;
    // Opening the VAR_PATHS_FILE file.
    variablesLocationPath.open(VAR_PATHS_FILE, ios::trunc);    // delete all file content

    // Saving all the variables and their paths to the DB file.
    for (auto &v: this->paths) {
        variablesLocationPath << v.first << "," << v.second << endl;
    }

    // Closing the VAR_PATHS_FILE file.
    variablesLocationPath.close();
}

vector<string> VarValuesPaths::getVariablesOfPath(string path) {
    vector<string> variables;
    findByValue(variables, this->GetPathsMap(), path);
    return variables;
}
