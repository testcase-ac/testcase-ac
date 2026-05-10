#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    int w;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read genders line: exactly N tokens, each "M" or "W"
    vector<char> gender(N + 1);
    for (int i = 1; i <= N; ++i) {
        string g = inf.readToken("(M|W)", "gender_i");
        ensuref(g == "M" || g == "W",
                "Invalid gender at position %d: '%s'", i, g.c_str());
        gender[i] = g[0];
        if (i != N) inf.readSpace();
    }
    inf.readEoln();

    // Read edges
    vector<Edge> edges;
    edges.reserve(M);
    vector<vector<pair<int,int>>> adj(N + 1); // adjacency list for undirected graph (for connectivity & MST)
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int d = inf.readInt(1, 1000, "d");
        inf.readEoln();

        // u and v can be equal (self-loop) unless statement forbids; it doesn't, so allow.

        edges.push_back({u, v, d});

        // For connectivity of the underlying road network, we consider all edges.
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }

    // There is no explicit guarantee in the statement that the original road graph is connected,
    // only that if no valid "사심 경로" connecting all schools exists, answer is -1.
    // So we are NOT required to enforce connectivity of the original graph or
    // existence of a valid path; that's solution's job.
    // However, we must enforce all *implied* always-true conditions; none is stated.

    // Additional semantic check based on description:
    // 사심 경로 uses only roads between male-majority and female-majority universities.
    // The input roads themselves may connect same-gender schools; that's allowed by problem,
    // since the restriction applies to the resulting path/tree, not the input graph.
    // Therefore we do not forbid same-gender edges in input.

    // Also no explicit restriction on multiple edges or self-loops; allow them.

    // Global formatting rule: EOF right after last newline already ensured by final readEof().
    inf.readEof();
}
