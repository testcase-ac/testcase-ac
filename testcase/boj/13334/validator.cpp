#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of people
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Each person's home and office positions
    for (int i = 1; i <= n; i++) {
        int h = inf.readInt(-100000000, 100000000, "h_i");
        inf.readSpace();
        int o = inf.readInt(-100000000, 100000000, "o_i");
        inf.readEoln();
        ensuref(h != o,
                "At person %d: home and office positions must differ, got %d and %d",
                i, h, o);
    }

    // Length of the railroad segment
    int d = inf.readInt(1, 200000000, "d");
    inf.readEoln();

    inf.readEof();
    return 0;
}
