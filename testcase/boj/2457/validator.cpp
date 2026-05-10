#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Days in each month for a non-leap year
    static const int daysInMonth[13] = {
        0, // dummy for 1-based
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

    // Read number of flowers
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        // Read bloom date: month and day
        int sm = inf.readInt(1, 12, "sm");
        inf.readSpace();
        int sd = inf.readInt(1, 31, "sd");
        // Check valid day for bloom month
        ensuref(sd <= daysInMonth[sm],
                "Invalid bloom day %d for month %d at flower %d", sd, sm, i+1);

        inf.readSpace();
        // Read die date: month and day
        int em = inf.readInt(1, 12, "em");
        inf.readSpace();
        int ed = inf.readInt(1, 31, "ed");
        // Check valid day for die month
        ensuref(ed <= daysInMonth[em],
                "Invalid die day %d for month %d at flower %d", ed, em, i+1);

        // Each flower must bloom strictly before it dies
        bool before = (sm < em) || (sm == em && sd < ed);
        ensuref(before,
                "Flower %d has non-positive lifespan: blooms %d/%d, dies %d/%d",
                i+1, sm, sd, em, ed);

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
