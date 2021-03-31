#ifndef _eX_INCLUDED
#define _eX_INCLUDED

#include "ProgramParameters.h"

double eW(int i , ProgramParamerters & params) {
    if (i == 1) return 0;
    else if (i > 1) return 1;
    else {
        throw "eW index Error!";
    }
}

double eE(int i , ProgramParamerters & params) {
    if (i < params.geometryData.imax) return 1;
    else if (i == params.geometryData.imax) return 0;
    else {
        throw "eE index Error!";
    }
}

double eS(int j , ProgramParamerters & params) {
    if (j == 1) return 0;
    else if (j > 1) return 1;
    else {
        throw "eS index Error!";
    }
}

double eN(int j , ProgramParamerters & params) {
    if (j < params.geometryData.jmax) return 1;
    else if (j == params.geometryData.jmax) return 0;
    else {
        throw "eW index Error!";
    }
}

#endif