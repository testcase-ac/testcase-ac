#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxT = 100;
    const int maxSmallN = 500;
    const int maxLargeN = 5000;
    const int maxK = 1000000;

    int t = inf.readInt(1, maxT, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, maxLargeN, "N");
        inf.readSpace();
        int k = inf.readInt(1, maxK, "K");
        inf.readEoln();

        if (n > maxSmallN) {
            ++largeCases;
        }
        ensuref(largeCases <= 25, "more than 25 cases have N > 500");

        for (int i = 0; i < n; ++i) {
            inf.readInt(0, k, "B_i");
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
