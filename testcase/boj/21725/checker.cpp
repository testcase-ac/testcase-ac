#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

const long long MAX_TRANSFER = 20000000000000LL;

int n, m;
vector<int> parentDsu, rootNode, treeLeft, treeRight;
vector<long long> paid, groupShare, balanceValue;

int findRoot(int x) {
    if (parentDsu[x] == x) return x;
    return parentDsu[x] = findRoot(parentDsu[x]);
}

void buildBalances() {
    n = inf.readInt();
    m = inf.readInt();

    parentDsu.assign(n + 1, 0);
    rootNode.assign(n + 1, 0);
    paid.assign(n + 1, 0);
    treeLeft.assign(2 * n + 1, 0);
    treeRight.assign(2 * n + 1, 0);
    groupShare.assign(2 * n + 1, 0);
    balanceValue.assign(n + 1, 0);

    vector<int> componentSize(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        parentDsu[i] = i;
        rootNode[i] = i;
    }

    int nodeCount = n;
    for (int i = 0; i < m; ++i) {
        int type = inf.readInt();
        int x = inf.readInt();
        int yOrCost = inf.readInt();

        if (type == 1) {
            int a = findRoot(x);
            int b = findRoot(yOrCost);
            int newNode = ++nodeCount;
            treeLeft[newNode] = rootNode[a];
            treeRight[newNode] = rootNode[b];

            parentDsu[b] = a;
            componentSize[a] += componentSize[b];
            rootNode[a] = newNode;
        } else {
            int root = findRoot(x);
            long long cost = yOrCost;
            long long share = cost / componentSize[root];
            paid[x] += cost;
            groupShare[rootNode[root]] += share;
        }
    }

    vector<pair<int, long long> > stack;
    stack.push_back(make_pair(rootNode[findRoot(1)], 0LL));
    while (!stack.empty()) {
        int node = stack.back().first;
        long long inheritedShare = stack.back().second;
        stack.pop_back();

        long long totalShare = inheritedShare + groupShare[node];
        if (node <= n) {
            balanceValue[node] = paid[node] - totalShare;
        } else {
            stack.push_back(make_pair(treeLeft[node], totalShare));
            stack.push_back(make_pair(treeRight[node], totalShare));
        }
    }
}

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "transfer count");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<long long> residual = balanceValue;
    for (int i = 0; i < first; ++i) {
        int from = stream.readInt(1, n, format("from[%d]", i + 1).c_str());
        int to = stream.readInt(1, n, format("to[%d]", i + 1).c_str());
        long long amount = stream.readLong(1LL, MAX_TRANSFER, format("amount[%d]", i + 1).c_str());
        if (from == to) {
            stream.quitf(_wa, "transfer %d has same sender and receiver %d", i + 1, from);
        }
        residual[from] += amount;
        residual[to] -= amount;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after transfer list");
    }

    for (int i = 1; i <= n; ++i) {
        if (residual[i] != 0) {
            stream.quitf(_wa, "friend %d is not settled: residual=%lld", i, residual[i]);
        }
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    buildBalances();
    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid settlement while jury reports impossible");
    }
    if (participant.impossible) {
        quitf(_wa, "jury provides a valid settlement but participant reports impossible");
    }
    quitf(_ok, "valid settlement");
}
