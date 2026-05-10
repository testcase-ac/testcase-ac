#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of cities
    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    // Number of buses
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Bus records
    for (int i = 1; i <= m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 100000, "c_i");
        inf.readEoln();

        // No loops allowed
        ensuref(a != b,
                "Loop detected at bus %d: start city %d and end city %d must differ",
                i, a, b);
    }

    inf.readEof();
    return 0;
}
