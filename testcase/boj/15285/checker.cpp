#include "testlib.h"

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct TestCase {
    int n;
    int m;
    vector<Edge> edges;
    unordered_map<long long, int> edgeIndex;
};

vector<TestCase> cases;

long long edgeKey(int from, int to) {
    return (static_cast<long long>(from) << 32) ^ static_cast<unsigned int>(to);
}

bool reachesAll(int n, const vector<vector<int>>& graph) {
    vector<int> seen(n + 1, 0);
    queue<int> q;
    seen[1] = 1;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (!seen[to]) {
                seen[to] = 1;
                q.push(to);
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        if (!seen[v]) {
            return false;
        }
    }
    return true;
}

void validateStronglyConnected(const TestCase& tc, const vector<int>& removed, InStream& stream, int caseIndex) {
    vector<vector<int>> graph(tc.n + 1), reverseGraph(tc.n + 1);

    for (int i = 0; i < tc.m; ++i) {
        if (removed[i]) {
            continue;
        }
        const Edge& edge = tc.edges[i];
        graph[edge.from].push_back(edge.to);
        reverseGraph[edge.to].push_back(edge.from);
    }

    if (!reachesAll(tc.n, graph)) {
        stream.quitf(_wa, "case %d: remaining roads are not reachable from city 1", caseIndex);
    }
    if (!reachesAll(tc.n, reverseGraph)) {
        stream.quitf(_wa, "case %d: city 1 is not reachable from every city", caseIndex);
    }
}

void readClaim(InStream& stream, int caseIndex) {
    const TestCase& tc = cases[caseIndex - 1];
    vector<int> removed(tc.m, 0);
    const int need = tc.m - 2 * tc.n;

    for (int i = 0; i < need; ++i) {
        int from = stream.readInt(1, tc.n, format("case %d abandoned road %d source", caseIndex, i + 1).c_str());
        int to = stream.readInt(1, tc.n, format("case %d abandoned road %d destination", caseIndex, i + 1).c_str());

        auto it = tc.edgeIndex.find(edgeKey(from, to));
        if (it == tc.edgeIndex.end()) {
            stream.quitf(_wa, "case %d: road %d (%d, %d) is not in the input", caseIndex, i + 1, from, to);
        }
        if (removed[it->second]) {
            stream.quitf(_wa, "case %d: road (%d, %d) is abandoned more than once", caseIndex, from, to);
        }
        removed[it->second] = 1;
    }

    validateStronglyConnected(tc, removed, stream, caseIndex);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    cases.resize(testCount);

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        TestCase& tc = cases[caseIndex - 1];
        tc.n = inf.readInt();
        tc.m = inf.readInt();
        tc.edges.resize(tc.m);
        tc.edgeIndex.reserve(tc.m * 2);

        for (int i = 0; i < tc.m; ++i) {
            int from = inf.readInt();
            int to = inf.readInt();
            tc.edges[i] = {from, to};
            tc.edgeIndex[edgeKey(from, to)] = i;
        }
    }

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        readClaim(ans, caseIndex);
    }
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        readClaim(ouf, caseIndex);
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d test case(s) have valid abandoned road sets", testCount);
}
