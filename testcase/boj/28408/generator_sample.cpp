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

static vector<int> shuffledLabels(int n) {
    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());
    return labels;
}

static int buildTree(vector<Node>& nodes, const vector<int>& labels, int l, int r, int mode) {
    if (l > r) return -1;

    int rootPos;
    if (mode == 0) {
        rootPos = l;
    } else if (mode == 1) {
        rootPos = r;
    } else if (mode == 2) {
        rootPos = (l + r) / 2;
    } else {
        rootPos = rnd.next(l, r);
    }

    int nodeIndex = nodes.size();
    nodes.push_back({labels[rootPos], -1, -1});

    vector<int> childSides;
    if (l <= rootPos - 1) childSides.push_back(0);
    if (rootPos + 1 <= r) childSides.push_back(1);
    if (childSides.size() == 2 && rnd.next(2)) swap(childSides[0], childSides[1]);

    for (int side : childSides) {
        int child = side == 0 ? buildTree(nodes, labels, l, rootPos - 1, mode)
                              : buildTree(nodes, labels, rootPos + 1, r, mode);
        if (nodes[nodeIndex].left == -1) {
            nodes[nodeIndex].left = child;
        } else {
            nodes[nodeIndex].right = child;
        }
    }

    return nodeIndex;
}

static void preorder(const vector<Node>& nodes, int u, vector<int>& out) {
    if (u == -1) return;
    out.push_back(nodes[u].value);
    preorder(nodes, nodes[u].left, out);
    preorder(nodes, nodes[u].right, out);
}

static void postorder(const vector<Node>& nodes, int u, vector<int>& out) {
    if (u == -1) return;
    postorder(nodes, nodes[u].left, out);
    postorder(nodes, nodes[u].right, out);
    out.push_back(nodes[u].value);
}

static void printCase(const vector<int>& pre, const vector<int>& post) {
    println((int)pre.size());
    println(pre);
    println(post);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 4) {
        n = rnd.next(2, 24);
    } else {
        n = rnd.next(2, 40);
    }

    vector<int> pre, post;
    vector<int> labels = shuffledLabels(n);

    if (mode <= 3) {
        vector<Node> nodes;
        int root = buildTree(nodes, labels, 0, n - 1, mode);
        preorder(nodes, root, pre);
        postorder(nodes, root, post);
    } else if (mode == 4) {
        pre = labels;
        post = labels;
        if (n > 1 && rnd.next(2)) {
            shuffle(post.begin(), post.end());
            if (post.back() == pre.front()) swap(post[0], post.back());
        }
    } else if (mode == 5) {
        pre = labels;
        post = labels;
        reverse(post.begin(), post.end());
        if (n > 1 && rnd.next(2)) swap(post[rnd.next(n)], post[rnd.next(n)]);
    } else {
        pre = labels;
        post = shuffledLabels(n);
    }

    printCase(pre, post);
    return 0;
}
