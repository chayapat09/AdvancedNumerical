#ifndef _RHS_INCLUDED_
#define _RHS_INCLUDED_
#include <iostream>
#include "Field.h"
#include "ProgramParameters.h"
#include "FG.h"


class RHS {
    public :
        FIELD< FieldDouble > * Rhs;

        RHS() {
            this->Rhs = nullptr;
            return;
        }

        RHS(int xSize , int ySize) {
            this->Rhs = new FIELD<FieldDouble>(xSize , ySize);
            this->Rhs = new FIELD<FieldDouble>(xSize , ySize);
        }
        RHS& operator=(RHS other) {
            using std::swap;
            swap(this->Rhs , other.Rhs);

            return *this;
        }
        RHS(const RHS & other) {
           this->Rhs = new FIELD< FieldDouble > (*other.Rhs);

        }
        ~RHS() {
            delete Rhs;
        }
};

void initRHS(RHS & rhs , ProgramParamerters & params) {
    #ifdef DEBUG
    std::cout << "INIT RHS" << '\n';
    #endif
    rhs.Rhs = new FIELD<FieldDouble>(params.geometryData.imax+2 , params.geometryData.jmax+2);
    // Uncomment and then add to ...
}

void computeRHS(RHS & rhs , FG & fg , ProgramParamerters & params) {
    /*
        COMPUTE Rhs FIELDS using FG FIELDS and ProgramParamerters
    */
    #ifdef DEBUG
    std::cout << "Computed RHS" << '\n';
    #endif

    int imax = params.geometryData.imax, jmax = params.geometryData.jmax;
    double delt = params.timeSteppingData.delt, delx = params.geometryData.delx, dely = params.geometryData.dely;

    for(int i=1; i <= imax; i++){
        for(int j=1; j <= jmax; j++){

            double exp1 = ( fg.F->get(i, j).val - fg.F->get(i-1, j).val ) / delx;
            double exp2 = ( fg.G->get(i, j).val - fg.G->get(i, j-1).val ) / dely;
            double tmp = ( 1/delt ) * ( exp1 + exp2 );

            rhs.Rhs->set(i, j, tmp);

        }
    }

}


#endif