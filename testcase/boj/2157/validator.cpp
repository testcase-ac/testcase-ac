#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(2, N, "M");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read K flight descriptions
    for (int i = 0; i < K; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 10000, "c_i");
        inf.readEoln();

        ensuref(a != b,
                "Self-loop detected at edge index %d: %d -> %d", i, a, b);
    }

    inf.readEof();
    return 0;
}
