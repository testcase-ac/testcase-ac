#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read month x: 1 to 12
    int x = inf.readInt(1, 12, "x");
    inf.readSpace();
    // Read day y: initially allow up to 31, we'll further check based on month
    int y = inf.readInt(1, 31, "y");
    inf.readEoln();

    // Days in each month for 2007 (non‐leap year)
    static const int mdays[13] = {
        0,
        31, // Jan
        28, // Feb
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

    // Validate that day y is within the allowed range for month x
    ensuref(y <= mdays[x],
            "Invalid day %d for month %d: month %d has only %d days",
            y, x, x, mdays[x]);

    inf.readEof();
    return 0;
}
