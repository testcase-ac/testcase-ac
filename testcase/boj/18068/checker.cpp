#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <set>
#include <vector>

using namespace std;

struct Node {
    long long x;
    long double y;
};

int treapHeight(vector<Node> nodes) {
    sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
        return a.x < b.x;
    });

    const int n = (int)nodes.size();
    vector<int> parent(n, -1), leftChild(n, -1), rightChild(n, -1);
    vector<int> stack;

    for (int i = 0; i < n; ++i) {
        int last = -1;
        while (!stack.empty() && stack.back() >= 0 && nodes[stack.back()].y < nodes[i].y) {
            last = stack.back();
            stack.pop_back();
        }
        if (!stack.empty()) {
            rightChild[stack.back()] = i;
            parent[i] = stack.back();
        }
        if (last != -1) {
            leftChild[i] = last;
            parent[last] = i;
        }
        stack.push_back(i);
    }

    int root = -1;
    for (int i = 0; i < n; ++i) {
        if (parent[i] == -1) {
            root = i;
            break;
        }
    }

    int height = 0;
    vector<pair<int, int>> dfs{{root, 1}};
    while (!dfs.empty()) {
        auto [v, depth] = dfs.back();
        dfs.pop_back();
        height = max(height, depth);
        if (leftChild[v] != -1) {
            dfs.push_back({leftChild[v], depth + 1});
        }
        if (rightChild[v] != -1) {
            dfs.push_back({rightChild[v], depth + 1});
        }
    }
    return height;
}

bool readClaim(InStream& stream, int n) {
    vector<Node> nodes;
    nodes.reserve(n);
    set<long long> used;

    for (int i = 0; i < n; ++i) {
        long long x = stream.readLong((long long)INT32_MIN, (long long)INT32_MAX,
                                      format("key[%d]", i + 1).c_str());
        if (!used.insert(x).second) {
            stream.quitf(_wa, "key[%d]=%lld is repeated", i + 1, x);
        }
        nodes.push_back({x, sinl((long double)x)});
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d keys", n);
    }

    return treapHeight(nodes) == n;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    bool juryValid = readClaim(ans, n);
    if (!juryValid) {
        quitf(_fail, "jury output does not form a treap of height %d", n);
    }

    bool participantValid = readClaim(ouf, n);
    if (!participantValid) {
        quitf(_wa, "participant output does not form a treap of height %d", n);
    }

    quitf(_ok, "valid treap of height %d", n);
}
