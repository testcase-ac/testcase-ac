#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and P
    int N = inf.readInt(3, 400, "N");
    inf.readSpace();
    int P = inf.readInt(1, 10000, "P");
    inf.readEoln();

    // Validate each of the P edges
    for (int i = 1; i <= P; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loops
        ensuref(u != v,
                "Self-loop detected on edge %d: (%d, %d)", i, u, v);

        // No direct edge between city 1 and city 2
        ensuref(!((u == 1 && v == 2) || (u == 2 && v == 1)),
                "Direct edge between city 1 and 2 is not allowed (edge %d: %d-%d)", 
                i, u, v);
    }

    // End of file
    inf.readEof();
    return 0;
}
