#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct Claim {
    int vertices;
    int maxDepth;
};

int inputLimit;
vector<vector<int>> graph;
vector<int> componentMark;
vector<int> distFromStart;
vector<int> parentInBfs;
int currentMark = 0;

TResult failVerdict(InStream& stream) {
    return &stream == &ans ? _fail : _wa;
}

int bfsFarthest(int start) {
    queue<int> q;
    vector<int> touched;

    distFromStart[start] = 0;
    parentInBfs[start] = 0;
    touched.push_back(start);
    q.push(start);

    int best = start;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (distFromStart[node] > distFromStart[best] ||
            (distFromStart[node] == distFromStart[best] && node < best)) {
            best = node;
        }

        for (int next : graph[node]) {
            if (componentMark[next] != currentMark || distFromStart[next] != -1) {
                continue;
            }
            distFromStart[next] = distFromStart[node] + 1;
            parentInBfs[next] = node;
            touched.push_back(next);
            q.push(next);
        }
    }

    for (int node : touched) {
        distFromStart[node] = -1;
    }
    return best;
}

int findCenter(const vector<int>& nodes) {
    ++currentMark;
    for (int node : nodes) {
        componentMark[node] = currentMark;
    }

    int firstEnd = bfsFarthest(nodes[0]);
    int secondEnd = bfsFarthest(firstEnd);

    vector<int> path;
    for (int node = secondEnd; node != 0; node = parentInBfs[node]) {
        path.push_back(node);
        if (node == firstEnd) {
            break;
        }
    }

    int edgeCount = static_cast<int>(path.size()) - 1;
    if (edgeCount % 2 == 0) {
        return path[edgeCount / 2];
    }
    return min(path[edgeCount / 2], path[edgeCount / 2 + 1]);
}

int computeMaxCenterDepth(int vertexCount) {
    componentMark.assign(vertexCount + 1, 0);
    distFromStart.assign(vertexCount + 1, -1);
    parentInBfs.assign(vertexCount + 1, 0);
    currentMark = 0;

    vector<int> all(vertexCount);
    iota(all.begin(), all.end(), 1);

    vector<pair<vector<int>, int>> stack;
    stack.push_back({all, 1});

    int maxDepth = 0;
    while (!stack.empty()) {
        vector<int> nodes = std::move(stack.back().first);
        int depth = stack.back().second;
        stack.pop_back();

        maxDepth = max(maxDepth, depth);
        if (nodes.size() == 1) {
            continue;
        }

        int center = findCenter(nodes);
        ++currentMark;
        for (int node : nodes) {
            if (node != center) {
                componentMark[node] = currentMark;
            }
        }

        for (int neighbor : graph[center]) {
            if (componentMark[neighbor] != currentMark) {
                continue;
            }

            vector<int> child;
            queue<int> q;
            componentMark[neighbor] = 0;
            q.push(neighbor);
            child.push_back(neighbor);

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (int next : graph[node]) {
                    if (componentMark[next] != currentMark) {
                        continue;
                    }
                    componentMark[next] = 0;
                    child.push_back(next);
                    q.push(next);
                }
            }

            stack.push_back({std::move(child), depth + 1});
        }
    }

    return maxDepth;
}

Claim readClaim(InStream& stream) {
    int vertexCount = stream.readInt(1, inputLimit, "m");

    graph.assign(vertexCount + 1, {});
    vector<int> parent(vertexCount + 1);
    iota(parent.begin(), parent.end(), 0);

    auto findRoot = [&](int node) {
        int root = node;
        while (parent[root] != root) {
            root = parent[root];
        }
        while (parent[node] != node) {
            int next = parent[node];
            parent[node] = root;
            node = next;
        }
        return root;
    };

    for (int i = 0; i < vertexCount - 1; ++i) {
        int u = stream.readInt(1, vertexCount, format("edge[%d].u", i + 1).c_str());
        int v = stream.readInt(1, vertexCount, format("edge[%d].v", i + 1).c_str());
        if (u == v) {
            stream.quitf(failVerdict(stream), "edge %d is a self-loop at vertex %d", i + 1, u);
        }

        int rootU = findRoot(u);
        int rootV = findRoot(v);
        if (rootU == rootV) {
            stream.quitf(failVerdict(stream), "edge %d creates a cycle", i + 1);
        }
        parent[rootU] = rootV;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    if (!stream.seekEof()) {
        stream.quitf(failVerdict(stream), "extra tokens after the tree description");
    }

    int root = findRoot(1);
    for (int node = 2; node <= vertexCount; ++node) {
        if (findRoot(node) != root) {
            stream.quitf(failVerdict(stream), "the graph is not connected");
        }
    }

    return {vertexCount, computeMaxCenterDepth(vertexCount)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    inputLimit = inf.readInt(1, 100000, "n");
    int requiredDepth = static_cast<int>(sqrt(inputLimit));
    while (1LL * (requiredDepth + 1) * (requiredDepth + 1) <= inputLimit) {
        ++requiredDepth;
    }
    while (1LL * requiredDepth * requiredDepth > inputLimit) {
        --requiredDepth;
    }

    Claim jury = readClaim(ans);
    if (jury.maxDepth < requiredDepth) {
        quitf(_fail,
              "jury tree reaches only %d center-decomposition levels, required %d",
              jury.maxDepth,
              requiredDepth);
    }

    Claim participant = readClaim(ouf);
    if (participant.maxDepth < requiredDepth) {
        quitf(_wa,
              "tree reaches only %d center-decomposition levels, required %d",
              participant.maxDepth,
              requiredDepth);
    }

    quitf(_ok,
          "m=%d, center-decomposition levels=%d",
          participant.vertices,
          participant.maxDepth);
}
