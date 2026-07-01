#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Traversals {
    string preorder;
    string inorder;
};

struct Node {
    int label = -1;
    int left = -1;
    int right = -1;
};

void visitPreorder(const vector<Node>& tree, int node, const string& labels, string& out) {
    if (node == -1) return;
    out += labels[tree[node].label];
    visitPreorder(tree, tree[node].left, labels, out);
    visitPreorder(tree, tree[node].right, labels, out);
}

void visitInorder(const vector<Node>& tree, int node, const string& labels, string& out) {
    if (node == -1) return;
    visitInorder(tree, tree[node].left, labels, out);
    out += labels[tree[node].label];
    visitInorder(tree, tree[node].right, labels, out);
}

int buildBalanced(vector<Node>& tree, const vector<int>& order, int lo, int hi) {
    if (lo > hi) return -1;

    int mid = (lo + hi) / 2;
    int node = static_cast<int>(tree.size());
    tree.push_back({order[mid], -1, -1});
    tree[node].left = buildBalanced(tree, order, lo, mid - 1);
    tree[node].right = buildBalanced(tree, order, mid + 1, hi);
    return node;
}

int buildRandomTree(vector<Node>& tree, vector<int>& remaining) {
    if (remaining.empty()) return -1;

    int picked = rnd.next(static_cast<int>(remaining.size()));
    int label = remaining[picked];
    remaining.erase(remaining.begin() + picked);

    int node = static_cast<int>(tree.size());
    tree.push_back({label, -1, -1});

    vector<int> leftLabels;
    vector<int> rightLabels;
    for (int value : remaining) {
        if (rnd.next(2) == 0) {
            leftLabels.push_back(value);
        } else {
            rightLabels.push_back(value);
        }
    }

    tree[node].left = buildRandomTree(tree, leftLabels);
    tree[node].right = buildRandomTree(tree, rightLabels);
    return node;
}

Traversals makeTreeCase(int n, int mode, const string& labels) {
    vector<Node> tree;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);

    int root = -1;
    if (mode == 0) {
        root = buildBalanced(tree, order, 0, n - 1);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            tree.push_back({order[i], -1, -1});
            if (i > 0) tree[i - 1].left = i;
        }
        root = 0;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            tree.push_back({order[i], -1, -1});
            if (i > 0) tree[i - 1].right = i;
        }
        root = 0;
    } else {
        shuffle(order.begin(), order.end());
        root = buildRandomTree(tree, order);
    }

    Traversals result;
    visitPreorder(tree, root, labels, result.preorder);
    visitInorder(tree, root, labels, result.inorder);
    return result;
}

Traversals makePermutationCase(int n, const string& labels) {
    string preorder = labels.substr(0, n);
    string inorder = preorder;
    shuffle(preorder.begin(), preorder.end());
    shuffle(inorder.begin(), inorder.end());
    return {preorder, inorder};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string labels = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int cases = rnd.next(3, 9);

    for (int tc = 0; tc < cases; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = rnd.next(20, 26);
        } else {
            n = rnd.next(2, 12);
        }

        string caseLabels = labels;
        shuffle(caseLabels.begin(), caseLabels.end());

        Traversals traversals;
        if (tc >= 2 && rnd.next(4) == 0) {
            traversals = makePermutationCase(n, caseLabels);
        } else {
            traversals = makeTreeCase(n, rnd.next(4), caseLabels);
        }

        println(traversals.preorder, traversals.inorder);
    }

    println("#");
    return 0;
}
