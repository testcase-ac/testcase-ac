#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    const int MAX_N = 200000;
    const long long MAX_P = 1000000000000000000LL;
    const long long MAX_C = 1000000000000000000LL;

    int T = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    long long sumN = 0;

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int N = inf.readInt(1, MAX_N, "N");
        inf.readSpace();
        long long P = inf.readLong(1LL, MAX_P, "P");
        inf.readEoln();

        sumN += N;
        ensuref(sumN <= MAX_N,
                "Sum of N over all test cases exceeds %d: current sum = %lld",
                MAX_N, sumN);

        vector<long long> C = inf.readLongs(N, 0LL, MAX_C, "C_i");
        inf.readEoln();

        ensuref(C[N - 1] != 0,
                "C_N must be nonzero, but C_N = %lld in test case %d",
                C[N - 1], tc + 1);
    }

    inf.readEof();
}
