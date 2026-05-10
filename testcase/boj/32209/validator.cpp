#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Q: number of events
    int Q = inf.readInt(1, 10, "Q");
    inf.readEoln();

    long long problems = 0;
    bool dissolved = false;

    for (int i = 0; i < Q; ++i) {
        int type = inf.readInt(1, 2, "t");
        inf.readSpace();
        int v = inf.readInt(1, 10, "value");
        inf.readEoln();

        if (type == 1) {
            // Add problems
            problems += v;
        } else {
            // Use problems
            if (problems < v) {
                dissolved = true;
            } else {
                problems -= v;
            }
        }
    }

    // Problem guarantees nothing about dissolution explicitly, but
    // it claims that dissolution happens exactly when y > remaining problems.
    // We've simulated it to ensure no hidden overflow or inconsistency.
    // (No extra constraint to assert beyond basic simulation here.)

    inf.readEof();
}
