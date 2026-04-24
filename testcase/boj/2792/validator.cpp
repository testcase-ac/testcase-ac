#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300000, "M");
    ensuref((long long)M <= N, "Constraint violation: M (%d) must be <= N (%lld)", M, N);
    inf.readEoln();

    // Read the counts for each color
    for (int i = 0; i < M; i++) {
        char namebuf[20];
        snprintf(namebuf, sizeof(namebuf), "K_%d", i+1);
        long long k = inf.readLong(1LL, 1000000000LL, namebuf);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
