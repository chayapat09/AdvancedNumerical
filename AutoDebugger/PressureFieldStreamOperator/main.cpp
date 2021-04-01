#include <iostream>
#include <fstream>
#include <assert.h>

#define DEBUG
#include "../../Field.h"
using namespace std;




void PressureFieldStreamOperatorSubTest1() {
    PressureField pres(10,20);
    FIELD<FieldDouble> & u = *pres.p;

    for (int x = 0 ; x < u.getXSize() ; x++) {
        for(int y = 0 ; y < u.getYSize() ; y++) {
            if (x - y == 0 || x + y == 9) {
                u.set(x,y , 1.234234);
            }
        }
    }

    
    ofstream myfile;
    myfile.open("generatePressure.txt");
    myfile << pres;
    myfile.close();

    ifstream myfile2;
    myfile2.open("generatePressure.txt");

    PressureField pres2;
    myfile2 >> pres2;
    myfile2.close();
    
    // Automated Tested
    assert(pres.p->getXSize() == pres2.p->getXSize());
    assert(pres.p->getYSize() == pres2.p->getYSize());
    for (int x = 0 ; x < pres.p->getXSize() ; x++) {
        for(int y = 0 ; y < pres.p->getYSize() ; y++) {
            assert(abs(pres.p->get(x,y).val - pres2.p->get(x,y).val) < 1e-3);
        }
    }
}

void PressureFieldStreamOperatorSubTest2(){
    PressureField pres(103,105);
    FIELD<FieldDouble> & u = *pres.p;

    for (int x = 0 ; x < u.getXSize() ; x++) {
        for(int y = 0 ; y < u.getYSize() ; y++) {
            u.set(x,y , x*x + 0.382*x+y + 0.348*y + y*y);
        }
    }
    // cout << u[0][31].val << '\n';

    // cout << pres;
    
    ofstream myfile;
    myfile.open("generatePressure.txt");
    myfile << pres;
    myfile.close();

    ifstream myfile2;
    myfile2.open("generatePressure.txt");

    PressureField pres2;
    myfile2 >> pres2;
    myfile2.close();
    
    // cout << pres2.p->get(0,31).val << '\n';
    // Automated Tested
    assert(pres.p->getXSize() == pres2.p->getXSize());
    assert(pres.p->getYSize() == pres2.p->getYSize());
    for (int x = 0 ; x < pres.p->getXSize() ; x++) {
        for(int y = 0 ; y < pres.p->getYSize() ; y++) {
            // if (abs(pres.p->get(x,y).val - pres2.p->get(x,y).val) >= 1e-3) cout << x << ' ' << y << '\n';
            assert(abs(pres.p->get(x,y).val - pres2.p->get(x,y).val) < 1e-5);
        }
    }
}

void PressureFieldStreamOperatorSubTest3(){
    PressureField pres(97,101);
    FIELD<FieldDouble> & u = *pres.p;

    for (int x = 0 ; x < u.getXSize() ; x++) {
        for(int y = 0 ; y < u.getYSize() ; y++) {
            u.set(x,y , (x*x + 0.382*x+y + 0.348*y + y*y) / 1e5);
        }
    }
    // cout << u[0][31].val << '\n';

    // cout << pres;
    
    ofstream myfile;
    myfile.open("generatePressure.txt");
    myfile << pres;
    myfile.close();

    ifstream myfile2;
    myfile2.open("generatePressure.txt");

    PressureField pres2;
    myfile2 >> pres2;
    myfile2.close();
    
    // cout << pres2.p->get(0,31).val << '\n';
    // Automated Tested
    assert(pres.p->getXSize() == pres2.p->getXSize());
    assert(pres.p->getYSize() == pres2.p->getYSize());
    for (int x = 0 ; x < pres.p->getXSize() ; x++) {
        for(int y = 0 ; y < pres.p->getYSize() ; y++) {
            // if (abs(pres.p->get(x,y).val - pres2.p->get(x,y).val) >= 1e-3) cout << x << ' ' << y << '\n';
            assert(abs(pres.p->get(x,y).val - pres2.p->get(x,y).val) < 1e-5);
        }
    }
}



#ifdef AUTOMATED_TEST
void PressureFieldStreamOperatorTest() {
#else
int main () {
#endif
    
    PressureFieldStreamOperatorSubTest1();
    PressureFieldStreamOperatorSubTest2();
    PressureFieldStreamOperatorSubTest3();

}
