#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and T
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int T = inf.readInt(N, 100000000, "T"); // T >= N
    inf.readEoln();

    // Read the carrot parameters
    for (int i = 1; i <= N; i++) {
        int w = inf.readInt(1, 100, "w_i");
        inf.readSpace();
        int p = inf.readInt(1, 100, "p_i");
        inf.readEoln();
        ensuref(p >= w,
                "At line %d: p_i (%d) must be at least w_i (%d)", 
                i+1, p, w);
    }

    inf.readEof();
    return 0;
}
