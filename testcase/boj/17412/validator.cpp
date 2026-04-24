#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and P
    int N = inf.readInt(3, 400, "N");
    inf.readSpace();
    int P = inf.readInt(1, 10000, "P");
    inf.readEoln();

    // Read P directed edges
    for (int i = 1; i <= P; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loops
        ensuref(u != v,
                "Self-loop detected at edge index %d: (%d, %d)", i, u, v);

        // No direct connection between city 1 and city 2 in input
        ensuref(!(u == 1 && v == 2) && !(u == 2 && v == 1),
                "Edge connecting city 1 and 2 is forbidden at index %d: (%d, %d)", i, u, v);
    }

    inf.readEof();
    return 0;
}
