#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int to;
    int weight;
};

struct Output {
    bool impossible;
    vector<int> path;
};

int n, m;
vector<vector<Edge>> graph;
set<pair<int, int>> edges;
vector<int> signNext;

vector<long long> shortestDistances() {
    const long long infDist = (1LL << 62);
    vector<long long> dist(n, infDist);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;
    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [curDist, v] = pq.top();
        pq.pop();
        if (curDist != dist[v]) {
            continue;
        }
        for (const Edge& edge : graph[v]) {
            long long nextDist = curDist + edge.weight;
            if (dist[edge.to] > nextDist) {
                dist[edge.to] = nextDist;
                pq.push({nextDist, edge.to});
            }
        }
    }
    return dist;
}

void buildSigns() {
    vector<long long> dist = shortestDistances();
    vector<int> component(n, -1);
    vector<vector<int>> vertices;

    for (int start = 0; start < n; ++start) {
        if (component[start] != -1) {
            continue;
        }

        int id = int(vertices.size());
        vertices.push_back({});
        vector<int> stack = {start};
        component[start] = id;

        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            vertices[id].push_back(v);
            for (const Edge& edge : graph[v]) {
                if (edge.weight != 0 || dist[v] != dist[edge.to] ||
                    component[edge.to] != -1) {
                    continue;
                }
                component[edge.to] = id;
                stack.push_back(edge.to);
            }
        }
    }

    signNext.assign(n, -1);
    for (const vector<int>& compVertices : vertices) {
        int terminal = -1;
        int terminalNext = -1;

        for (int v : compVertices) {
            if (v == 1) {
                terminal = v;
                terminalNext = -1;
                break;
            }
            for (const Edge& edge : graph[v]) {
                if (component[v] != component[edge.to] &&
                    dist[v] == dist[edge.to] + edge.weight) {
                    if (terminal != -1) {
                        quitf(_fail, "multiple shortest-route terminals in component");
                    }
                    terminal = v;
                    terminalNext = edge.to;
                }
            }
        }

        if (terminal == -1) {
            quitf(_fail, "component has no shortest-route terminal");
        }
        signNext[terminal] = terminalNext;

        queue<int> q;
        q.push(terminal);
        vector<int> seen(n, 0);
        seen[terminal] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const Edge& edge : graph[v]) {
                if (component[edge.to] != component[terminal] || edge.weight != 0 ||
                    dist[edge.to] != dist[v] || seen[edge.to]) {
                    continue;
                }
                seen[edge.to] = 1;
                signNext[edge.to] = v;
                q.push(edge.to);
            }
        }
    }
}

Output readOutput(InStream& stream) {
    string first = stream.readToken("[A-Za-z0-9]+", "first output token");
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true, {}};
    }

    int k = 0;
    try {
        size_t pos = 0;
        k = stoi(first, &pos);
        if (pos != first.size()) {
            stream.quitf(_wa, "path length is not an integer");
        }
    } catch (...) {
        stream.quitf(_wa, "expected path length or impossible, found '%s'",
                     first.c_str());
    }

    if (k < 2 || k > n) {
        stream.quitf(_wa, "path length %d is outside [2, %d]", k, n);
    }

    vector<int> path(k);
    vector<int> used(n, 0);
    for (int i = 0; i < k; ++i) {
        path[i] = stream.readInt(0, n - 1, format("p[%d]", i).c_str());
        if (used[path[i]]) {
            stream.quitf(_wa, "vertex %d appears more than once", path[i]);
        }
        used[path[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after path");
    }

    if (path.front() != 0) {
        stream.quitf(_wa, "path starts at %d instead of 0", path.front());
    }
    if (path.back() != 1) {
        stream.quitf(_wa, "path ends at %d instead of 1", path.back());
    }

    for (int i = 0; i + 1 < k; ++i) {
        int a = path[i];
        int b = path[i + 1];
        if (!edges.count(minmax(a, b))) {
            stream.quitf(_wa, "road (%d, %d) does not exist", a, b);
        }
        if (signNext[a] == b) {
            stream.quitf(_wa, "step %d from %d to %d follows the sign", i, a, b);
        }
    }

    return {false, path};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    graph.assign(n, {});
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        int d = inf.readInt();
        graph[a].push_back({b, d});
        graph[b].push_back({a, d});
        edges.insert(minmax(a, b));
    }

    buildSigns();

    Output jury = readOutput(ans);
    Output part = readOutput(ouf);

    if (jury.impossible) {
        if (part.impossible) {
            quitf(_ok, "both outputs say impossible");
        }
        quitf(_fail, "participant found a valid path while jury says impossible");
    }

    if (part.impossible) {
        quitf(_wa, "jury has a valid path but participant says impossible");
    }

    quitf(_ok, "valid detour path of length %d", int(part.path.size()));
}
