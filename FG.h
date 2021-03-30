#ifndef _FG_INCLUDED_
#define _FG_INCLUDED_
#include <iostream>
#include "Field.h"
#include "ProgramParameters.h"
// class FG {
//     FIELD< FieldDouble > * F;
//     FIELD< FieldDouble > * G;

//     ~FG() {
//         delete[] F;
//         delete[] G;
//     }
// };

class FG {
    public :
        FIELD< FieldDouble > * F;
        FIELD< FieldDouble > * G;

        FG() {
            this->F = nullptr;
            this->G = nullptr;
            return;
        }

        FG(int x_max , int y_max) {
            this->F = new FIELD<FieldDouble>(x_max , y_max);
            this->G = new FIELD<FieldDouble>(x_max , y_max);
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
    std::cout << "INIT FG" << '\n';
    // fg.F = new FIELD< FieldDouble >(...)
    // fg.G = new FIELD< FieldDouble >(...)
    // Uncomment and then add to ...
}

void computeFG(VelocityField & velocity ,FG & fg,  ProgramParamerters & params) {
        /*
            COMPUTE F and G FIELDS using Velocity FIELDS and ProgramParamerters
        */
        std::cout << "Computed FG" << '\n';
}


#endif