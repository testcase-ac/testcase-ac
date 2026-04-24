#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check constraints
    int N = inf.readInt(2, 10000, "N");
    ensuref(N % 2 == 0, "N must be even, but N=%d", N);
    inf.readEoln();

    // There should be exactly N-1 cost lines
    for (int i = 1; i <= N - 1; i++) {
        int Pi = inf.readInt(0, 10000, "P_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
