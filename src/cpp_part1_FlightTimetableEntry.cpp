#include "cpp_part1_FlightTimetableEntry.hpp"

// static variables
int FlightTimetableEntry::flight_durations[5][5] = {{-1,95,80,95,85},{95,-1,60,105,95},{80,60,-1,100,90},{95,105,100,-1,50},{85,95,90,50,-1}};

// Constructor & Destructor
FlightTimetableEntry::FlightTimetableEntry(){
    this->init_flag = false;
    this->destination = INVALID;
    this->origin = INVALID;
    this->airline_id = NAN;
}

FlightTimetableEntry::~FlightTimetableEntry(){
    // do nothing
}
//Setters
bool FlightTimetableEntry::checkAndSetFTE(AirportEnum orig, AirportEnum dest, AirlinesEnum air_id, int fl_code, unsigned char dept_min, unsigned char dept_hour){
    //check basic rules
    if(!this->init_flag && this->checkEntryVals(orig, dest, air_id, fl_code, dept_min, dept_hour)){
        //set values
        return true;
    }

    return false;
}
//Utility

bool FlightTimetableEntry::checkEntryVals(AirportEnum orig, AirportEnum dest, AirlinesEnum air_id, int fl_code, unsigned char dept_min, unsigned char dept_hour){
    if(orig == dest){
        std::cout << "origin and destination must not be the same" << std::endl;
        return false;
    }
    else{
        switch(orig){
            case Aberdeen:
                if(dept_hour < 5 && dept_min < 0 || dept_hour > 20 && dept_min > 50){
                    std::cout << "departure invalid" << std::endl;
                    return false;
                }
                break;
            case London:
                if(dept_hour < 5 && dept_min < 0 || dept_hour > 21 && dept_min > 05){
                    std::cout << "departure invalid" << std::endl;
                    return false;
                }
                break;
            case Manchester:
                if(dept_hour < 5 && dept_min < 15 || dept_hour > 20 && dept_min > 55){
                    std::cout << "departure invalid" << std::endl;
                    return false;
                }
                break;
            case Copenhagen:
                if(dept_hour < 5 && dept_min < 0 || dept_hour > 21 && dept_min > 45){
                    std::cout << "departure invalid" << std::endl;
                    return false;
                }
                break;
            case Esbjerg:
                if(dept_hour < 5 && dept_min < 45 || dept_hour > 21 && dept_min > 30){
                    std::cout << "departure invalid" << std::endl;
                    return false;
                }
                break;
            default:
                std::cout << "origin must be valid" << std::endl;
                return false;
                break;
        }
        switch(dest){
            //check if destination is in enum
            case Aberdeen:
                break;
            case London:
                break;
            case Manchester:
                break;
            case Copenhagen:
                break;
            case Esbjerg:
                break;
            default:
                return false;
        }
        // check air_id is correct
        // digit 1:
        // AM:
        //  0 -> domestic
        //  2 -> international
        // PM:
        //  7 -> domestic
        //  9 -> international
        //
        //  digit 2:
        //  0 -> duration < 90 min
        //  5 -> duration > 90 min
        //
        // digit 3 & 4:
        //  BA: 80-99
        //  SK: 00-19
        //  KL: 20-39
        //  EZY: 40-59
        //  LM: 60-79
        int first = (int)fl_code/1000;
        int second = (int)fl_code/100;
        int last = (int)fl_code%100;

    }
    return true;

}

bool FlightTimetableEntry::getFlightDurationTime(AirportEnum orig, AirportEnum dest, unsigned char& out_hrs, unsigned char& out_min){
    // this function assumes that the airports are valid, since it is called in checkInputVals after this is
    // validated
    if(orig < 5 && dest < 5){
        out_hrs = (int)(flight_durations[orig][dest]/60);
        out_min = (int)(flight_durations[orig][dest]%60);
        return true;
    }
    return false;
}
