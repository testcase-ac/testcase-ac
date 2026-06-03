#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 10000;
    const int MAX_N = 500000;
    const long long MAX_VALUE = 1000000000LL;

    int t = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, MAX_N, "N");
        inf.readSpace();
        inf.readLong(0LL, MAX_VALUE, "K");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= MAX_N, "sum of N exceeds %d at case %d", MAX_N, tc);

        inf.readInts(n, 1, 2, "C_i");
        inf.readEoln();

        inf.readLongs(n, 0LL, MAX_VALUE, "W_i");
        inf.readEoln();
    }

    inf.readEof();
}
