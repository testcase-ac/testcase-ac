#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_Q = 100000;
    const long long MAX_TASTE = 2147483647LL;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, MAX_TASTE, "A_i");
    inf.readEoln();
    vector<long long> b = inf.readLongs(n, 1LL, MAX_TASTE, "B_j");
    inf.readEoln();

    for (int idx = 1; idx < n; ++idx) {
        ensuref(a[idx - 1] < a[idx],
                "A must be strictly increasing: A_%d=%lld, A_%d=%lld",
                idx, a[idx - 1], idx + 1, a[idx]);
        ensuref(b[idx - 1] < b[idx],
                "B must be strictly increasing: B_%d=%lld, B_%d=%lld",
                idx, b[idx - 1], idx + 1, b[idx]);
    }

    vector<long long> all;
    all.reserve(2 * n);
    all.insert(all.end(), a.begin(), a.end());
    all.insert(all.end(), b.begin(), b.end());
    sort(all.begin(), all.end());
    for (int idx = 1; idx < 2 * n; ++idx) {
        ensuref(all[idx - 1] != all[idx], "food taste values must be unique: %lld", all[idx]);
    }

    int q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    for (int query = 1; query <= q; ++query) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readSpace();
        int k = inf.readInt(1, i + j, "k");
        inf.readEoln();
    }

    inf.readEof();
}
