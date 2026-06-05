#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int jerseyCount = inf.readInt(1, 1000000, "J");
    inf.readEoln();
    int athleteCount = inf.readInt(1, 1000000, "A");
    inf.readEoln();

    for (int j = 1; j <= jerseyCount; ++j) {
        inf.readToken("S|M|L", "jersey_size");
        inf.readEoln();
    }

    for (int a = 1; a <= athleteCount; ++a) {
        inf.readToken("S|M|L", "requested_size");
        inf.readSpace();
        inf.readInt(1, jerseyCount, "requested_jersey");
        inf.readEoln();
    }

    inf.readEof();
}
