#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, m, "a_i");
    inf.readEoln();

    vector<int> b = inf.readInts(m, 1, n, "b_i");
    inf.readEoln();

    long long required = 0;
    for (int i = 0; i < m; ++i) {
        required += b[i];
    }
    ensuref(required <= n, "sum of b_i must not exceed n: %lld > %d", required, n);

    inf.readEof();
}
