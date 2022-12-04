#include "tester.hpp"

using namespace std;

void test_helpers()
{
    FlightTimetableEntry::AirportEnum orig, dest;
    unsigned char dur_hrs, dur_min, dpt_hrs, dpt_min, arr_hrs, arr_min;
    FlightTimetableEntry::AirlinesEnum airID;
    bool result;
    int flightCode;
    /////////////////// Input values for Test: choose values that apply to your rules ///////////////////////////////////
    orig = FlightTimetableEntry::Aberdeen;
    dest = FlightTimetableEntry::Esbjerg;
    dpt_hrs = 9;
    dpt_min = 5;
    airID = FlightTimetableEntry::BA;
    int temp = FlightTimetableEntry::RandomValInBounds(80,99);
    flightCode = 2000 + temp;
    // -------------------------------------------------------------------------//
    cout << "Test values: " << endl; cout << "Flight origin: " << FlightTimetableEntry::value2string(orig);
    cout << ". Flight destination: " << FlightTimetableEntry::value2string(dest) << endl;
    cout << "Test getFlightDurationTime()" << endl;
    result = FlightTimetableEntry::getFlightDurationTime(orig, dest, dur_hrs, dur_min);
    if (result)
        cout << "Flight duration (hh:mm) is " << FlightTimetableEntry::value2string(dur_hrs, dur_min) << endl;
    else
        cout << "No flight duration found" << endl;
    ///////////////////////////////////////////////////////////
    cout << endl << "Test getFlightArrivalTime()" << endl;
    cout << "Flight departure time (hh:mm) is " << FlightTimetableEntry::value2string(dpt_hrs, dpt_min) << endl;
    result = FlightTimetableEntry::getFlightArrivalTime(orig,dest,dpt_hrs,dpt_min,arr_hrs,arr_min);
    if (result)
        cout << "Arrival (local) time (hh:mm) is " << FlightTimetableEntry::value2string(arr_hrs, arr_min) << endl;
    else
        cout << "No Arrival time found" << endl;
    ///////////////////////////////////////////////////////////
    cout << endl << "Test checkEntryVals()" << endl;
    cout << "Airline ID: " << FlightTimetableEntry::value2string(airID);
    cout << ". Flight code: " << FlightTimetableEntry::value2string(flightCode) << endl;
    result = FlightTimetableEntry::checkEntryVals(orig, dest, airID, flightCode, dpt_hrs, dpt_min);
    if (result)
        cout << "Flight entry is valid." << endl;
    else
        cout << "Flight entry NOT valid." << endl;
}

void test_SettersAndGetters()
{
    FlightTimetableEntry testEntry;
    FlightTimetableEntry::AirportEnum orig, dest;
    unsigned char dur_hrs, dur_min, dpt_hrs, dpt_min, arr_hrs, arr_min;
    FlightTimetableEntry::AirlinesEnum airID;
    bool result;
    int flCode;
    /////////////////// Input values for Test ///////////////////////////////////
    orig = FlightTimetableEntry::Aberdeen;
    dest = FlightTimetableEntry::Esbjerg;
    dpt_hrs = 9;
    dpt_min = 5;
    airID = FlightTimetableEntry::BA;
    flCode = 2089;
    // -------------------------------------------------------------------------//
    cout << "Test values: " << endl << "Flight origin: " << FlightTimetableEntry::value2string(orig);
    cout << ". Flight destination: " << FlightTimetableEntry::value2string(dest) << endl;
    cout << "Flight departure time (hh:mm) is " << FlightTimetableEntry::value2string(dpt_hrs, dpt_min) << endl;
    cout << "Airline ID: " << FlightTimetableEntry::value2string(airID);
    cout << ". Flight code: " << FlightTimetableEntry::value2string(flCode) << endl;
    cout << "First, Test checkAndSetFTE()" << endl;
    result = testEntry.checkAndSetFTE(orig, dest, airID, flCode, dpt_hrs, dpt_min);
    if (!result)
        cout << "FTE could not be set." << endl;
    else
    {
        cout << "Done: FTE set." << endl << endl <<"Now Test getFTE() :" << endl;
        orig = FlightTimetableEntry::Aberdeen; dest = FlightTimetableEntry::Aberdeen;// if all works, these values will not matter
        dpt_hrs = 0; dpt_min = 0; airID = FlightTimetableEntry::KL; flCode = 9999; // if all works, these values will not matter
        result = testEntry.getFTE(orig, dest, airID, flCode, dpt_hrs, dpt_min, arr_hrs, arr_min, dur_hrs, dur_min);
        if (result)
        {
            cout << "Airline ID: " << FlightTimetableEntry::value2string(airID);
            cout << ". Flight code: " << FlightTimetableEntry::value2string(flCode) << endl;
            cout << "Flight origin: " << FlightTimetableEntry::value2string(orig);
            cout << ". Flight destination: " << FlightTimetableEntry::value2string(dest) << endl;
            cout << "Flight departure time (hh:mm) is " << FlightTimetableEntry::value2string(dpt_hrs, dpt_min) << endl;
            cout << "Flight arrival (local) time (hh:mm) is " << FlightTimetableEntry::value2string(arr_hrs, arr_min) << endl;
            cout << "Flight duration (hh:mm) is " << FlightTimetableEntry::value2string(dur_hrs, dur_min) << endl;
            cout << "Done." << endl << endl << "Next check that the same result is obtained from printEntry():" << endl;
            testEntry.printEntry();
            cout << "Done." << endl << endl << "Finally reset:" << endl;
            testEntry.reset();
            testEntry.printEntry();
        }
        else
            cout << "getFTE() did not work" << endl;
    }
}
/*
void testInsertion() {
    FlightTimetableEntry testEntry;
    FlightTimetableEntry::AirportEnum orig, dest, test_airport=FlightTimetableEntry::Aberdeen;

    unsigned char dur_hrs, dur_min, dpt_hrs, dpt_min, arr_hrs, arr_min;
    FlightTimetableEntry::AirlinesEnum airID;
    bool result;
    int flCode;
    AirportFlightTimetable ABD_Timetable;
    bool check;
    int flCode, tot_tests = 50;
    for (int test_i = 0; test_i < tot_tests; test_i++)
    {
        if (ABD_Timetable.isTimetableFull())
            break;
        cout << "Random entry " << test_i << ":" << endl;
        while (true)
        {
            testEntry.reset();
            testEntry.setRandomFTE();
            if (testEntry.isEntrySet())
            {
                testEntry.getFTE(orig, dest, airID, flCode, dpt_hrs, dpt_min, arr_hrs, arr_min, dur_hrs, dur_min);
                if (orig == test_airport || dest == test_airport)
                {
                    cout << "Checking entry:" << endl; testEntry.printEntry();
                    check = ABD_Timetable.checkEntryIsValid(testEntry, true);// print to screen the (first) rule that is violated
                    if (check)
                    { // insert entry and print
                        cout << endl << "Entry is valid: Inserting Entry" << endl; check = ABD_Timetable.checkAndAddEntry(testEntry);
                        if (check)
                        {
                            cout << "Entry Added" << endl; ABD_Timetable.printTimetable();
                        }
                        else
                        {
                            cout << "Inserting Entry FAILED" << endl;
                            return;
                        }
                        break;
                    }
                    else cout << "Check Failed: Entry can't be added to current timetable; try a different one" << endl << endl;
                }
            }
            else cout << "Entry Not set" << endl;
        }
        cout << "----------------" << endl;
    }
}
*/
