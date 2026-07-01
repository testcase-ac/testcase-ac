#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxT = 100;
    const int maxLargeCases = 10;
    const int smallLimit = 1000;
    const int maxN = 300000;
    const int maxD = 300000;
    const int maxH = 300000;

    int T = inf.readInt(1, maxT, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int D = inf.readInt(1, maxD, "D");
        inf.readSpace();
        int N = inf.readInt(1, maxN, "N");
        inf.readSpace();
        int K = inf.readInt(1, N, "K");
        inf.readEoln();

        if (N > smallLimit || D > smallLimit) {
            ++largeCases;
        }

        for (int i = 1; i <= N; ++i) {
            int h = inf.readInt(1, maxH, "h_i");
            inf.readSpace();
            int s = inf.readInt(1, D, "s_i");
            inf.readSpace();
            int e = inf.readInt(s, D, "e_i");
            inf.readEoln();
        }
    }

    ensuref(largeCases <= maxLargeCases,
            "at most %d test cases may have N or D greater than %d, found %d",
            maxLargeCases, smallLimit, largeCases);

    inf.readEof();
}
