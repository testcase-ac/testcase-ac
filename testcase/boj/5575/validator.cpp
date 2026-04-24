#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 3 lines, one for each employee.
    for (int i = 1; i <= 3; i++) {
        char buf[32];

        // Arrival time h, m, s
        sprintf(buf, "h_arrival_%d", i);
        int h1 = inf.readInt(7, 22, buf);
        inf.readSpace();
        sprintf(buf, "m_arrival_%d", i);
        int m1 = inf.readInt(0, 59, buf);
        inf.readSpace();
        sprintf(buf, "s_arrival_%d", i);
        int s1 = inf.readInt(0, 59, buf);
        inf.readSpace();

        // Departure time h, m, s
        sprintf(buf, "h_departure_%d", i);
        int h2 = inf.readInt(7, 22, buf);
        inf.readSpace();
        sprintf(buf, "m_departure_%d", i);
        int m2 = inf.readInt(0, 59, buf);
        inf.readSpace();
        sprintf(buf, "s_departure_%d", i);
        int s2 = inf.readInt(0, 59, buf);

        // End of line for this employee
        inf.readEoln();

        // Check that departure is strictly after arrival
        long long t1 = (long long)h1 * 3600 + m1 * 60 + s1;
        long long t2 = (long long)h2 * 3600 + m2 * 60 + s2;
        ensuref(t1 < t2,
                "Employee %d: departure time (%02d:%02d:%02d) is not strictly after arrival time (%02d:%02d:%02d)",
                i, h2, m2, s2, h1, m1, s1);
    }

    // After the third line, there must be no extra data
    inf.readEof();
    return 0;
}
