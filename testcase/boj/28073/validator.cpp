#include "testlib.h"

#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    int maxM = min(1000000LL, 1LL * n * (n - 1) / 2);
    int m = inf.readInt(0, maxM, "M");
    inf.readEoln();

    string start = inf.readToken("[A-Z]", "S");
    inf.readSpace();
    string finish = inf.readToken("[A-Z]", "E");
    inf.readEoln();

    string labels = inf.readToken("[A-Z]{2,1000000}", "labels");
    inf.readEoln();
    ensuref((int)labels.size() == n, "labels length must be N: got %d, expected %d",
            (int)labels.size(), n);
    ensuref(labels.find(start[0]) != string::npos, "labels must contain S '%c'", start[0]);
    ensuref(labels.find(finish[0]) != string::npos, "labels must contain E '%c'", finish[0]);

    unordered_set<long long> edges;
    edges.reserve((size_t)m * 2 + 1);
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u < v, "edge %d must satisfy u < v: %d %d", i, u, v);

        // CHECK: The statement gives M as the number of connection relations and
        // caps it by N(N-1)/2, so repeated pairs are rejected as duplicate relations.
        long long key = 1LL * (u - 1) * n + (v - 1);
        ensuref(edges.insert(key).second, "duplicate edge at index %d: %d %d", i, u, v);
    }

    inf.readEof();
}
