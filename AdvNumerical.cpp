#include <iostream>
#include <fstream>

#define DEBUG

#include "ProgramParameters.h"
#include "Field.h"
#include "FG.h"
#include "RHS.h"
#include "Poisson.h"
#include "./utils/ProgressBar.h"
// using namespace std; 

/* Discramer
    Only Pass by References to Other function
    DONOT USE NAMESPACE DUETO CODE REUSEABLE WILL LOW // using namespace std; <- BAD PRACTICE
    Field Value Type is Double by Default
*/

/*
    The stepsize delt for the next time step is calculated according to (3.50). In case of negative tau the stepsize read in
    READ-PARAMETER is to be used.
*/

void computeDelt(VelocityField &velocity, ProgramParamerters & params){
    double tau = params.timeSteppingData.tau, Re = params.problemParameters.Re;
    double delx = params.geometryData.delx, dely = params.geometryData.dely;
    double absUmax = velocity.u->findAbsoluteMax();
    double absVmax = velocity.v->findAbsoluteMax();
    
    //exp is a short term for expression
    double exp1 = (Re/2.) * ( 1./ ( 1. / ( delx*delx ) + 1. / ( dely*dely ) ) );
    double exp2 = delx/absUmax;
    double exp3 = dely/absVmax;
    params.timeSteppingData.delt = tau* std::min( exp1, std::min( exp2, exp3 ) );
}

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
    #ifdef DEBUG
    std::cout << "Velocity Field Are updated!" << '\n';
    #endif

    int imax = params.geometryData.imax, jmax = params.geometryData.jmax;
    double delt = params.timeSteppingData.delt, delx = params.geometryData.delx, dely = params.geometryData.dely;

    //set new u
    for(int i=1; i <= imax-1; i++){
        for(int j=1; j <= jmax; j++){
            double new_u = fg.F->get(i, j).val - ( delt/delx ) * \
                           ( pressure.p->get(i+1, j).val - pressure.p->get(i, j).val );
                           
            velocity.u->set(i, j, new_u);             
        }
    }

    //set new v
    for(int i=1; i <= imax; i++){
        for(int j=1; j <= jmax-1; j++){
            double new_v = fg.G->get(i, j).val - ( delt/dely ) * \
                           ( pressure.p->get(i, j+1).val - pressure.p->get(i, j).val );
            
            velocity.v->set(i, j, new_v);
        }
    }

}

void saveParaview(VelocityField & velocityField , PressureField & pressureField ,ProgramParamerters & params ) {
    // Write Pressure Field
    std::ofstream f;
    f.open("./paraview/P_" + std::to_string(params.runtimeVariable.paraviewCounter) + ".vtk");
    pressureField.p->paraview_VTK(f , params);
    f.close();
    
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

    // Assume const delt
    uint32_t checkPointPeriod = (programParameter.timeSteppingData.t_end / programParameter.timeSteppingData.delt) / 1000;
    checkPointPeriod = std::max(checkPointPeriod , 1u);

    for (; programParameter.timeSteppingData.t <= programParameter.timeSteppingData.t_end ; 
            programParameter.timeSteppingData.t += programParameter.timeSteppingData.delt) {

        // 3.COMP_DELT
        // computeDelt(pressureField, programParameter);

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
        // Note : pressureField is updated in here
        poission(pressureField , rhs , programParameter);

        // 9.ADAP_UV
        updateVelocityField(velocityField , fg , pressureField , programParameter);

        programParameter.runtimeVariable.n++;

        #ifndef DEBUG

        if (programParameter.runtimeVariable.n % checkPointPeriod == 0) {
            showProgress(programParameter);
            saveParaview(velocityField , pressureField , programParameter);
            programParameter.runtimeVariable.paraviewCounter++;
            // Neet to be at Last Scope Execution
            // saveCheckPoint(velocityField , pressureField , programParameter ); 
        }
        #endif
    }
    
}