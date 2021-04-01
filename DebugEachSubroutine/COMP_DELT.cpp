#include <iostream>

#define _DEBUG_

#include "../ProgramParameters.h"
#include "../Field.h"

using namespace std;

void computeDelt(VelocityField &velocity, ProgramParamerters & params){
    double tau = params.timeSteppingData.tau, Re = params.problemParameters.Re;
    double delx = params.geometryData.delx, dely = params.geometryData.dely;
    double absUmax = velocity.u->findAbsoluteMax();
    double absVmax = velocity.v->findAbsoluteMax();
    
    //exp is a short term for expression
    double exp1 = (Re/2) * ( 1/ ( 1 / ( delx*delx ) + 1 / ( dely*dely ) ) );
    double exp2 = delx/absUmax;
    double exp3 = dely/absVmax;
    params.timeSteppingData.delt = tau* std::min( exp1, std::min( exp2, exp3 ) );
}

int main() {
    
    // FIELD<FieldDouble> u(4,4);
    // u.setAll(3);
    // u.printField();

    // u.set(2, 2, 10);
    // cout << "The maximum value in the field is " << u.findMax() << " " << u.findAbsoluteMax() << "\n";
    // u.set(1,3, -100);
    // cout << "The maximum value in the field is " << u.findMax() << " " << u.findAbsoluteMax() << "\n";
    
    ProgramParamerters programParameter;
    initProblemParams(programParameter);
    VelocityField uv(3,3);
    uv.u->setAll(4);
    uv.v->setAll(6);
    cout << "delt before = " << programParameter.timeSteppingData.delt << "\n";
    computeDelt(uv, programParameter);
    cout << "delt after = " << programParameter.timeSteppingData.delt << "\n";

}