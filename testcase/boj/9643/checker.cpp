#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

struct TestCase {
    int n;
    vector<vector<int>> dist;
};

vector<Edge> readRoads(InStream& stream, int tc, int n) {
    vector<Edge> edges;
    edges.reserve(n);
    for (int i = 0; i < n; ++i) {
        int u = stream.readInt(1, n, format("case %d road[%d].a", tc, i + 1).c_str());
        int v = stream.readInt(1, n, format("case %d road[%d].b", tc, i + 1).c_str());
        int w = stream.readInt(1, 1000000, format("case %d road[%d].c", tc, i + 1).c_str());
        if (u == v) {
            stream.quitf(_wa, "case %d road %d is a self-loop at city %d", tc, i + 1, u);
        }
        edges.push_back({u - 1, v - 1, w});
    }
    return edges;
}

void validateRoadNetwork(InStream& stream, const TestCase& tc, const vector<Edge>& edges, int caseNo) {
    const long long INF = (1LL << 60);
    vector<vector<pair<int, int>>> graph(tc.n);
    for (const Edge& edge : edges) {
        graph[edge.u].push_back({edge.v, edge.w});
        graph[edge.v].push_back({edge.u, edge.w});
    }

    vector<long long> d(tc.n);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    for (int source = 0; source < tc.n; ++source) {
        fill(d.begin(), d.end(), INF);
        d[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [du, u] = pq.top();
            pq.pop();
            if (du != d[u]) {
                continue;
            }
            for (auto [v, w] : graph[u]) {
                if (d[v] > du + w) {
                    d[v] = du + w;
                    pq.push({d[v], v});
                }
            }
        }

        for (int target = 0; target < tc.n; ++target) {
            if (d[target] != tc.dist[source][target]) {
                stream.quitf(_wa,
                             "case %d distance %d->%d is %lld, expected %d",
                             caseNo,
                             source + 1,
                             target + 1,
                             d[target],
                             tc.dist[source][target]);
            }
        }
    }
}

void readAndValidateOutput(InStream& stream, const vector<TestCase>& tests) {
    for (int tc = 0; tc < (int)tests.size(); ++tc) {
        vector<Edge> edges = readRoads(stream, tc + 1, tests[tc].n);
        validateRoadNetwork(stream, tests[tc], edges, tc + 1);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the last test case");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    vector<TestCase> tests;
    while (!inf.seekEof()) {
        int n = inf.readInt(2, 2000, "N");
        TestCase tc;
        tc.n = n;
        tc.dist.assign(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                tc.dist[i][j] = inf.readInt(0, 1000000, format("dist[%d][%d]", i + 1, j + 1).c_str());
            }
        }
        tests.push_back(std::move(tc));
    }

    readAndValidateOutput(ans, tests);
    readAndValidateOutput(ouf, tests);

    quitf(_ok, "%d test case(s) matched the supplied distance tables", (int)tests.size());
}
