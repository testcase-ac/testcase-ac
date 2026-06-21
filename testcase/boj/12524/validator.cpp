#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 1000, "N");
        inf.readEoln();

        vector<int> F = inf.readInts(N, 1, N, "F_i");
        inf.readEoln();

        for (int i = 0; i < N; ++i) {
            ensuref(F[i] != i + 1, "monk %d immediately follows himself", i + 1);
        }
    }

    inf.readEof();
    return 0;
}
