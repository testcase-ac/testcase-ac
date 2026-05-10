#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read t
    int t = inf.readInt(1, 25, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // Read n and m
        int n = inf.readInt(1, 9, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100000, "m");
        inf.readEoln();

        // No further constraints to check for n and m
    }

    inf.readEof();
}
