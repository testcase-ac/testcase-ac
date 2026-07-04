#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 200000, "m");
    inf.readEoln();

    long long vertexCount = 1LL * n * m;
    ensuref(vertexCount <= 200000, "n * m must not exceed 200000, got %lld", vertexCount);

    long long edgeCount = 1LL * n * (m - 1) + 1LL * (n - 1) * m;
    set<pair<int, int>> edges;

    for (long long i = 1; i <= edgeCount; ++i) {
        int u = inf.readInt(1, static_cast<int>(vertexCount), "u_i");
        inf.readSpace();
        int v = inf.readInt(1, static_cast<int>(vertexCount), "v_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge index %lld: (%d, %d)", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %lld: (%d, %d)", i, u, v);
    }

    inf.readEof();
}
