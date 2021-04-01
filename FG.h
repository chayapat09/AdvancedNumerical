#ifndef _FG_INCLUDED_
#define _FG_INCLUDED_
#include <iostream>
#include "Field.h"
#include "ProgramParameters.h"

class FG {
    public :
        FIELD< FieldDouble > * F;
        FIELD< FieldDouble > * G;

        FG() {
            this->F = nullptr;
            this->G = nullptr;
            return;
        }

        FG(int xSize , int ySize) {
            this->F = new FIELD<FieldDouble>(xSize , ySize);
            this->G = new FIELD<FieldDouble>(xSize , ySize);
        }
        FG(const FG & other) {
            F = new FIELD< FieldDouble > (*other.F);
            G = new FIELD< FieldDouble > (*other.G);
        }

        FG& operator=(FG other) {
            using std::swap;
            swap(this->F , other.F);
            swap(this->G , other.G);

            return *this;
        }
        ~FG() {
            delete F;
            delete G;
        }
};

void initFG(FG & fg , ProgramParamerters & params) {
    #ifdef DEBUG
    std::cout << "INIT FG" << '\n';
    #endif
    // fg.F = new FIELD< FieldDouble >(...)
    // fg.G = new FIELD< FieldDouble >(...)
    // Uncomment and then add to ...
}

void computeFG(VelocityField & velocity ,FG & fg,  ProgramParamerters & params) {
    /*
        COMPUTE F and G FIELDS using Velocity FIELDS and ProgramParamerters
    */
    #ifdef DEBUG
    std::cout << "Computed FG" << '\n';
    #endif

    int imax = params.geometryData.imax, jmax = params.geometryData.jmax;

    //boundary condition (3.42)
    for(int j=1; j <= jmax; j++){
        (fg.F)->set(0, j, velocity.u->get(0, j).val );
        (fg.F)->set(imax, j, velocity.u->get(imax, j).val );
    }
    for(int i=1; i <= imax; i++){
        (fg.G)->set(i, 0, velocity.v->get(i, 0).val );
        (fg.G)->set(i, jmax, velocity.v->get(i, jmax).val );
    }

    // (3.36) Compute F
    double delt = params.timeSteppingData.delt, delx = params.geometryData.delx, dely = params.geometryData.dely;
    double GX = params.problemParameters.GX, GY = params.problemParameters.GY;
    double gamma = params.pressureiterationData.gamma, Re = params.problemParameters.Re;

    for(int i=1; i <= imax-1; i++){
        for(int j=1; j <= jmax; j++){
            double exp1 = ( velocity.u->get(i+1,j).val - 2.* velocity.u->get(i, j).val + velocity.u->get(i-1,j).val ) / ( delx*delx );
            double exp2 = ( velocity.u->get(i, j+1).val - 2.*velocity.u->get(i, j).val + velocity.u->get(i, j-1).val ) / ( dely*dely );

            double exp3_1 = ( velocity.u->get(i, j).val + velocity.u->get(i+1, j).val ) / 2.;
            double exp3_2 = ( velocity.u->get(i-1, j).val + velocity.u->get(i, j).val ) / 2.;
            double exp3_3 = ( std::abs( exp3_1 ) ) * \
                            ( ( velocity.u->get(i, j).val - velocity.u->get(i+1, j).val ) / 2. );
            double exp3_4 = ( std::abs( exp3_2 ) ) * \
                            ( ( velocity.u->get(i-1, j).val - velocity.u->get(i, j).val ) / 2. );
            double exp3 = ( 1/delx ) * ( exp3_1*exp3_1 - exp3_2*exp3_2 ) + \
                          ( gamma/delx ) * ( exp3_3 - exp3_4 );

            double exp4_1 = ( ( velocity.v->get(i, j).val + velocity.v->get(i+1, j).val )/2. ) * \
                            ( ( velocity.u->get(i, j).val + velocity.u->get(i, j+1).val )/ 2. );
            double exp4_2 = ( ( velocity.v->get(i, j-1).val + velocity.v->get(i+1, j-1).val )/2. ) * \
                            ( ( velocity.u->get(i, j-1).val + velocity.u->get(i, j).val )/2. );
            double exp4_3 = ( std::abs( velocity.v->get(i, j).val + velocity.v->get(i+1, j).val )/2. ) * \
                            ( ( velocity.u->get(i, j).val - velocity.u->get(i, j+1).val )/2. );
            double exp4_4 = ( std::abs( velocity.v->get(i, j-1).val + velocity.v->get(i+1, j-1).val )/2. ) * \
                            ( ( velocity.u->get(i, j-1).val - velocity.u->get(i, j).val )/2. );
            double exp4 = ( 1/dely ) * ( exp4_1 - exp4_2 ) + \
                          ( gamma/dely ) * ( exp4_3 - exp4_4 );
            
            double tmp = velocity.u->get(i, j).val + \
                         delt*( (1/Re) * ( exp1 + exp2 ) - exp3 - exp4 + GX );           
            fg.F->set(i, j, tmp);

        }
    }

    //(3.37) Compute G
    for(int i=1; i <= imax; i++){
        for(int j=1; j <= jmax-1; j++){
            double exp1 = ( velocity.v->get(i+1, j).val - 2.*velocity.v->get(i, j).val + velocity.v->get(i-1, j).val ) / (delx*delx);
            double exp2 = ( velocity.v->get(i, j+1).val - 2*velocity.v->get(i, j).val + velocity.v->get(i, j-1).val ) / (dely*dely);

            double exp3_1 = ( ( velocity.u->get(i, j).val + velocity.u->get(i, j+1).val )/2. ) * \
                            ( ( velocity.v->get(i, j).val + velocity.v->get(i+1, j).val )/ 2. );
            double exp3_2 = ( ( velocity.u->get(i-1, j).val + velocity.u->get(i-1, j+1).val )/2. ) * \
                            ( ( velocity.v->get(i-1, j).val + velocity.v->get(i, j).val )/ 2. );
            double exp3_3 = ( std::abs( velocity.u->get(i, j).val + velocity.u->get(i, j+1).val )/2. ) * \
                            ( ( velocity.v->get(i, j).val - velocity.v->get(i+1, j).val )/ 2. );
            double exp3_4 = ( std::abs( velocity.u->get(i-1, j).val + velocity.u->get(i-1, j+1).val )/2. ) * \
                            ( ( velocity.v->get(i-1, j).val + velocity.v->get(i, j).val )/ 2. );
            double exp3 = (1/delx) * ( exp3_1 - exp3_2 ) + (gamma/delx)*( exp3_3 - exp3_4 );

            double exp4_1 = ( velocity.v->get(i, j).val + velocity.v->get(i, j+1).val ) / 2;
            double exp4_2 = ( velocity.v->get(i, j-1).val + velocity.v->get(i, j).val ) / 2;
            double exp4_3 = ( std::abs( velocity.v->get(i, j).val + velocity.v->get(i, j+1).val )/2. ) * \
                            ( ( velocity.v->get(i, j).val - velocity.v->get(i, j+1).val )/ 2. );
            double exp4_4 = ( std::abs( velocity.v->get(i, j-1).val + velocity.v->get(i, j).val )/2. ) * \
                            ( ( velocity.v->get(i, j-1).val - velocity.v->get(i, j).val )/ 2. );
            double exp4 = (1/dely) * ( exp4_1*exp4_1 - exp4_2*exp4_2 ) + \
                          (gamma/dely) * ( exp4_3 - exp4_4 );

            double tmp = velocity.v->get(i, j).val + \
                         delt*( (1/Re) * ( exp1 + exp2 ) - exp3 - exp4 + GY );           
            fg.G->set(i, j, tmp);

        }
    }

}


#endif