#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read month
    int m = inf.readInt(1, 12, "month");
    inf.readEoln();

    // Read day
    int d = inf.readInt(1, 31, "day");
    inf.readEoln();

    // Validate day against the actual days in each month for 2015 (non‐leap year)
    static const int daysInMonth[13] = {
        0,  // dummy for 1-based index
        31, // Jan
        28, // Feb (2015 is not a leap year)
        31, // Mar
        30, // Apr
        31, // May
        30, // Jun
        31, // Jul
        31, // Aug
        30, // Sep
        31, // Oct
        30, // Nov
        31  // Dec
    };
    ensuref(d <= daysInMonth[m],
            "Invalid day %d for month %d (max %d days)", 
            d, m, daysInMonth[m]);

    inf.readEof();
    return 0;
}
