#include "cpp_part2_AirportFlightTimetable.hpp"

bool AirportFlightTimetable::checkEntryIsValid(const FlightTimetableEntry& test_entry, bool verbose) const{
    bool departure;
    int int_arr_in_h = 0;
    int arr_in_h = 0;
    // generic rules
    //  same ariline:
    //  + two entries with same dest & orig && same departure & arrival time
    //  + two entries with the sane flight code
    FlightTimetableEntry::AirportEnum orig, dest, new_orig, new_dest;
    FlightTimetableEntry::AirlinesEnum air_id, new_air_id;
    int fl_code, new_fl_code;
    unsigned char dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min;
    unsigned char new_dept_hour, new_dept_min, new_arriv_hr, new_arriv_min, new_durat_hr, new_durat_min;
    test_entry.getFTE(new_orig, new_dest, new_air_id, new_fl_code, new_dept_hour, new_dept_min, new_arriv_hr, new_arriv_min, new_durat_hr, new_durat_min);


    if(new_orig != this->home_airport && new_dest != this->home_airport){
        if(verbose) std::cout << "this airport does not invlolve " << test_entry.value2string(this->home_airport) << std::endl;
        return false;
    }

    departure = (orig == this->home_airport) ? true : false;

    if(departure && departures.size() == 0 || !departure && arrivals.size() == 0) return true;

    for(std::list<FlightTimetableEntry>::const_iterator itr=this->arrivals.begin(); itr != this->arrivals.end(); ++itr){
        //itr is a pointer to an instace of FlightTimetableEntry
        itr->getFTE(orig, dest, air_id, fl_code, dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min);

        if(!departure && orig == new_orig && dest == new_dest && new_dept_hour == dept_hour && 
                new_dept_min == dept_min && new_arriv_hr == arriv_hr && new_arriv_min == arriv_min && new_air_id == air_id){
            if(verbose) std::cout << "doublicate flight" << std::endl;
            return false;
        }

        if(new_fl_code == fl_code){
            if(verbose) std::cout << "Flight code already exists" << std::endl;
            return false;
        }
        // counters for arrival restrictions
        int_arr_in_h += (new_arriv_hr == arriv_hr && new_dest < 3) ? 1 : 0;
        arr_in_h += (new_arriv_hr == arriv_hr) ? 1 : 0;

        // check for time diff from same origin
        // min
        if(fabs(new_arriv_min-arriv_min) < 10 && (new_arriv_hr == arriv_hr || new_arriv_hr == arriv_hr + 1 || new_arriv_hr == arriv_hr - 1) && orig == new_orig){
            if(verbose) std::cout << "not enough time between arrivals from same origin" << std::endl;
            return false;
        }
    }

    for(std::list<FlightTimetableEntry>::const_iterator itr=this->departures.begin(); itr != this->arrivals.end(); ++itr){
        //itr is a pointer to an instace of FlightTimetableEntry
        itr->getFTE(orig, dest, air_id, fl_code, dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min);

        if(departure && orig == new_orig && dest == new_dest && new_dept_hour == dept_hour && 
                new_dept_min == dept_min && new_arriv_hr == arriv_hr && new_arriv_min == arriv_min && new_air_id == air_id){
            if(verbose) std::cout << "doublicate flight" << std::endl;
            return false;
        }

        if(new_fl_code == fl_code){
            if(verbose) std::cout << "Flight code already exists" << std::endl;
            return false;
        }
    }

    // specific rules
    //  + max departures:           40
    //  + max arrivals:             40
    //
    //  + max arriving flights/h:   6
    //  + max international arriving flights/h: 4
    //
    //  + min time between flights with same orig: 10 min

    if(departure && this->departures.size() >= 40){
        if(verbose) std::cout << "max departures have been reached" << std::endl;
        return false;
    }
    else if(!departure && this->arrivals.size() >= 40){
        if(verbose) std::cout << "max arrivals have been reached" << std::endl;
        return false;
    }

    if(int_arr_in_h > 4 || arr_in_h > 6){
        if(verbose) std::cout << "too many arrivals per hour" << std::endl;
        return false;
    }

    return true;
}

bool AirportFlightTimetable::checkAndAddEntry(const FlightTimetableEntry& test_entry){
    std::cout <<  "doing checks " << std::endl;
    if(this->checkEntryIsValid(test_entry, false)){
        std::cout <<  "inserting " << std::endl;
        // get info of test_entry
        FlightTimetableEntry::AirportEnum orig, dest, new_orig, new_dest;
        FlightTimetableEntry::AirlinesEnum air_id, new_air_id;
        int fl_code, new_fl_code;
        unsigned char dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min;
        unsigned char new_dept_hour, new_dept_min, new_arriv_hr, new_arriv_min, new_durat_hr, new_durat_min;
        test_entry.getFTE(new_orig, new_dest, new_air_id, new_fl_code, new_dept_hour, new_dept_min, new_arriv_hr, new_arriv_min, new_durat_hr, new_durat_min);

        bool departure = (new_orig == this->home_airport) ? true : false;

        if(departure){
            // insert into departures
            if(departures.size() == 0){
                departures.push_front(test_entry);
            }
            else{
                for(std::list<FlightTimetableEntry>::const_iterator itr=this->departures.begin(); itr != ++this->arrivals.end(); ++itr){
                    //itr is a potiner to an instance of FlightTimetableEntry
                    itr->getFTE(orig, dest, air_id, fl_code, dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min);
                    if(new_dept_hour < dept_hour && new_dept_min < dept_min){
                        departures.insert(itr, test_entry);
                        break;
                    }
                }
            }
        }
        else{
            // indert into arrivals
            if(arrivals.size() == 0){
                arrivals.push_front(test_entry);
            }
            else{
                for(std::list<FlightTimetableEntry>::const_iterator itr=this->arrivals.begin(); itr != ++this->arrivals.end(); ++itr){
                    //itr is a pointer to an instace of FlightTimetableEntry
                    itr->getFTE(orig, dest, air_id, fl_code, dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min);
                    if(new_arriv_hr < arriv_hr && new_arriv_min < arriv_min){
                        arrivals.insert(itr, test_entry);
                        break;
                    }
                }
            }
        }
        // determine if departure or arrival
        // insert in the correct possition in the correct table (arrivals or departures)
        return true;
    }
    return false;
}

void AirportFlightTimetable::printTimetable(tmtblCaseEnum ArrOrDepartOrBoth) const {
    // to be implemented
    FlightTimetableEntry::AirportEnum new_orig, new_dest;
    FlightTimetableEntry::AirlinesEnum new_air_id;
    int new_fl_code;
    unsigned char new_dept_hour, new_dept_min, new_arriv_hr, new_arriv_min, new_durat_hr, new_durat_min;


    if(arrivals.size() != 0 && (ArrOrDepartOrBoth == Both or ArrOrDepartOrBoth == Arrivals)){
        std::cout << "---------- Arrivals to Esbjerg ---------" << std::endl;
        for(std::list<FlightTimetableEntry>::const_iterator itr=this->arrivals.begin(); itr != this->arrivals.end(); ++itr){
            //itr is a pointer to an instace of FlightTimetableEntry
            itr->getFTE(new_orig, new_dest, new_air_id, new_fl_code, new_dept_hour, new_dept_min, new_arriv_hr, new_arriv_min, new_durat_hr, new_durat_min);
            std::cout << itr->value2string(new_orig) << " " << itr->value2string(new_arriv_hr, new_arriv_min) << " " << itr->value2string(new_air_id) << itr->value2string(new_fl_code) << std::endl;

        }
    }
    if(departures.size() != 0 && (ArrOrDepartOrBoth == Both or ArrOrDepartOrBoth == Departures)){
        std::cout << "---------- Departures from Esbjerg ---------" << std::endl;
        for(std::list<FlightTimetableEntry>::const_iterator itr=this->departures.begin(); itr != this->arrivals.end(); ++itr){
            //itr is a potiner to an instance of FlightTimetableEntry
            itr->getFTE(new_orig, new_dest, new_air_id, new_fl_code, new_dept_hour, new_dept_min, new_arriv_hr, new_arriv_min, new_durat_hr, new_durat_min);
            std::cout << itr->value2string(new_dest) << " " << itr->value2string(new_dept_hour, new_dept_min) << " " << itr->value2string(new_air_id) << itr->value2string(new_fl_code) << std::endl;
        }
    }
}

bool AirportFlightTimetable::isTimetableFull() const {
    // a timetable is full if the max amount of deparures and arrivals has been reached for the day
    bool res = (this->departures.size() >= 40 && this->arrivals.size() >= 40) ? true : false;
    return res;
}

