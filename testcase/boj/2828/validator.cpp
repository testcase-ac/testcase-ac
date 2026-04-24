#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    ensuref(M < N, "Constraint violated: M (%d) must be less than N (%d)", M, N);
    inf.readEoln();

    // Read J
    int J = inf.readInt(1, 20, "J");
    inf.readEoln();

    // Read the J apple drop positions
    for (int i = 0; i < J; i++) {
        char buf[32];
        std::sprintf(buf, "x_%d", i+1);
        int x = inf.readInt(1, N, buf);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
