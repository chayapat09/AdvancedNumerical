#include <iostream>

#define _DEBUG_

#include "../../ProgramParameters.h"
#include "../../Poisson.h"

using namespace std;


int main() {
    PressureField p(5,5);
    RHS rhs(5,5);
    ProgramParamerters po;
    po.geometryData.imax = 3;
    po.geometryData.jmax = 3;
    po.pressureiterationData.eps = 0.0001;
    po.pressureiterationData.itermax = 200;
    po.pressureiterationData.omg = 1.2;

    po.geometryData.delx = 0.01;
    po.geometryData.dely = 0.01;
    for (int i = 0 ; i < 5 ; i++) {
        for (int j = 0 ; j < 5 ; j++) {
            // rhs.Rhs->set(i,j,1);
        }
    }
    poission(p , rhs , po);

    p.p->printField();
}