#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int maxM = min(N * (N - 1) / 2, 1000);
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();

    // 2. Read p_i
    int maxMin = max(min(N-1, M), 1);
    long long pLow = -10000000LL * maxMin;
    long long pHigh = 10000000LL * maxMin;
    vector<long long> p(N);
    for (int i = 0; i < N; ++i) {
        p[i] = inf.readLong(pLow, pHigh, format("p_%d", i+1).c_str());
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read edges, check for no loops and no multiple edges
    set<pair<int,int>> edgeSet;
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, format("u_%d", i+1).c_str());
        inf.readSpace();
        int v = inf.readInt(1, N, format("v_%d", i+1).c_str());
        inf.readSpace();
        int s = inf.readInt(0, 10000000, format("s_%d", i+1).c_str());
        inf.readSpace();
        int e = inf.readInt(s, 10000000, format("e_%d", i+1).c_str());
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d, %d)", i+1, u, v);
        ensuref(!edgeSet.count({u, v}), "Multiple edges detected between %d and %d (edge %d)", u, v, i+1);
        edgeSet.insert({u, v});
    }

    inf.readEof();
}
