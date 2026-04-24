#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of classes
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read each interval and validate constraints
    for (int i = 1; i <= N; i++) {
        int S = inf.readInt(0, 1000000000, "S_i");
        inf.readSpace();
        int T = inf.readInt(0, 1000000000, "T_i");
        inf.readEoln();
        ensuref(S < T,
                "Interval %d is invalid: S_i (%d) must be < T_i (%d)", 
                i, S, T);
    }

    inf.readEof();
    return 0;
}
