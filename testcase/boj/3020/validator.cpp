#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and H
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int H = inf.readInt(2, 500000, "H");
    inf.readEoln();

    // N must be even as per statement
    ensuref(N % 2 == 0, "N must be even, but got %d", N);

    // Read N obstacle sizes, one per line
    char buf[32];
    for (int i = 1; i <= N; i++) {
        snprintf(buf, sizeof(buf), "s_%d", i);
        // size is a positive integer less than H
        inf.readInt(1, H - 1, buf);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
