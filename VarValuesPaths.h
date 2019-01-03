//
// Created by Dorin Keshales on 2018-12-22.
//

#ifndef FIRSTMILESTONE_VARVALUESPATHS_H
#define FIRSTMILESTONE_VARVALUESPATHS_H

#include <map>
#include <vector>
using namespace std;

/**
 * This class represents a mapping bettween variables(some words) and pathes
 * in Flight-gear simulator.
 */
class VarValuesPaths {
private:
    map<string, string> paths;
public:
    static const string INDICATED_SPEED_KT;
    static const string ALTIMETER_INDICATED_ALTITUDE_FT;
    static const string ALTIMETER_PRESSURE_ALT_FT;
    static const string INDICATED_PITCH_DEG;
    static const string INDICATED_ROLL_DEG;
    static const string INTERNAL_PITCH_DEG;
    static const string INTERNAL_ROLL_DEG;
    static const string ENCODER_INDICATED_ALTITUDE_FT;
    static const string ENCODER_PRESSURE_ALT_FT;
    static const string GPS_INDICATED_ALTITUDE_FT;
    static const string INDICATED_GROUND_SPEED_KT;
    static const string INDICATED_VERTICAL_STRING;
    static const string HEADING_INDICATOR_INDICATED_HEADING_DEG;
    static const string MAGNETIC_COMPASS_INDICATED_HEADING_DEG;
    static const string INDICATED_SLIP_SKID;
    static const string INDICATED_TURN_RATE;
    static const string INDICATED_SPEED_FPM;
    static const string FLIGHT_AILERON;
    static const string FLIGHT_ELEVATOR;
    static const string FLIGHT_RUDDER;
    static const string FLIGHT_FLAPS;
    static const string ENGINE_THROTTLE;
    static const string ENGINE_RPM;

    map<string, string> GetPathsMap();
    vector<string>  split(string s);
    void SetPath(string var, string newPath);

    string GetPath(string var);

    bool isPathExist(string var);

    void AddPathOfNewVar(string var, string path);

    void loadMap();

    void saveMap();

    vector<string> getVariablesOfPath(string path);
};


#endif //FIRSTMILESTONE_VARVALUESPATHS_H
