#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Node {
    char label;
    int left = -1;
    int right = -1;
};

static int buildTree(vector<Node>& nodes, const vector<char>& labels, int lo, int hi,
                     int mode) {
    if (lo > hi) return -1;

    int rootPos;
    if (mode == 0) {
        rootPos = lo;
    } else if (mode == 1) {
        rootPos = hi;
    } else if (mode == 2) {
        rootPos = (lo + hi) / 2;
    } else if (mode == 3) {
        rootPos = rnd.next(lo, hi);
    } else {
        rootPos = rnd.wnext(hi - lo + 1, rnd.next(-2, 2)) + lo;
    }

    int root = int(nodes.size());
    nodes.push_back({labels[rootPos], -1, -1});
    nodes[root].left = buildTree(nodes, labels, lo, rootPos - 1, mode);
    nodes[root].right = buildTree(nodes, labels, rootPos + 1, hi, mode);
    return root;
}

static void preorder(const vector<Node>& nodes, int u, string& out) {
    if (u == -1) return;
    out += nodes[u].label;
    preorder(nodes, nodes[u].left, out);
    preorder(nodes, nodes[u].right, out);
}

static void inorder(const vector<Node>& nodes, int u, string& out) {
    if (u == -1) return;
    inorder(nodes, nodes[u].left, out);
    out += nodes[u].label;
    inorder(nodes, nodes[u].right, out);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 8);
    for (int tc = 0; tc < caseCount; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 26;
        } else {
            n = rnd.next(1, 14);
        }

        vector<char> labels;
        for (char ch = 'A'; ch <= 'Z'; ++ch) labels.push_back(ch);
        shuffle(labels.begin(), labels.end());
        labels.resize(n);
        shuffle(labels.begin(), labels.end());

        int mode = rnd.next(0, 4);
        vector<Node> nodes;
        int root = buildTree(nodes, labels, 0, n - 1, mode);

        string preord, inord;
        preorder(nodes, root, preord);
        inorder(nodes, root, inord);
        println(preord, inord);
    }

    return 0;
}
