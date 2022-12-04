#include <iostream>
#include "cpp_part1_FlightTimetableEntry.hpp"
//#include "tester.hpp"

int main(int argv, char* argc[]){

    FlightTimetableEntry a;
    a.checkEntryVals(Aberdeen, London, BA, 590, 6,0);

    std::cout << "Hello World" << std::endl;
    return 0;
}
