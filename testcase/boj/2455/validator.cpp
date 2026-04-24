#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int STATIONS = 4;
    int current = 0;
    int off[STATIONS+1], on[STATIONS+1];

    // Read data for 4 stations
    for (int i = 1; i <= STATIONS; i++) {
        char name[16];

        // people exiting at station i
        sprintf(name, "off_%d", i);
        off[i] = inf.readInt(0, 10000, name);

        inf.readSpace();

        // people entering at station i
        sprintf(name, "on_%d", i);
        on[i] = inf.readInt(0, 10000, name);

        inf.readEoln();
    }

    // Check fixed constraints for first and last station
    ensuref(off[1] == 0,
            "At station 1 (start), number of exiting passengers must be 0, found %d",
            off[1]);
    ensuref(on[STATIONS] == 0,
            "At station %d (end), number of entering passengers must be 0, found %d",
            STATIONS, on[STATIONS]);

    // Simulate the train to enforce no-overexit and capacity constraints
    current = 0;
    for (int i = 1; i <= STATIONS; i++) {
        // cannot exit more than are on board
        ensuref(off[i] <= current,
                "At station %d, exiting = %d exceeds current onboard = %d",
                i, off[i], current);
        current -= off[i];

        // add entering passengers
        current += on[i];

        // capacity must not exceed 10000
        ensuref(current <= 10000,
                "Capacity exceeded at station %d: current onboard = %d",
                i, current);
    }

    inf.readEof();
    return 0;
}
