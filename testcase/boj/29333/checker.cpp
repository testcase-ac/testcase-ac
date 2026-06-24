#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
};

struct Claim {
    bool impossible;
    bool validWitness;
};

int n, m, s, e;
vector<Edge> edges;

Claim readClaim(InStream& stream, TResult invalidVerdict) {
    int first = stream.readInt(-1, 1, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(invalidVerdict, "extra output after -1");
        }
        return {true, false};
    }

    vector<int> bits(m);
    bits[0] = first;
    for (int i = 1; i < m; ++i) {
        bits[i] = stream.readInt(0, 1, format("direction[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after direction list");
    }

    vector<vector<int>> graph(n + 1), reverseGraph(n + 1);
    for (int i = 0; i < m; ++i) {
        int from = bits[i] == 0 ? edges[i].u : edges[i].v;
        int to = bits[i] == 0 ? edges[i].v : edges[i].u;
        graph[from].push_back(to);
        reverseGraph[to].push_back(from);
    }

    vector<char> reachableFromS(n + 1, 0), reachesE(n + 1, 0);
    queue<int> q;
    reachableFromS[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (!reachableFromS[to]) {
                reachableFromS[to] = 1;
                q.push(to);
            }
        }
    }

    reachesE[e] = 1;
    q.push(e);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : reverseGraph[v]) {
            if (!reachesE[to]) {
                reachesE[to] = 1;
                q.push(to);
            }
        }
    }

    if (!reachableFromS[e]) {
        stream.quitf(invalidVerdict, "there is no walk from S=%d to E=%d", s, e);
    }

    vector<char> useful(n + 1, 0);
    queue<int> topo;
    int usefulCount = 0;
    for (int v = 1; v <= n; ++v) {
        useful[v] = reachableFromS[v] && reachesE[v];
        if (useful[v]) {
            ++usefulCount;
        }
    }

    vector<int> usefulIndegree(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (!useful[v]) {
            continue;
        }
        for (int to : graph[v]) {
            if (useful[to]) {
                ++usefulIndegree[to];
            }
        }
    }
    for (int v = 1; v <= n; ++v) {
        if (useful[v] && usefulIndegree[v] == 0) {
            topo.push(v);
        }
    }

    vector<int> order;
    order.reserve(usefulCount);
    while (!topo.empty()) {
        int v = topo.front();
        topo.pop();
        order.push_back(v);
        for (int to : graph[v]) {
            if (useful[to] && --usefulIndegree[to] == 0) {
                topo.push(to);
            }
        }
    }

    if ((int)order.size() != usefulCount) {
        stream.quitf(invalidVerdict,
                     "a directed cycle lies on an S-to-E walk, so multiple walks exist");
    }

    vector<int> ways(n + 1, 0);
    ways[s] = 1;
    for (int v : order) {
        for (int to : graph[v]) {
            if (useful[to]) {
                ways[to] = min(2, ways[to] + ways[v]);
            }
        }
    }

    if (ways[e] != 1) {
        stream.quitf(invalidVerdict,
                     "there are %s walks from S=%d to E=%d",
                     ways[e] == 0 ? "no" : "multiple", s, e);
    }

    return {false, true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    s = inf.readInt();
    e = inf.readInt();
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        edges[i].u = inf.readInt();
        edges[i].v = inf.readInt();
    }

    Claim jury = readClaim(ans, _fail);
    Claim participant = readClaim(ouf, _wa);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both jury and participant report impossible");
        }
        if (participant.validWitness) {
            quitf(_fail, "participant found a valid orientation while jury reports impossible");
        }
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible but jury provides a valid orientation");
    }

    quitf(_ok, "participant provides a valid orientation with exactly one S-to-E walk");
}
