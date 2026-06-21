#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100000, "N");
        inf.readEoln();

        totalN += N;
        ensuref(totalN <= 1000000, "sum of N exceeds 1000000");

        vector<int> A = inf.readInts(N, 1, N, "A_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
