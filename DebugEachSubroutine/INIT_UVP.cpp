#include <iostream>

#define DEBUG

#include "../ProgramParameters.h"
#include "../Field.h"

using namespace std;

int main() {
    
    FIELD<FieldDouble> u(4,4);
    u.printField();

    u.setAll(10);
    cout << "After set all values\n";
    u.printField();

    VelocityField uv(3,3);
    (uv.u)->printField();
    (uv.v)->printField();
    cout << "After set all values\n";
    (uv.u)->setAll(5);
    (uv.u)->printField();
    (uv.v)->setAll(11);
    (uv.v)->printField();

}