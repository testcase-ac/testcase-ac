#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int STATIONS = 10;
    int curr = 0;
    for (int i = 1; i <= STATIONS; i++) {
        // Read number of people getting off
        string off_name = "off_" + to_string(i);
        int off = inf.readInt(0, 10000, off_name.c_str());
        inf.readSpace();

        // Read number of people getting on
        string on_name = "on_" + to_string(i);
        int on = inf.readInt(0, 10000, on_name.c_str());
        inf.readEoln();

        // Constraint: at departure station, nobody gets off
        if (i == 1) {
            ensuref(off == 0,
                    "At station 1, off_1 must be 0 but found %d", off);
        }
        // Constraint: at terminal station, nobody gets on
        if (i == STATIONS) {
            ensuref(on == 0,
                    "At station %d (last), on_%d must be 0 but found %d",
                    STATIONS, STATIONS, on);
        }
        // Cannot get off more people than currently onboard
        ensuref(off <= curr,
                "At station %d, off_%d = %d exceeds current onboard = %d",
                i, i, off, curr);
        curr -= off;

        // Add boarding, check capacity does not exceed 10000
        curr += on;
        ensuref(curr <= 10000,
                "After station %d, onboard = %d exceeds capacity 10000",
                i, curr);
    }

    inf.readEof();
    return 0;
}
