#include <iostream>
#define AUTOMATED_TEST

#include "./FieldStreamOperator/main.cpp"
#include "./VelocityFieldStreamOperator/main.cpp"
using namespace std;

int main() {

    // FieldStreamOperatorTest
    cout << "FieldStreamOperatorTest : ";
    try {
        FieldStreamOperatorTest();
        cout << "PASS";
    }
    catch(const std::exception& e) {
        cout << "FAILED";
    }
    cout << '\n';
    
    // VelocityFieldStreamOperatorTest
    cout << "VelocityFieldStreamOperatorTest : ";
    try {
        VelocityFieldStreamOperatorTest();
        cout << "PASS";
    }
    catch(const std::exception& e) {
        cout << "FAILED";
    }
    cout << '\n';
}