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
}


#endif