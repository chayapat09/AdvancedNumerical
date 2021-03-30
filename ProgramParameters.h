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

struct ProgramParamerters {
    GeomertyData geometryData;
    TimeSteppingData timeSteppingData;
    PressureIterationData pressureiterationData;
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