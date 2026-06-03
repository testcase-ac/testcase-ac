#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 10, "N");
        inf.readEoln();

        vector<int> A = inf.readInts(N, 1, N, "A_i");
        inf.readEoln();

        vector<bool> seen(N + 1, false);
        for (int i = 0; i < N; ++i) {
            ensuref(!seen[A[i]], "duplicate value %d at position %d", A[i], i + 1);
            seen[A[i]] = true;
        }
    }

    inf.readEof();
    return 0;
}
