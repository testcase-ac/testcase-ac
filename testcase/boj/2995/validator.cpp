#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of intervals
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each interval [A, B]
    for (int i = 1; i <= N; i++) {
        int A = inf.readInt(1, 1000000, "A");
        inf.readSpace();
        int B = inf.readInt(1, 1000000, "B");
        inf.readEoln();

        ensuref(A < B,
                "Interval %d is invalid: A (%d) must be less than B (%d)", 
                i, A, B);
    }

    // No extra data
    inf.readEof();
    return 0;
}
