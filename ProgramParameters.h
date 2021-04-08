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
    // long long n;
};

struct PressureIterationData {
    int itermax;
    int it;
    double res;
    double eps;
    double omg;
    double gamma;
};

struct ProblemParameters {
    double Re;
    double GX;
    double GY;
    double UI;
    double VI;
    double PI;
    int wW;
    int wE;
    int wN;
    int wS;
};

struct RuntimeVariable {
    long long n;
    long long paraviewCounter;

};

struct ProgramParamerters {
    GeomertyData geometryData;
    TimeSteppingData timeSteppingData;
    PressureIterationData pressureiterationData;
    ProblemParameters problemParameters;
    RuntimeVariable runtimeVariable;
};

// Abstract Function
// void initProblemParams(ProgramParamerters & params);





void initProblemParams(ProgramParamerters & params){
    // Initialized Problem parameters
    params.geometryData.xlength = 10;
    params.geometryData.ylength = 2;
    params.geometryData.imax = 100;
    params.geometryData.jmax = 20;
    params.geometryData.delx = 0.1;
    params.geometryData.dely = 0.1;
    params.timeSteppingData.delt = 0.001;
    
    params.timeSteppingData.tau = 0.5;

    params.problemParameters.wN = 2;
    params.problemParameters.wS = 2;
    params.problemParameters.wE = 3;
    params.problemParameters.wW = 3;

    params.problemParameters.PI = 1;
    params.problemParameters.UI = 1;
    params.problemParameters.VI = 1;
    params.problemParameters.Re = 20;

    params.timeSteppingData.t_end = 100;

    params.timeSteppingData.t = 0;
    params.runtimeVariable.n = 0;
    params.runtimeVariable.paraviewCounter = 0;

    params.pressureiterationData.eps = 0.0001;
    params.pressureiterationData.itermax = 1000;
    params.pressureiterationData.omg = 1.2;
    
    params.pressureiterationData.gamma = 1;

    // Ex.
    // params.geometryData.delx = 20;

} 
    
#endif