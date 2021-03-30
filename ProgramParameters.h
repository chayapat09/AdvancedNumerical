#ifndef _PROGRAM_PARAM_INCLUDED_
#define _PROGRAM_PARAM_INCLUDED_

#include <iostream>
/*
    3.3.1 Problem Parameters and Data Structures
    Ref page 40-41
*/
struct GeomertyData {
    double xlength;
    double ylength;
    int imax;
    int jmax;
    double delx;
    double dely;
};

struct TimeSteppingData {
    double t;
    double t_end;
    double delt;
    double tau;
};

struct PressureIterationData {
    int itermax;
    int it;
    double res;
    double rps;
    double omg;
    double gamma;
};

struct ProblemParameters {
    double Re;
    double UI;
    double VI;
    double PI;
    int wW;
    int wE;
    int wN;
    int wS;
};

struct ProgramParamerters {
    GeomertyData geometryData;
    TimeSteppingData timeSteppingData;
    PressureIterationData pressureiterationData;
    ProblemParameters problemParameters;
};

// Abstract Function
// void initProblemParams(ProgramParamerters & params);





void initProblemParams(ProgramParamerters & params){
    // Initialized Problem parameters
    params.geometryData.imax = 4;
    params.geometryData.jmax = 4;
    // Ex.
    // params.geometryData.delx = 20;

} 
    
#endif