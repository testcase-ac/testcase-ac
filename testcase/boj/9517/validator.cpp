#include "testlib.h"
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: initial holder K
    int K = inf.readInt(1, 8, "K");
    inf.readEoln();

    // Second line: number of questions N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Next N lines: time T_i and result Z_i
    long long totalTime = 0;
    for (int i = 1; i <= N; i++) {
        // Read time
        int t = inf.readInt(1, 100, "T_i");
        totalTime += t;
        // Exactly one space
        inf.readSpace();
        // Read result character: T, N, or P
        inf.readToken("[TNP]", "Z_i");
        inf.readEoln();
    }

    // The bomb explodes at 3 minutes 30 seconds = 210 seconds.
    // We must have recorded enough questions to cover the explosion moment.
    ensuref(totalTime >= 210,
            "Total recorded time %lld is less than explosion time 210", totalTime);

    inf.readEof();
    return 0;
}
