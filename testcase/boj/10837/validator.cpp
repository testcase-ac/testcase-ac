#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read C
    int C = inf.readInt(1, 100000, "C");
    inf.readEoln();

    for (int i = 0; i < C; ++i) {
        int M = inf.readInt(0, K, "M");
        inf.readSpace();
        int N = inf.readInt(0, K, "N");
        inf.readEoln();

        // No further per-line constraints: M, N in [0, K]
    }

    inf.readEof();
}
