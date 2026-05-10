#include "testlib.h"
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(2, 500, "N");
    inf.readSpace();
    int maxM = N * (N - 1) / 2;
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();

    // 2. Read M edges, check 1 <= a, b <= N, a != b, no multiedges, undirected
    set<pair<int, int>> edges;
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();

        ensuref(a != b, "Edge %d: loop detected (%d, %d)", i+1, a, b);
        int u = min(a, b), v = max(a, b);
        ensuref(edges.count({u, v}) == 0, "Edge %d: duplicate edge (%d, %d)", i+1, u, v);
        edges.insert({u, v});
    }

    inf.readEof();
}
