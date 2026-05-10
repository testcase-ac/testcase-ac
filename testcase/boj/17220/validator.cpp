#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 26, "N");
    inf.readSpace();
    int M = inf.readInt(1, 600, "M");
    inf.readEoln();

    // Map supplier labels 'A'.. to indices 0..N-1
    auto readNode = [&](const char* name) -> int {
        string t = inf.readToken("[A-Z]", name);
        char c = t[0];
        int id = c - 'A';
        ensuref(0 <= id && id < N,
                "Node %s = '%c' (id %d) is out of allowed range A..%c for N=%d",
                name, c, id, char('A' + N - 1), N);
        return id;
    };

    vector<vector<int>> g(N);
    vector<int> indeg(N, 0);

    // Read M relations: "A B" meaning A -> B, one per line
    for (int i = 0; i < M; ++i) {
        int u = readNode("u");
        inf.readSpace();
        int v = readNode("v");
        inf.readEoln();

        // Multiple edges and self-loops are not forbidden by statement,
        // so we allow them. But we still build graph/indegree.
        g[u].push_back(v);
        indeg[v]++;
    }

    // Read last line: number of known suppliers K, then K labels
    int K = inf.readInt(0, N, "K");
    if (K > 0) inf.readSpace();
    vector<int> arrested;
    arrested.reserve(K);
    vector<bool> isArrested(N, false);

    for (int i = 0; i < K; ++i) {
        int x = readNode("arrested_i");
        if (i + 1 < K) inf.readSpace();
        // suppliers in this list should be distinct (natural assumption)
        ensuref(!isArrested[x],
                "Arrested supplier '%c' appears multiple times",
                char('A' + x));
        isArrested[x] = true;
        arrested.push_back(x);
    }
    inf.readEoln();

    // Now validate the implied global condition:
    // "마약의 원산지: 다른 공급책에게 공급받지 않으면서 마약을 공급하는 공급책"
    // i.e., at least one node with indeg == 0 and outdeg > 0.
    int originCount = 0;
    for (int i = 0; i < N; ++i) {
        if (indeg[i] == 0 && !g[i].empty())
            originCount++;
    }
    ensuref(originCount >= 1,
            "There must be at least one origin supplier (indegree 0 and outgoing >= 1), found %d",
            originCount);

    // Additionally, the problem guarantees answer always exists in terms of:
    // after arresting given suppliers, some suppliers may still receive drugs.
    // This is not strictly stated as "always at least one", so we don't enforce
    // positive count, but we can simulate and ensure that the model is consistent.

    // Simulate supply availability:
    // Origin suppliers that are not arrested initially have supply.
    vector<bool> hasSupply(N, false);
    queue<int> q;
    for (int i = 0; i < N; ++i) {
        if (indeg[i] == 0 && !g[i].empty() && !isArrested[i]) {
            hasSupply[i] = true;
            q.push(i);
        }
    }
    // BFS / multi-source propagation through directed edges,
    // skipping arrested suppliers as intermediates / receivers.
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (isArrested[v]) continue;
            if (!hasSupply[v]) {
                hasSupply[v] = true;
                q.push(v);
            }
        }
    }
    // No additional guarantee to check; simulation is mainly to
    // catch pathological inconsistencies if any further constraints
    // were implicit.

    inf.readEof();
}
