#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities N and number of roads M
    int N = inf.readInt(2, 1500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 5000, "M");
    inf.readEoln();

    // Read each road: O, D, L
    for (int i = 0; i < M; i++) {
        // Road start
        int O = inf.readInt(1, N, "O_i");
        inf.readSpace();
        // Road destination
        int D = inf.readInt(1, N, "D_i");
        inf.readSpace();
        // Road length
        int L = inf.readInt(1, 10000, "L_i");
        inf.readEoln();

        // No self loops
        ensuref(O != D,
                "Self loop detected on road %d: O = %d, D = %d", i + 1, O, D);
    }

    inf.readEof();
    return 0;
}
