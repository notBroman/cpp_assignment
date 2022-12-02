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
    if(!this->init_flag){
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
                default:
                    break;
            }
            switch(air_id){
                //check if air_id is in enum
                default:
                    break;
            }

        }
        return true;
    }

    return false;
}
//Utility
