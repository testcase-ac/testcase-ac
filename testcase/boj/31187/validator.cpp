#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T_MAX = 100000;
    const int N_MAX = 1000000;
    const long long A_MIN = -1000000000LL;
    const long long A_MAX =  1000000000LL;

    long long sumN = 0;

    int T = inf.readInt(1, T_MAX, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, N_MAX, "n");
        inf.readEoln();
        sumN += n;
        ensuref(sumN <= N_MAX,
                "Sum of n over all test cases exceeds %d (currently %lld)",
                N_MAX, sumN);

        vector<long long> a = inf.readLongs(n, A_MIN, A_MAX, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
