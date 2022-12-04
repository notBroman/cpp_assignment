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
    this->airline_id = INV;

    this->departure.clear();
    this->arrival.clear();
}

FlightTimetableEntry::~FlightTimetableEntry(){
    // do nothing
}
//Setters
bool FlightTimetableEntry::checkAndSetFTE(AirportEnum orig, AirportEnum dest, AirlinesEnum air_id, int fl_code, unsigned char dept_hour, unsigned char dept_min){
    //check basic rules
    if(!this->init_flag && this->checkEntryVals(orig, dest, air_id, fl_code, dept_min, dept_hour)){
        unsigned char arr_hour, arr_min;
        this->getFlightArrivalTime(orig, dest, dept_hour, dept_min, arr_hour, arr_min);

        //set values
        this->origin = orig;
        this->destination = dest;
        this->airline_id = air_id;
        this->flight_code = fl_code;

        this->departure = this->value2string(dept_hour, dept_min);
        this->arrival = this->value2string(arr_hour, arr_min);

        this->init_flag = true;

        return true;
    }

    return false;
}

void FlightTimetableEntry::reset(){
    this->init_flag = false;
    this->destination = INVALID;
    this->origin = INVALID;
    this->airline_id = INV;
    this->flight_code = -1;

    this->departure.clear();
    this->arrival.clear();
}

bool FlightTimetableEntry::setRandomFTE(){
    if(!this->init_flag){
        AirportEnum orig, dest;
        AirlinesEnum airline;
        unsigned char dept_hr, dept_min, dur_hr, dur_min;
        int fl_code, temp;
        fl_code = 0;

        orig = (AirportEnum)this->RandomValInBounds(0,4);
        dest = (AirportEnum)this->RandomValInBounds(0,4);
        airline = (AirlinesEnum)this->RandomValInBounds(0,4);

        // get valid departure
        switch(orig){
            case Aberdeen:
                temp = this->RandomValInBounds(5*60,20*60+50);
                break;
            case London:
                temp = this->RandomValInBounds(5*60,21*60+05);
                break;
            case Manchester:
                temp = this->RandomValInBounds(5*60+15,20*60+55);
                break;
            case Copenhagen:
                temp = this->RandomValInBounds(5*60,21*60+45);
                break;
            case Esbjerg:
                temp = this->RandomValInBounds(5*60+45,21*60+30);
                break;
            default:
                break;
        }

        dept_hr = (int)temp/60;
        dept_min = temp%60;
        // get valid fl_code
        this->getFlightDurationTime(orig, dest, dur_hr, dur_min);
        // if the flight is international add 5 as the second digit
        fl_code += (dur_hr*60+min > 90) ? 500 : 0;

        // add a rendom value for each airline
        switch(airline){
            case BA:
                fl_code += this->RandomValInBounds(80,99);
                break;
            case SK:

                fl_code += this->RandomValInBounds(0,19);
                break;
            case KL:

                fl_code += this->RandomValInBounds(20,39);
                break;
            case EZY:

                fl_code += this->RandomValInBounds(40,59);
                break;
            case LM:

                fl_code += this->RandomValInBounds(60,79);
                break;
            default:
                break;
        }
        // 7 is added to the first digit if it leaves in the afternoon
        // 2 is added to the first digit if it is an international flight
        // otherwise 0 is added
        fl_code += (dept_hr*60+dept_min > 12*60 ) ? 7000 : 0;
        fl_code += ( orig > 2 || dest > 2 ) ? 2000 : 0;


        this->checkAndSetFTE(orig, dest, airline, fl_code, dept_hr, dept_min);
        return true;
    }
    return false;
}

//Getters

bool FlightTimetableEntry::getFTE(AirportEnum& orig, AirportEnum& dest, AirlinesEnum& air_id, int& fl_code, unsigned char& dept_hour, unsigned char& dept_min, unsigned char& arriv_hr, unsigned char& arriv_min, unsigned char& durat_hr, unsigned char& durat_min){
    if(this->init_flag){
        orig = this->origin;
        dest = this->destination;
        air_id = this->airline_id;
        fl_code = this->flight_code;
        // the colon will always be at position 2 (xx:yy)
        // a substring of length 2 is always looked for
        dept_hour = std::stoi(departure.substr(0,2),nullptr);
        dept_min = std::stoi(departure.substr(3,2),nullptr);
        arriv_hr = std::stoi(arrival.substr(0,2),nullptr);
        arriv_min = std::stoi(arrival.substr(3,2),nullptr);
        this->getFlightDurationTime(orig, dest, durat_hr, durat_min);

        return true;
    }
    return false;
}

void FlightTimetableEntry::printEntry() const {
    std::cout << "Flight " << this->value2string(this->flight_code) << " :\n" << this->value2string(this->origin) << "->" << this->value2string(this->destination) << std::endl;
    std::cout << "Departure: " << this->departure << "->" << "Arrival: " << this->arrival << std::endl;
    unsigned char hr, m;
    this->getFlightDurationTime(this->origin, this->destination, hr, m);
    std::cout << "Flight duration: "  << this->value2string(hr, m) << std::endl;
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
        int second = (int)fl_code%1000/100;
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
        h = "0" + h;
    }
    if(m.size() < 2){
        m = "0" + m;
    }
    return h + ":" + m;
}

std::string FlightTimetableEntry::value2string(int fl_code){
    std::string a = std::to_string(fl_code);
    if(a.size() < 4){
        a = "0" + a;
    }
    return a;
}

int FlightTimetableEntry::RandomValInBounds(int min_val, int max_val){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min_val, max_val);
    return distribution(generator);
}
