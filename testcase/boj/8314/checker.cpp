#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int n, m;
vector<pair<int, int>> edges;

struct Output {
    int k;
};

void ensureAcyclic(InStream& stream, const vector<int>& group, int groupIndex) {
    vector<int> touched;
    for (int edgeIndex : group) {
        touched.push_back(edges[edgeIndex].first);
        touched.push_back(edges[edgeIndex].second);
    }

    sort(touched.begin(), touched.end());
    touched.erase(unique(touched.begin(), touched.end()), touched.end());

    vector<vector<int>> graph(touched.size());
    vector<int> indegree(touched.size(), 0);
    for (int edgeIndex : group) {
        int u = lower_bound(touched.begin(), touched.end(), edges[edgeIndex].first) - touched.begin();
        int v = lower_bound(touched.begin(), touched.end(), edges[edgeIndex].second) - touched.begin();
        graph[u].push_back(v);
        ++indegree[v];
    }

    queue<int> q;
    for (int i = 0; i < (int)touched.size(); ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++visited;

        for (int v : graph[u]) {
            --indegree[v];
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (visited != (int)touched.size()) {
        stream.quitf(_wa, "group %d contains a directed cycle", groupIndex);
    }
}

Output readOutput(InStream& stream) {
    int k = stream.readInt(1, m, "k");

    vector<int> seen(m + 1, 0);
    vector<vector<int>> groups(k);

    for (int i = 0; i < k; ++i) {
        int length = stream.readInt(1, m, format("l_%d", i + 1).c_str());
        groups[i].reserve(length);

        int previous = 0;
        for (int j = 0; j < length; ++j) {
            int edgeIndex = stream.readInt(1, m, format("edge[%d][%d]", i + 1, j + 1).c_str());
            if (edgeIndex <= previous) {
                stream.quitf(_wa,
                             "edge numbers in group %d are not strictly increasing at position %d",
                             i + 1,
                             j + 1);
            }
            if (seen[edgeIndex]) {
                stream.quitf(_wa,
                             "edge %d appears in both group %d and group %d",
                             edgeIndex,
                             seen[edgeIndex],
                             i + 1);
            }
            previous = edgeIndex;
            seen[edgeIndex] = i + 1;
            groups[i].push_back(edgeIndex);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after decomposition");
    }

    for (int edgeIndex = 1; edgeIndex <= m; ++edgeIndex) {
        if (!seen[edgeIndex]) {
            stream.quitf(_wa, "edge %d is missing from the decomposition", edgeIndex);
        }
    }

    for (int i = 0; i < k; ++i) {
        ensureAcyclic(stream, groups[i], i + 1);
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.assign(m + 1, {0, 0});
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges[i] = {u, v};
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (participant.k != jury.k) {
        quitf(_wa, "expected k=%d, found k=%d", jury.k, participant.k);
    }

    quitf(_ok, "valid decomposition into %d acyclic graphs", participant.k);
}
