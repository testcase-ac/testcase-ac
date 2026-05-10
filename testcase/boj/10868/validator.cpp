#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the array of N integers
    for (int i = 0; i < N; i++) {
        long long v = inf.readLong(1LL, 1000000000LL, "value");
        inf.readEoln();
    }

    // Read M queries
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();
        ensuref(a <= b,
                "Query %d is invalid: a (%d) must be <= b (%d)", i, a, b);
    }

    inf.readEof();
    return 0;
}
