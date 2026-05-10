#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    long long total_N = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N
        int N = inf.readInt(2, 10000000, "N");
        inf.readEoln();

        total_N += N;
        ensuref(total_N <= 10000000, "Sum of N over all test cases exceeds 1e7, currently %lld after test case %d", total_N, tc);

        // Read S
        string S = inf.readLine("[01]{2,10000000}", "S");
        ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d) at test case %d", (int)S.size(), N, tc);

        // No further checks needed, as S is already validated by regex and length
    }

    inf.readEof();
}
