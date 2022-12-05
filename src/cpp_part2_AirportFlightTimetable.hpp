#pragma once

#include <iostream>
#include <string>
#include <list>

#include "cpp_part1_FlightTimetableEntry.hpp"

class AirportFlightTimetable{
    /*
     * It is assumed that each instance of the class keeps track of flight during ONE day
     *
     * This class keeps track of the airport in Esbjerg
     */
    public:
        enum tmtblCaseEnum {Both=0, Arrivals, Departures};

    protected:
        // easy to find, insert & delete element in list
        // implemented as a doubly linked list
        std::list<FlightTimetableEntry> departures;
        std::list<FlightTimetableEntry> arrivals;
        FlightTimetableEntry::AirportEnum home_airport = FlightTimetableEntry::Esbjerg;

    public:
        bool checkEntryIsValid(const FlightTimetableEntry& test_entry, bool verbose) const;
        bool checkAndAddEntry(const FlightTimetableEntry& test_entry);
        void printTimetable(tmtblCaseEnum ArrOrDepartOrBoth=Both) const;
        bool isTimetableFull() const;

};
