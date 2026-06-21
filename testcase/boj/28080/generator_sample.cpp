#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Node {
    int left = -1;
    int right = -1;
};

int buildShape(int lo, int hi, int mode, vector<int>& inorderToNode, vector<Node>& nodes,
               int forcedRoot = -1) {
    if (lo > hi) {
        return -1;
    }

    int mid;
    if (forcedRoot != -1) {
        mid = forcedRoot;
    } else if (mode == 0) {
        mid = lo;
    } else if (mode == 1) {
        mid = hi;
    } else if (mode == 2) {
        mid = (lo + hi) / 2;
    } else {
        mid = rnd.next(lo, hi);
    }

    int node = inorderToNode[mid];
    nodes[node].left = buildShape(lo, mid - 1, mode, inorderToNode, nodes);
    nodes[node].right = buildShape(mid + 1, hi, mode, inorderToNode, nodes);
    return node;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0 || mode == 1) {
        n = rnd.next(1, 12);
    } else {
        n = rnd.next(2, 16);
    }

    int m;
    if (rnd.next(0, 4) == 0) {
        m = n;
    } else {
        m = rnd.next(n, min(2000, n + rnd.next(0, 35)));
    }

    vector<int> inorderToNode(n);
    iota(inorderToNode.begin(), inorderToNode.end(), 1);
    shuffle(inorderToNode.begin(), inorderToNode.end());
    int rootPos = rnd.next(0, n - 1);
    swap(inorderToNode[rootPos], *find(inorderToNode.begin(), inorderToNode.end(), 1));

    vector<Node> nodes(n + 1);
    buildShape(0, n - 1, mode, inorderToNode, nodes, rootPos);

    vector<int> completion(m);
    iota(completion.begin(), completion.end(), 1);
    shuffle(completion.begin(), completion.end());
    completion.resize(n);
    sort(completion.begin(), completion.end());

    vector<int> value(n + 1);
    for (int i = 0; i < n; ++i) {
        value[inorderToNode[i]] = completion[i];
    }

    int erasedCount;
    int eraseMode = rnd.next(0, 5);
    if (eraseMode == 0) {
        erasedCount = 1;
    } else if (eraseMode == 1) {
        erasedCount = n;
    } else {
        erasedCount = rnd.next(1, n);
    }

    vector<int> eraseNodes(n);
    iota(eraseNodes.begin(), eraseNodes.end(), 1);
    shuffle(eraseNodes.begin(), eraseNodes.end());
    for (int i = 0; i < erasedCount; ++i) {
        value[eraseNodes[i]] = -1;
    }

    println(n, m);
    for (int i = 1; i <= n; ++i) {
        println(value[i], nodes[i].left, nodes[i].right);
    }

    return 0;
}
