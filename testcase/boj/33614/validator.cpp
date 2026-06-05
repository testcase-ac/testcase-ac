#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    long long sumP = 0;
    long long sumQ = 0;
    long long sumR = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int p = inf.readInt(1, 10000000, "p");
        inf.readSpace();
        int q = inf.readInt(1, 10000000, "q");
        inf.readSpace();
        int r = inf.readInt(1, 10000000, "r");
        inf.readEoln();

        sumP += p;
        sumQ += q;
        sumR += r;
    }

    ensuref(sumP <= 10000000LL, "sum of p values is %lld, exceeds 10000000", sumP);
    ensuref(sumQ <= 10000000LL, "sum of q values is %lld, exceeds 10000000", sumQ);
    ensuref(sumR <= 10000000LL, "sum of r values is %lld, exceeds 10000000", sumR);

    inf.readEof();
}
