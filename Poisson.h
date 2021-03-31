#ifndef _POISSION_INCLUDED_
#define _POISSION_INCLUDED_

#include "Field.h"
#include "RHS.h"
#include "ProgramParameters.h"
#include "eX.h"

#include <iostream>

double dAbs(double d) {
    return d > 0 ? d : -d;
}

double max_norm(FIELD<FieldDouble> & f , ProgramParamerters & params) {
    double max_norm = std::abs(f[1][1].val);
    for (int i = 1 ; i <= params.geometryData.imax ; i++) {
        for (int j = 1 ; j <= params.geometryData.jmax ; j++) {
            max_norm = std::max(max_norm , dAbs(f[i][j].val));
        }
    }
    return max_norm;
}

void poission(PressureField & pressure , RHS & rhs , ProgramParamerters &params ) {
    
    /*
        iteration for the pressure Poisson equation according to (3.44). 
        The iteration is terminated once the residual norm res drops below the tolerance limit eps 
        (absolute or relative, multiplied by the norm of the initial pressure) or once the maximal 
        number of iterations i termax is reached. Upon completion, the number of steps taken is returned 
        and the current residual norm is stored in res. 
    */
    PressureField pIT(pressure);
    // PressureField pIT_Next(pressure);
    FIELD<FieldDouble> & pTmp = *pIT.p;

    for (int it = 1 ; it <= params.pressureiterationData.itermax ; it++) {

        /*
            Calculate r(it)[i][j] 
        */

        FIELD<FieldDouble> r(pressure.p->getXSize() , pressure.p->getYSize());
        for (int i = 1 ; i <= params.geometryData.imax ; i++) {
            for (int j = 1 ; j <= params.geometryData.jmax ; j++) {
                /*
                    Equation (3.45)
                */
                double expression1 = ( 
                      eE(i , params) * (pTmp[i+1][j].val - pTmp[i][j].val  ) 
                    - eW(i , params) * (pTmp[i][j].val   - pTmp[i-1][j].val) ) 
                    / (params.geometryData.delx * params.geometryData.delx);

                double expression2 = (eN(j, params) * (pTmp[i][j+1].val - pTmp[i][j].val) - eS(j , params) * (pTmp[i][j].val - pTmp[i][j-1].val)) / (params.geometryData.dely*params.geometryData.dely);

                double merge = expression1 + expression2 - rhs.Rhs->get(i,j).val;
                r[i][j].val = merge;
                // std::cout << merge << '\n';
            }
        }

        /*
            Now We has 2 methods of Norm to use (3.46) and (3.47)
            In this implementation we use maximum norm
        */

        double r_inf = max_norm(r , params);

        /* Not Sure of using p(it) to find norm in book says use p(0)
        */

        FIELD<FieldDouble> & p0 = *pressure.p;
        double p_inf = max_norm(p0 , params);

        // Update res
        params.pressureiterationData.res = r_inf;
        
        // Break due to r
        if (r_inf < params.pressureiterationData.eps || r_inf < params.pressureiterationData.eps * p_inf) {
            #ifdef _DEBUG_
            std::cout << "SOR Break condition reached" << '\n';
            #endif
            break;
        }

        /*
            If the pressure boundary values are treated using the second method, 
            then the boundary values must be set according to (3.48) prior to each iteration step.
            p(it+1)[..][..] = p(it)[..][..] (3.48)
        */
        for (int j = 1 ; j <= params.geometryData.jmax ; j++) {
            pTmp[0][j].val = pTmp[1][j].val;
            pTmp[params.geometryData.imax + 1][j].val = pTmp[params.geometryData.imax][j].val;
        }

        for (int i = 1 ; i <= params.geometryData.imax ; i++) {
            pTmp[i][0].val = pTmp[i][1].val;
            pTmp[i][params.geometryData.jmax + 1].val = pTmp[i][params.geometryData.jmax].val;
        }


        // SOR

        for (int i = 1 ; i <= params.geometryData.imax ; i++) {
            for (int j = 1 ; j <= params.geometryData.jmax ; j++) {
                /*
                    Equation (3.44)
                */
                double expresstion1 = (1 - params.pressureiterationData.omg) * pTmp[i][j].val;
                double expresstion2 = params.pressureiterationData.omg 
                                    / ( 
                                          (eE(i , params) + eW(i , params ) )    /  ( params.geometryData.delx * params.geometryData.delx ) 
                                        + (eN(j , params) + eS(j , params ) )    /  ( params.geometryData.dely * params.geometryData.dely ) 
                                        );
                double expresstion3 = (eE(i , params) * pTmp[i+1][j].val + eW(i , params) * pTmp[i-1][j].val) / (params.geometryData.delx * params.geometryData.delx);
                double expresstion4 = (eN(j , params) * pTmp[i][j+1].val + eS(j , params) * pTmp[i][j-1].val) / (params.geometryData.dely * params.geometryData.dely);

                double merge = expresstion1 + expresstion2 * (expresstion3 + expresstion4 - rhs.Rhs->get(i,j).val );

                pTmp[i][j].val = merge;
                // std::cout << merge << '\n';
           }
        }

    }

    // Set Pressure to new Pressure
    pressure = pIT;


}

#endif