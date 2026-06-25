#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxSum = 100000;

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    long long sumD = 0;
    long long sumK = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int D = inf.readInt(1, maxSum, "D");
        inf.readSpace();
        int K = inf.readInt(1, maxSum, "K");
        inf.readEoln();

        string N = inf.readToken("[0-9]{1,100000}", "N");
        inf.readEoln();

        ensuref((int)N.size() == D,
                "case %d: N has %d digits, expected D=%d",
                tc, (int)N.size(), D);
        ensuref(N[0] != '0', "case %d: N must be a D-digit positive integer", tc);

        sumD += D;
        sumK += K;
        ensuref(sumD <= maxSum, "sum of D exceeds %d at case %d", maxSum, tc);
        ensuref(sumK <= maxSum, "sum of K exceeds %d at case %d", maxSum, tc);
    }

    inf.readEof();
    return 0;
}
