#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int n;
vector<int> expectedDegree;

struct Answer {
    int edgeCount;
};

Answer readAnswer(InStream& stream) {
    vector<int> degree(n + 1, 0);
    set<pair<int, int>> edges;

    int expectedEdges = 0;
    for (int i = 1; i <= n; ++i) {
        expectedEdges += expectedDegree[i];
    }
    expectedEdges /= 2;

    for (int i = 0; i < expectedEdges; ++i) {
        int u = stream.readInt(1, n, format("edge[%d].u", i + 1).c_str());
        int v = stream.readInt(1, n, format("edge[%d].v", i + 1).c_str());

        if (u == v) {
            stream.quitf(_wa, "edge %d is a loop at town %d", i + 1, u);
        }
        if (u > v) {
            swap(u, v);
        }
        if (!edges.insert({u, v}).second) {
            stream.quitf(_wa, "edge %d duplicates connection %d %d", i + 1, u, v);
        }

        ++degree[u];
        ++degree[v];
        if (degree[u] > expectedDegree[u]) {
            stream.quitf(_wa, "town %d has too many connections: expected %d", u, expectedDegree[u]);
        }
        if (degree[v] > expectedDegree[v]) {
            stream.quitf(_wa, "town %d has too many connections: expected %d", v, expectedDegree[v]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (degree[i] != expectedDegree[i]) {
            stream.quitf(_wa,
                         "town %d has degree %d instead of %d",
                         i,
                         degree[i],
                         expectedDegree[i]);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra data after %d edges", expectedEdges);
    }

    return {expectedEdges};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(3, 500, "n");
    expectedDegree.assign(n + 1, 0);

    int degreeSum = 0;
    for (int i = 1; i <= n; ++i) {
        expectedDegree[i] = inf.readInt(0, n - 1, format("d[%d]", i).c_str());
        degreeSum += expectedDegree[i];
    }

    if (degreeSum % 2 != 0) {
        quitf(_fail, "input degree sum is odd: %d", degreeSum);
    }

    readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid graph with %d edges", participant.edgeCount);
}
