#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, Q
    int N = inf.readInt(2, 500, "N");
    inf.readSpace();
    int M = inf.readInt(0, 10000, "M");
    inf.readSpace();
    int Q = inf.readInt(0, 40000, "Q");
    inf.readEoln();

    // 2. Read N integers: annoyance times
    for (int i = 1; i <= N; ++i) {
        inf.readInt(1, 10000, "annoy_i");
        if (i < N) inf.readSpace();
        else inf.readEoln();
    }

    // 3. Read M roads: a, b, d
    for (int i = 0; i < M; ++i) {
        inf.readInt(1, N, "a");
        inf.readSpace();
        inf.readInt(1, N, "b");
        inf.readSpace();
        inf.readInt(1, 10000, "d");
        inf.readEoln();
    }

    // 4. Read Q queries: S, T
    for (int i = 0; i < Q; ++i) {
        inf.readInt(1, N, "S");
        inf.readSpace();
        inf.readInt(1, N, "T");
        inf.readEoln();
    }

    inf.readEof();
}
