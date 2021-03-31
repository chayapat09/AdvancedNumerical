#include <iostream>
#include <vector>

#include "ProgramParameters.h"
#include "Field.h"
#include "FG.h"
#include "RHS.h"
#include "Poisson.h"
// using namespace std; 

/* Discramer
    Only Pass by References to Other function
    DONOT USE NAMESPACE DUETO CODE REUSEABLE WILL LOW // using namespace std; <- BAD PRACTICE
    Field Value Type is Double by Default
*/



/*
The boundary values for the arrays U and V are set depending on the boundary 
data parameters wW,wE,wN,wS according to the formulas in Section 3.1.2.
*/
void setBoundaryCondition(VelocityField &velocity , ProgramParamerters & params) {
    
}


/*
Here , specificboundary conditions (such as inflow boundary conditions) of the problem 
specified by the parameter problem can be set. It is also possible to redefine 
the bound- ary data on parts of a boundary which has been previously assigned a boundary condition 
by one of the flags wW, wE, wN, or wS (for example, a small in or outflow area within a solid wall).
*/
void setSpecificBoundaryCondition(VelocityField &velocity , ProgramParamerters & params) {

}

/*
    The new velocities are calculated according to (3.34) and (3.35).
*/
void updateVelocityField(VelocityField & velocity ,FG & fg , PressureField & pressure , ProgramParamerters & params ) {
    std::cout << "Velocity Field Are upadted!" << '\n';
}

int main() {

    
    // Programs flow coressponding to 3.3.2 The Program on page 42-43
    
    // 1.READ_PARAMETER // INIT PARAMS
    ProgramParamerters programParameter;
    initProblemParams(programParameter);

    // 2.INIT_UVP
    VelocityField velocityField;
    PressureField pressureField;

    INIT_UVP(velocityField , pressureField , programParameter);

    // 3.COMP_DELT
    // ?? 


    for (int i = 0 ; i < 1 ; i++) {
        // 4.SETBCOND
        setBoundaryCondition(velocityField , programParameter);

        // 5.SETSPECBCOND
        setSpecificBoundaryCondition(velocityField , programParameter);


        // 6.COMP_FG
        FG fg;
        initFG(fg , programParameter);
        computeFG(velocityField , fg , programParameter);

        // 7.COMP_RHS
        RHS rhs;
        initRHS(rhs , programParameter);
        computeRHS(rhs ,fg ,  programParameter);

        // 8.POISSON
        PressureField res;
        initRes(res , programParameter);
        poission(pressureField , rhs , res , programParameter);

        // 9.ADAP_UV
        updateVelocityField(velocityField , fg , res , programParameter);

    }

    
}