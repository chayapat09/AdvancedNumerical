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

        RHS(int x_max , int y_max) {
            this->Rhs = new FIELD<FieldDouble>(x_max , y_max);
            this->Rhs = new FIELD<FieldDouble>(x_max , y_max);
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
    std::cout << "INIT RHS" << '\n';
    // rhs.rhs = new FIELD< FieldDouble >(...)
    // Uncomment and then add to ...
}

void computeRHS(RHS & rhs , FG & fg , ProgramParamerters & params) {
        /*
            COMPUTE Rhs FIELDS using FG FIELDS and ProgramParamerters
        */
        std::cout << "Computed RHS" << '\n';
}


#endif