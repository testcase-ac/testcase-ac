#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T_MAX = 100000;
    const int N_MAX = 200000;
    const long long A_MIN = -1000000000LL;
    const long long A_MAX =  1000000000LL;

    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    long long sumN = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, N_MAX, "N");
        inf.readEoln();

        sumN += N;
        ensuref(sumN <= N_MAX,
                "Sum of N over all test cases exceeds %d: current sum = %lld at test %d",
                N_MAX, sumN, tc);

        // Read array A_1..A_N
        vector<long long> A = inf.readLongs(N, A_MIN, A_MAX, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
