#include <iostream>
#include <fstream>
#include <assert.h>

#define DEBUG
#include "../../Field.h"
using namespace std;




void VelocityFieldStreamOperatorSubTest1() {
    VelocityField vel(10,20);
    FIELD<FieldDouble> & u = *vel.u;
    FIELD<FieldDouble> & v = *vel.v;

    for (int x = 0 ; x < u.getXSize() ; x++) {
        for(int y = 0 ; y < u.getYSize() ; y++) {
            if (x - y == 0 || x + y == 9) {
                u.set(x,y , 1.234234);
            }
        }
    }

    for (int x = 0 ; x < v.getXSize() ; x++) {
        for(int y = 0 ; y < v.getYSize() ; y++) {
            if (x - y == 2 || x + y == 10) {
                v.set(x,y , 19.23423);
            }
        }
    }
    
    ofstream myfile;
    myfile.open("generateVelocity.txt");
    myfile << vel;
    myfile.close();

    ifstream myfile2;
    myfile2.open("generateVelocity.txt");

    VelocityField vel2;
    myfile2 >> vel2;
    myfile2.close();
    
    // Automated Tested
    assert(vel.u->getXSize() == vel2.u->getXSize());
    assert(vel.u->getYSize() == vel2.u->getYSize());
    assert(vel.v->getXSize() == vel2.v->getXSize());
    assert(vel.v->getYSize() == vel2.v->getYSize());
    for (int x = 0 ; x < vel.u->getXSize() ; x++) {
        for(int y = 0 ; y < vel.u->getYSize() ; y++) {
            assert(abs(vel.u->get(x,y).val - vel2.u->get(x,y).val) < 1e-3);
            assert(abs(vel.v->get(x,y).val - vel2.v->get(x,y).val) < 1e-3);
        }
    }
}

void VelocityFieldStreamOperatorSubTest2(){
    VelocityField vel(103,105);
    FIELD<FieldDouble> & u = *vel.u;
    FIELD<FieldDouble> & v = *vel.v;

    for (int x = 0 ; x < u.getXSize() ; x++) {
        for(int y = 0 ; y < u.getYSize() ; y++) {
            u.set(x,y , x*x + 0.382*x+y + 0.348*y + y*y);
        }
    }
    // cout << u[0][31].val << '\n';

    for (int x = 0 ; x < v.getXSize() ; x++) {
        for(int y = 0 ; y < v.getYSize() ; y++) {
            v.set(x,y , -x*x - 0.211*x*y + 0.324*y + y*y);
        }
    }
    // cout << vel;
    
    ofstream myfile;
    myfile.open("generateVelocity.txt");
    myfile << vel;
    myfile.close();

    ifstream myfile2;
    myfile2.open("generateVelocity.txt");

    VelocityField vel2;
    myfile2 >> vel2;
    myfile2.close();
    
    // cout << vel2.u->get(0,31).val << '\n';
    // Automated Tested
    assert(vel.u->getXSize() == vel2.u->getXSize());
    assert(vel.u->getYSize() == vel2.u->getYSize());
    assert(vel.v->getXSize() == vel2.v->getXSize());
    assert(vel.v->getYSize() == vel2.v->getYSize());
    for (int x = 0 ; x < vel.u->getXSize() ; x++) {
        for(int y = 0 ; y < vel.u->getYSize() ; y++) {
            // if (abs(vel.u->get(x,y).val - vel2.u->get(x,y).val) >= 1e-3) cout << x << ' ' << y << '\n';
            assert(abs(vel.u->get(x,y).val - vel2.u->get(x,y).val) < 1e-5);
            assert(abs(vel.v->get(x,y).val - vel2.v->get(x,y).val) < 1e-5);
        }
    }
}

void VelocityFieldStreamOperatorSubTest3(){
    VelocityField vel(97,101);
    FIELD<FieldDouble> & u = *vel.u;
    FIELD<FieldDouble> & v = *vel.v;

    for (int x = 0 ; x < u.getXSize() ; x++) {
        for(int y = 0 ; y < u.getYSize() ; y++) {
            u.set(x,y , (x*x + 0.382*x+y + 0.348*y + y*y) / 1e5);
        }
    }
    // cout << u[0][31].val << '\n';

    for (int x = 0 ; x < v.getXSize() ; x++) {
        for(int y = 0 ; y < v.getYSize() ; y++) {
            v.set(x,y , (-x*x - 0.211*x*y + 0.324*y + y*y ) / 1e5);
        }
    }
    // cout << vel;
    
    ofstream myfile;
    myfile.open("generateVelocity.txt");
    myfile << vel;
    myfile.close();

    ifstream myfile2;
    myfile2.open("generateVelocity.txt");

    VelocityField vel2;
    myfile2 >> vel2;
    myfile2.close();
    
    // cout << vel2.u->get(0,31).val << '\n';
    // Automated Tested
    assert(vel.u->getXSize() == vel2.u->getXSize());
    assert(vel.u->getYSize() == vel2.u->getYSize());
    assert(vel.v->getXSize() == vel2.v->getXSize());
    assert(vel.v->getYSize() == vel2.v->getYSize());
    for (int x = 0 ; x < vel.u->getXSize() ; x++) {
        for(int y = 0 ; y < vel.u->getYSize() ; y++) {
            // if (abs(vel.u->get(x,y).val - vel2.u->get(x,y).val) >= 1e-3) cout << x << ' ' << y << '\n';
            assert(abs(vel.u->get(x,y).val - vel2.u->get(x,y).val) < 1e-5);
            assert(abs(vel.v->get(x,y).val - vel2.v->get(x,y).val) < 1e-5);
        }
    }
}



#ifdef AUTOMATED_TEST
void VelocityFieldStreamOperatorTest() {
#else
int main () {
#endif
    
    VelocityFieldStreamOperatorSubTest1();
    VelocityFieldStreamOperatorSubTest2();
    VelocityFieldStreamOperatorSubTest3();

}
