#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int l = inf.readInt(1, 100000, "l");
    inf.readEoln();

    int totalStations = 0;
    for (int i = 1; i <= l; ++i) {
        int lineLength = 0;
        while (true) {
            int station = inf.readInt(-1, n, "station");
            if (station == -1) {
                break;
            }
            ensuref(station >= 1, "station number must be -1 or in [1, n]");
            ++lineLength;
            ++totalStations;
            ensuref(totalStations <= 1000000,
                    "total route station count exceeds 1000000");
            inf.readSpace();
        }
        // CHECK: A subway line that passes no stations would make the stated
        // route object absent, so require at least one station before -1.
        ensuref(lineLength >= 1, "line %d has no stations", i);
        inf.readEoln();
    }

    inf.readInt(1, n, "source");
    inf.readSpace();
    inf.readInt(1, n, "destination");
    inf.readEoln();

    inf.readEof();
}
