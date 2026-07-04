#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    for (int i = 1; i <= K; ++i) {
        int P = inf.readInt(1, N, "P_i");
        inf.readSpace();
        int S = inf.readInt(1, 1000000, "S_i");
        inf.readEoln();

        // CHECK: the statement does not require initial positions or sizes to be distinct.
        (void)P;
        (void)S;
    }

    inf.readEof();
}
