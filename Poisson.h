#include "Field.h"
#include "RHS.h"
#include "ProgramParameters.h"
#include <iostream>

void initRes(PressureField & res , ProgramParamerters & params) {
    // Init res
}

void poission(PressureField & pressure , RHS & rhs ,PressureField & res , ProgramParamerters &params ) {
    std::cout << "Compute Poission" << '\n';
}