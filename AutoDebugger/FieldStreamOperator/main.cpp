#include <iostream>
#include <fstream>
#include <assert.h>
#include "../../Field.h"
using namespace std;

#ifdef AUTOMATED_TEST
void FieldStreamOperatorTest() {
#else
int main () {
#endif
    FIELD<FieldDouble> f(10,10);

    for (int x = 0 ; x < f.getXSize() ; x++) {
        for(int y = 0 ; y < f.getYSize() ; y++) {
            if (x - y == 0 || x + y == 9) {
                f.set(x,y , 1.234234);
            }
        }
    }
    // cout << f;
    ofstream myfile;
    myfile.open("generated.txt");
    myfile << f;
    myfile.close();

    ifstream myfile2;
    myfile2.open("generated.txt");

    FIELD<FieldDouble> f2(1,1);
    myfile2 >> f2;
    myfile2.close();
    
    // Automated Tested
    assert(f.getXSize() == f2.getXSize());
    assert(f.getYSize() == f2.getYSize());
    for (int x = 0 ; x < f.getXSize() ; x++) {
        for(int y = 0 ; y < f.getYSize() ; y++) {
            assert(abs(f[x][y].val - f2[x][y].val) < 1e-5);            
        }
    }

}