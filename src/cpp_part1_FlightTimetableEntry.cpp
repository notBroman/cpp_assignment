#include "cpp_part1_FlightTimetableEntry.hpp"

// static variables
int FlightTimetableEntry::flight_durations[5][5] = {{-1,95,80,95,85},{95,-1,60,105,95},{80,60,-1,100,90},{95,105,100,-1,50},{85,95,90,50,-1}};
const char* FlightTimetableEntry::AirportsEnumStrings[6] = {"Aberdeen", "London", "Manchester", "Copenhagen", "Esbjerg", "INVALID"};
const char* FlightTimetableEntry::AirlinesEnumStrings[6] = {"BA", "SK", "KL", "EZY", "LM", "INVALID"};

// Constructor & Destructor
FlightTimetableEntry::FlightTimetableEntry(){
    this->init_flag = false;
    this->destination = INVALID;
    this->origin = INVALID;
    this->airline_id = NAN;

    this->departure.clear();
    this->arrival.clear();
}

FlightTimetableEntry::~FlightTimetableEntry(){
    // do nothing
}
//Setters
bool FlightTimetableEntry::checkAndSetFTE(AirportEnum orig, AirportEnum dest, AirlinesEnum air_id, int fl_code, unsigned char dept_min, unsigned char dept_hour){
    //check basic rules
    if(!this->init_flag && this->checkEntryVals(orig, dest, air_id, fl_code, dept_min, dept_hour)){
        unsigned char arr_hour, arr_min;
        this->getFlightArrivalTime(orig, dest, dept_hour, dept_min, arr_hour, arr_min);

        //set values
        this->origin = orig;
        this->destination = dest;
        this->airline_id = air_id;
        this->flight_code = fl_code;

        this->departure += this->value2string(dept_hour, dept_min);
        this->arrival += this->value2string(arr_hour, arr_min);

        this->init_flag = true;

        return true;
    }

    return false;
}

void FlightTimetableEntry::reset(){
    this->init_flag = false;
    this->destination = INVALID;
    this->origin = INVALID;
    this->airline_id = NAN;
    this->flight_code = -1;

    this->departure.clear();
    this->arrival.clear();
}

//Getters


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
                std::cout << "invlad destination" << std::endl;
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
        unsigned char dur_h;
        unsigned char dur_min;
        getFlightDurationTime(orig, dest, dur_h, dur_min);
        int dur = (int)dur_h * 60 + (int)dur_min;
        bool res;

        if(dest > 2 || orig > 2){
            // do smth if international
            if(dept_hour >= 12 && dept_min > 0 && first != 9 || (dept_hour < 12 || dept_hour == 12 && dept_min == 0) && first != 2){
                std::cout << "flight code incorrect" << std::endl;
                return false;
            }
        }
        else{

            if(dept_hour >= 12 && dept_min > 0 && first != 7 || (dept_hour < 12 || dept_hour == 12 && dept_min == 0) && first != 0){
                std::cout << "flight code incorrect" << std::endl;
                return false;
            }
        }

        if (dur > 90 && second != 5){
            std::cout << "flight code incorrect" << std::endl;
            return false;
        }
        else if (dur < 90 && second != 0){
            std::cout << "flight code incorrect" << std::endl;
            return false;
        }

        switch(air_id){
            case BA:
                res = (last >= 80 && last <= 99) ? true : false;
                break;
            case SK:
                res = (last >= 0 && last <= 19) ? true : false;
                break;
            case KL:
                res = (last >= 20 && last <= 39) ? true : false;
                break;
            case EZY:
                res = (last >= 40 && last <= 59) ? true : false;
                break;
            case LM:
                res = (last >= 60 && last <= 79) ? true : false;
                break;
            default:
                res = false;
                std::cout << "flight code incorrect" << std::endl;
                break;
        }
        if(res == false){
            std::cout << "flight code incorrect" << std::endl;
            return res;
        }
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


bool FlightTimetableEntry::getFlightArrivalTime(AirportEnum orig, AirportEnum dest, unsigned char dept_hrs_loc, unsigned char dept_min_loc, unsigned char& arr_hrs_loc, unsigned char& arr_min_loc){
    if(orig < 5 && dest < 5){
        unsigned char dur_h, dur_min;
        int arrival = (int)dept_hrs_loc * 60 + (int)dept_min_loc;

        getFlightDurationTime(orig, dest, dur_h, dur_min);
        arrival += (int)dur_min;
        arrival += (int)dur_h * 60;

        arr_hrs_loc = arrival/60;
        arr_min_loc = arrival%60;

        return true;
    }
    return false;
}

std::string FlightTimetableEntry::value2string(AirlinesEnum airline){
    return AirlinesEnumStrings[ airline ];
}

std::string FlightTimetableEntry::value2string(AirportEnum airport){
    return AirportsEnumStrings[ airport ];
}

std::string FlightTimetableEntry::value2string(unsigned char hour, unsigned char min){
    std::string h = std::to_string((int)hour);
    std::string m = std::to_string((int)min);
    if(h.size() < 2){
        h.insert(h.front(),"0");
    }
    if(m.size() < 2){
        m.insert(h.front(),"0");
    }
    return h + ":" + m;
}

std::string FlightTimetableEntry::value2string(int fl_code){
    return std::to_string(42);
}
