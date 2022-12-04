#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <random>


class FlightTimetableEntry{
public:
    enum AirportEnum{Aberdeen=0, London, Manchester, Copenhagen, Esbjerg, INVALID};
    enum AirlinesEnum{BA=0, SK, KL, EZY, LM, INV};

protected:
    static const char* AirportsEnumStrings[6];
    static const char* AirlinesEnumStrings[6];

    AirportEnum origin;
    AirportEnum destination;
    AirlinesEnum airline_id;

    static int flight_durations[5][5];

    int flight_code;
    std::string departure;
    std::string arrival;
    bool init_flag;
public:

    FlightTimetableEntry();
    ~FlightTimetableEntry();

    // Setter functions
    bool checkAndSetFTE(AirportEnum orig, AirportEnum dest, AirlinesEnum air_id, int fl_code, unsigned char dept_min, unsigned char dept_hour);
    bool setRandomFTE();
    void reset();

    // Getter Functions
bool getFTE(AirportEnum& orig, AirportEnum& dest, AirlinesEnum& air_id, int& fl_code, unsigned char& dept_min, unsigned char& dept_hour, unsigned char& arriv_hr, unsigned char& arriv_min, unsigned char& durat_hr, unsigned char& durat_min);
    void printEntry() const;

    // Utility Functions

    static bool getFlightDurationTime(AirportEnum orig, AirportEnum dest, unsigned char& out_hrs, unsigned char& out_min);
    static bool getFlightArrivalTime(AirportEnum orig, AirportEnum dest, unsigned char dpt_hrs_loc, unsigned char dpt_min_loc, unsigned char& arr_hrs_loc, unsigned char& arr_min_loc);
    static bool checkEntryVals(AirportEnum orig, AirportEnum dest, AirlinesEnum airID, int flCode, unsigned char dp_hr, unsigned char dp_min);

    static std::string value2string(AirlinesEnum airline);
    static std::string value2string(AirportEnum airp);
    static std::string value2string(unsigned char hour, unsigned char minute);
    static std::string value2string(int flCode);

    static int RandomValInBounds(int min_val, int max_val);
};


