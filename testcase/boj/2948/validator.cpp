#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read day D and month M for a date in 2009
    int D = inf.readInt(1, 31, "D");
    inf.readSpace();
    int M = inf.readInt(1, 12, "M");
    inf.readEoln();

    // Validate the day against the month in the (non-leap) year 2009
    static const int daysInMonth[13] = {
        0,  // dummy to make the index 1-based
        31, // January
        28, // February (2009 is not a leap year)
        31, // March
        30, // April
        31, // May
        30, // June
        31, // July
        31, // August
        30, // September
        31, // October
        30, // November
        31  // December
    };
    ensuref(D <= daysInMonth[M],
            "Invalid day %d for month %d in year 2009", D, M);

    inf.readEof();
    return 0;
}
