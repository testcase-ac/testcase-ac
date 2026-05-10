#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, A, B
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readEoln();

    ensuref(A + B == N, "A + B must be equal to N, but got A=%d, B=%d, N=%d", A, B, N);

    for (int i = 0; i < N; ++i) {
        int p = inf.readInt(1, 1000000000, "p_i");
        inf.readSpace();
        int q = inf.readInt(1, 1000000000, "q_i");
        inf.readEoln();
    }

    inf.readEof();
}
