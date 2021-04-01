#include <iostream>

#define _DEBUG_

#include "../ProgramParameters.h"
#include "../Field.h"
#include "../FG.h"

using namespace std;

int main() {
    
    ProgramParamerters programParameter;
    initProblemParams(programParameter);
    VelocityField uv(11, 17);
    uv.u->setAll(1);
    for(int i=0; i < 11; i++){
        uv.u->set(i, 0, -1);
        uv.u->set(i, 16, -1);
    }
    uv.v->setAll(0);

    FG fg(11, 17);
    fg.F->setAll(0);
    fg.G->setAll(0);

    cout << "Before\n";
    cout << "u\n";
    uv.u->printField();
    cout << "v\n";
    uv.v->printField();
    cout << "F\n";
    fg.F->printField();
    cout << "G\n";
    fg.G->printField();

    computeFG(uv, fg, programParameter);

    cout << "After\n";
    // fg.F->printField();
    // fg.G->printField();
    cout << "u\n";
    uv.u->printField();
    cout << "v\n";
    uv.v->printField();
    cout << "F\n";
    fg.F->printField();
    cout << "G\n";
    fg.G->printField();

}