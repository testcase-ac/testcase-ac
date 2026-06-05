#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalColors = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(3, 1000, "N");
        inf.readEoln();

        totalColors += 1LL * N * (N - 1) / 2;
        // CHECK: T has no statement upper bound; cap total matrix entries by local size policy.
        ensuref(totalColors < 5000000LL,
                "too many color entries across test cases: %lld", totalColors);

        for (int i = 1; i <= N - 1; ++i) {
            int rowLength = N - i;
            for (int j = 0; j < rowLength; ++j) {
                inf.readInt(0, 1, "color");
                if (j + 1 < rowLength) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
