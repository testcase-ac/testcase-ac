#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 500000, "M");
    inf.readEoln();

    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readEoln();

        ensuref(A < B, "Prerequisite edge %d: A (%d) must be less than B (%d)", i + 1, A, B);
    }

    inf.readEof();
}
