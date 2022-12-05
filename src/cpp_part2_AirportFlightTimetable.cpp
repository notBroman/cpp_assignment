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


    if(orig != this->home_airport && dest != this->home_airport){
        std::cout << "this airport does not invlolve " << test_entry.value2string(this->home_airport) << std::endl;
        return false;
    }
    departure = (orig == this->home_airport) ? true : false;

    for(std::list<FlightTimetableEntry>::const_iterator itr=this->arrivals.begin(); itr != this->arrivals.end(); ++itr){
        //itr is a pointer to an instace of FlightTimetableEntry
        itr->getFTE(orig, dest, air_id, fl_code, dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min);

        if(!departure && orig == new_orig && dest == new_dest && new_dept_hour == dept_hour && 
                new_dept_min == dept_min && new_arriv_hr == arriv_hr && new_arriv_min == arriv_min && new_air_id == air_id){
            return false;
        }

        if(new_fl_code == fl_code){
            return false;
        }
        // counters for arrival restrictions
        int_arr_in_h += (new_arriv_hour == arriv_hour && new_dest < 3) ? 1 : 0;
        arr_in_h += (new_arriv_hour == arriv_hour) ? 1 : 0;

        // check for time diff from same origin
        // min
        if(fabs(new_arriv_min-arriv_min) < 10 && (new_arriv_hour == arriv_hour || new_arriv_hour == arriv_hour + 1 || new_arriv_hour == arriv_hour - 1) && orig == new_orig){
            return false;
        }
    }

    for(std::list<FlightTimetableEntry>::const_iterator itr=this->departures.begin(); itr != this->arrivals.end(); ++itr){
        //itr is a pointer to an instace of FlightTimetableEntry
        itr->getFTE(orig, dest, air_id, fl_code, dept_hour, dept_min, arriv_hr, arriv_min, durat_hr, durat_min);

        if(departure && orig == new_orig && dest == new_dest && new_dept_hour == dept_hour && 
                new_dept_min == dept_min && new_arriv_hr == arriv_hr && new_arriv_min == arriv_min && new_air_id == air_id){
            return false;
        }

        if(new_fl_code == fl_code){
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
        return false;
    }
    else if(!departure && this->arrivals.size() >= 40){
        return false;
    }

    if(int_arr_in_h > 4 || arr_in_h > 6){
        return false;
    }

    return true;
}

bool AirportFlightTimetable::checkAndAddEntry(const FlightTimetableEntry& test_entry){
    if(this->checkEntryIsValid(test_entry, false)){
        // get info of test_entry

        // determine if departure or arrival

        // insert in the correct possition in the correct table (arrivals or departures)
        return true;
    }
    return false;
}

void AirportFlightTimetable::printTimetable(tmtblCaseEnum ArrOrDepartOrBoth) const {
    // to be implemented
    if(ArrOrDepartOrBoth == Both or ArrOrDepartOrBoth == Arrivals){
        for(std::list<FlightTimetableEntry>::const_iterator itr=this->arrivals.begin(); itr != this->arrivals.end(); ++itr){
        //itr is a pointer to an instace of FlightTimetableEntry
        }
    }
    if(ArrOrDepartOrBoth == Both or ArrOrDepartOrBoth == Departures){
        for(std::list<FlightTimetableEntry>::const_iterator itr=this->departures.begin(); itr != this->arrivals.end(); ++itr){
            //itr is a potiner to an instance of FlightTimetableEntry

        }
    }
}

bool AirportFlightTimetable::isTimetableFull() const {
    // a timetable is full if the max amount of deparures and arrivals has been reached for the day
    bool res = (this->departures.size() >= 40 && this->arrivals.size() >= 40) ? true : false;
    return res;
}

