#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of cities
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Number of buses
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Each bus: a -> b with cost c
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 100000, "c_i");
        inf.readEoln();

        // No self loops allowed
        ensuref(a != b,
                "Bus %d has same start and end city: %d",
                i + 1, a);
    }

    inf.readEof();
    return 0;
}
