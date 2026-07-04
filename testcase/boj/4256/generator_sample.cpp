#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Node {
    int value;
    int left = -1;
    int right = -1;
};

void addPreorder(const vector<Node>& tree, int node, vector<int>& order) {
    if (node == -1) return;
    order.push_back(tree[node].value);
    addPreorder(tree, tree[node].left, order);
    addPreorder(tree, tree[node].right, order);
}

void addInorder(const vector<Node>& tree, int node, vector<int>& order) {
    if (node == -1) return;
    addInorder(tree, tree[node].left, order);
    order.push_back(tree[node].value);
    addInorder(tree, tree[node].right, order);
}

int buildBalanced(vector<Node>& tree, const vector<int>& values, int lo, int hi) {
    if (lo > hi) return -1;
    int mid = (lo + hi) / 2;
    int node = (int)tree.size();
    tree.push_back({values[mid], -1, -1});
    tree[node].left = buildBalanced(tree, values, lo, mid - 1);
    tree[node].right = buildBalanced(tree, values, mid + 1, hi);
    return node;
}

int buildChain(vector<Node>& tree, const vector<int>& values, bool toLeft) {
    if (values.empty()) return -1;
    int root = (int)tree.size();
    tree.push_back({values[0], -1, -1});
    int current = root;
    for (int i = 1; i < (int)values.size(); ++i) {
        int child = (int)tree.size();
        tree.push_back({values[i], -1, -1});
        if (toLeft) {
            tree[current].left = child;
        } else {
            tree[current].right = child;
        }
        current = child;
    }
    return root;
}

int buildZigzag(vector<Node>& tree, const vector<int>& values) {
    if (values.empty()) return -1;
    int root = (int)tree.size();
    tree.push_back({values[0], -1, -1});
    int current = root;
    bool leftNext = rnd.next(2) == 0;
    for (int i = 1; i < (int)values.size(); ++i) {
        int child = (int)tree.size();
        tree.push_back({values[i], -1, -1});
        if (leftNext) {
            tree[current].left = child;
        } else {
            tree[current].right = child;
        }
        current = child;
        leftNext = !leftNext;
    }
    return root;
}

int buildRandom(vector<Node>& tree, const vector<int>& values, int lo, int hi) {
    if (lo > hi) return -1;
    int rootPos = rnd.next(lo, hi);
    int node = (int)tree.size();
    tree.push_back({values[rootPos], -1, -1});
    tree[node].left = buildRandom(tree, values, lo, rootPos - 1);
    tree[node].right = buildRandom(tree, values, rootPos + 1, hi);
    return node;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 6);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(5);
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 1;
        } else if (mode <= 2) {
            n = rnd.next(2, 12);
        } else {
            n = rnd.next(8, 30);
        }

        vector<int> values(n);
        iota(values.begin(), values.end(), 1);
        shuffle(values.begin(), values.end());

        vector<Node> tree;
        int root;
        if (mode == 0) {
            root = buildChain(tree, values, true);
        } else if (mode == 1) {
            root = buildChain(tree, values, false);
        } else if (mode == 2) {
            root = buildZigzag(tree, values);
        } else if (mode == 3) {
            sort(values.begin(), values.end());
            root = buildBalanced(tree, values, 0, n - 1);
        } else {
            root = buildRandom(tree, values, 0, n - 1);
        }

        vector<int> preorder;
        vector<int> inorder;
        addPreorder(tree, root, preorder);
        addInorder(tree, root, inorder);

        println(n);
        println(preorder);
        println(inorder);
    }

    return 0;
}
