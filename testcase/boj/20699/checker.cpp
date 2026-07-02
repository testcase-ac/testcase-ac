#include "testlib.h"

#include <vector>

using namespace std;

struct Claim {
    bool impossible;
};

int needWeight1;
int needWeight2;
int nodeCount;

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, 2, "first token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> weight(nodeCount + 1);
    vector<int> left(nodeCount + 1);
    vector<int> right(nodeCount + 1);
    vector<int> indegree(nodeCount + 1, 0);

    weight[1] = first;
    left[1] = stream.readInt(0, nodeCount, "left child[1]");
    right[1] = stream.readInt(0, nodeCount, "right child[1]");

    int countWeight1 = (weight[1] == 1);
    int countWeight2 = (weight[1] == 2);

    for (int i = 2; i <= nodeCount; ++i) {
        weight[i] = stream.readInt(1, 2, format("weight[%d]", i).c_str());
        left[i] = stream.readInt(0, nodeCount, format("left child[%d]", i).c_str());
        right[i] = stream.readInt(0, nodeCount, format("right child[%d]", i).c_str());

        countWeight1 += (weight[i] == 1);
        countWeight2 += (weight[i] == 2);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after tree description");
    }

    if (weight[1] != 1 && weight[1] != 2) {
        stream.quitf(_wa, "weight[1] must be 1 or 2, found %d", weight[1]);
    }
    if (countWeight1 != needWeight1 || countWeight2 != needWeight2) {
        stream.quitf(_wa,
                     "wrong weight counts: found weight1=%d weight2=%d, expected weight1=%d weight2=%d",
                     countWeight1,
                     countWeight2,
                     needWeight1,
                     needWeight2);
    }

    for (int i = 1; i <= nodeCount; ++i) {
        if (left[i] == right[i] && left[i] != 0) {
            stream.quitf(_wa, "node %d uses child %d twice", i, left[i]);
        }
        if (left[i] == i || right[i] == i) {
            stream.quitf(_wa, "node %d is its own child", i);
        }
        if (left[i] != 0 && ++indegree[left[i]] > 1) {
            stream.quitf(_wa, "node %d has more than one parent", left[i]);
        }
        if (right[i] != 0 && ++indegree[right[i]] > 1) {
            stream.quitf(_wa, "node %d has more than one parent", right[i]);
        }
    }

    if (indegree[1] != 0) {
        stream.quitf(_wa, "root node 1 has a parent");
    }
    for (int i = 2; i <= nodeCount; ++i) {
        if (indegree[i] != 1) {
            stream.quitf(_wa, "node %d is not reachable from root 1", i);
        }
    }

    vector<int> state(nodeCount + 1, 0);
    vector<int> subtreeWeight(nodeCount + 1, 0);
    vector<pair<int, bool>> stack;
    stack.push_back({1, false});

    int visited = 0;
    while (!stack.empty()) {
        int node = stack.back().first;
        bool exiting = stack.back().second;
        stack.pop_back();

        if (!exiting) {
            if (state[node] == 1) {
                stream.quitf(_wa, "cycle reaches node %d", node);
            }
            if (state[node] == 2) {
                continue;
            }
            state[node] = 1;
            stack.push_back({node, true});
            if (right[node] != 0) {
                stack.push_back({right[node], false});
            }
            if (left[node] != 0) {
                stack.push_back({left[node], false});
            }
            continue;
        }

        int leftWeight = left[node] == 0 ? 0 : subtreeWeight[left[node]];
        int rightWeight = right[node] == 0 ? 0 : subtreeWeight[right[node]];
        if (abs(leftWeight - rightWeight) > 1) {
            stream.quitf(_wa,
                         "node %d is not almost balanced: left weight=%d right weight=%d",
                         node,
                         leftWeight,
                         rightWeight);
        }
        subtreeWeight[node] = weight[node] + leftWeight + rightWeight;
        state[node] = 2;
        ++visited;
    }

    if (visited != nodeCount) {
        stream.quitf(_wa, "only %d of %d nodes are reachable from root 1", visited, nodeCount);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    needWeight1 = inf.readInt();
    needWeight2 = inf.readInt();
    nodeCount = needWeight1 + needWeight2;

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs report impossible");
    }
    if (jury.impossible) {
        quitf(_fail, "participant found a valid tree while jury reports impossible");
    }
    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury provides a valid tree");
    }

    quitf(_ok, "valid almost balanced tree");
}
