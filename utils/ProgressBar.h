#include "../ProgramParameters.h"
#include <iostream>

void showProgress(ProgramParamerters & params) {
    float progress = params.timeSteppingData.t / params.timeSteppingData.t_end;
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