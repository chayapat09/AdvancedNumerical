#include <iostream>
#define AUTOMATED_TEST

#include "./FieldStreamOperator/main.cpp"
#include "./VelocityFieldStreamOperator/main.cpp"
#include "./PressureFieldStreamOperator/main.cpp"
#include "./FieldMemoryLeak/main.cpp"
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

    // PressureFieldStreamOperatorTest
    cout << "PressureFieldStreamOperatorTest : ";
    try {
        PressureFieldStreamOperatorTest();
        cout << "PASS";
    }
    catch(const std::exception& e) {
        cout << "FAILED";
    }
    cout << '\n';

    // FieldMemoryLeakTest
    cout << "FieldMemoryLeakTest : ";
    try {
        cout << '\n';
        FieldMemoryLeakTest();
        cout << '\n';
        cout << "PASS";
    }
    catch(const std::exception& e) {
        cout << "FAILED";
    }
    cout << '\n';
}