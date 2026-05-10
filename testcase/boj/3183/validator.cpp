#include "testlib.h"

using namespace std;

bool isLeap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return (y % 4 == 0);
}

int daysInMonth(int m, int y) {
    if (m == 2) return isLeap(y) ? 29 : 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input is a sequence of lines, each with three non-negative integers:
    // day, month, year, terminated by "0 0 0" line.
    // Day, month < 100; year in [1700,2200] for non-terminator lines.

    while (true) {
        int d = inf.readInt(0, 99, "day");
        inf.readSpace();
        int m = inf.readInt(0, 99, "month");
        inf.readSpace();
        int y = inf.readInt(0, 2200, "year");
        inf.readEoln();

        if (d == 0 && m == 0 && y == 0) {
            break;
        }

        // Year must be in [1700, 2200] for actual dates
        ensuref(y >= 1700, "Year out of range for a non-terminator line: %d", y);

        // No further structural constraints are guaranteed; invalid dates
        // are allowed and should be handled by the solution. Thus we do not
        // enforce day/month validity ranges beyond the token bounds above.
        // Specifically, we do NOT reject invalid calendar dates like 32 1 1976.
    }

    inf.readEof();
}
