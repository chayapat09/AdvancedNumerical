#include <iostream>
#include <fstream>
#include <assert.h>
#include "../../Field.h"
using namespace std;



void showProgress(int n ,int max_n) {
    float progress =  ((float)n / (float)max_n);
    int barWidth = 70;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();

// std::cout << std::endl;
}

#ifdef AUTOMATED_TEST
void FieldMemoryLeakTest() {
#else
int main () {
#endif

    // Allocated x = 1 , and y = ?
    // Allocated x = ? , and y = 1
    int targetGB = 8; // 8 GB of memory to be allocated Note: Allocated > your computer Memory
    int GBPerLoop = 1; // 1GB per loop
    // Assume 8 bytes per points for convenience
    int sizePerGb = 1024 * 1024 * 1024 / 8;
    int n = 0;
    int max_n = targetGB / GBPerLoop * 2;
    for (int i = 0 ; i < targetGB / GBPerLoop ; i++) {
        FIELD<FieldDouble> f1(1 , sizePerGb * GBPerLoop);
        n++;
        showProgress(n , max_n);
    }

    for (int i = 0 ; i < targetGB / GBPerLoop ; i++) {
        FIELD<FieldDouble> f1(sizePerGb * GBPerLoop / 8 , 1);
        n++;
        showProgress(n , max_n);
    }

    // Assert Program will crash if memory leaked beacause of 128 GB MEMORY Allocation

}

