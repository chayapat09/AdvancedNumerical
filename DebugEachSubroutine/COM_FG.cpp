#include <iostream>

#define DEBUG

#include "../ProgramParameters.h"
#include "../Field.h"
#include "../FG.h"
#include "../RHS.h"

using namespace std;

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

int main() {
    
    ProgramParamerters programParameter;
    initProblemParams(programParameter);

    programParameter.geometryData.xlength = 11;
    programParameter.geometryData.ylength = 17;
    programParameter.geometryData.imax = 9;
    programParameter.geometryData.jmax = 15;

    VelocityField uv(11, 17);
    uv.u->setAll(1);
    for(int i=0; i < 11; i++){
        uv.u->set(i, 0, -1);
        uv.u->set(i, 16, -1);
    }
    uv.v->setAll(0);

    FG fg(11, 17);
    fg.F->setAll(0);
    fg.G->setAll(0);

    cout << "Before\n";
    cout << "u\n";
    uv.u->printField();
    cout << "v\n";
    uv.v->printField();
    cout << "F\n";
    fg.F->printField();
    cout << "G\n";
    fg.G->printField();

    computeFG(uv, fg, programParameter);

    cout << "After\n";
    // fg.F->printField();
    // fg.G->printField();
    cout << "u\n";
    uv.u->printField();
    cout << "v\n";
    uv.v->printField();
    cout << "F\n";
    fg.F->printField();
    cout << "G\n";
    fg.G->printField();

    //----------------------------------------------------------------------------------------------------------------------------
    //compute rhs
    RHS rhs(11, 17);

    computeRHS(rhs, fg, programParameter);
    cout << "Show rhs\n";
    rhs.Rhs->printField();

    //----------------------------------------------------------------------------------------------------------------------------
    //compute new u and v
    PressureField pf(11, 17);
    pf.p->setAll(2);
    cout << "Before\n";
    cout << "u\n";
    uv.u->printField();
    cout << "v\n";
    uv.v->printField();
    
    updateVelocityField(uv, fg, pf, programParameter);

    cout << "After\n";
    cout << "u\n";
    uv.u->printField();
    cout << "v\n";
    uv.v->printField();


}