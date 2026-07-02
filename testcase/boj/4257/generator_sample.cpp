#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Node {
    vector<int> children;
};

void addChain(vector<Node>& tree, int parent, int& nextNode, int remaining) {
    int current = parent;
    for (int i = 0; i < remaining; ++i) {
        tree[current].children.push_back(nextNode);
        tree.push_back(Node{});
        current = nextNode;
        ++nextNode;
    }
}

vector<Node> makeTree(int n, int m, int mode) {
    vector<Node> tree(1);
    int nextNode = 1;

    if (n == 1) {
        return tree;
    }

    if (mode == 0 || m == 1) {
        addChain(tree, 0, nextNode, n - 1);
    } else if (mode == 1) {
        int childCount = min(m, n - 1);
        for (int i = 0; i < childCount; ++i) {
            tree[0].children.push_back(nextNode);
            tree.push_back(Node{});
            ++nextNode;
        }
        while (nextNode < n) {
            int parent = rnd.next(1, nextNode - 1);
            if (static_cast<int>(tree[parent].children.size()) < m) {
                tree[parent].children.push_back(nextNode);
                tree.push_back(Node{});
                ++nextNode;
            }
        }
    } else {
        while (nextNode < n) {
            vector<int> candidates;
            for (int node = 0; node < nextNode; ++node) {
                if (static_cast<int>(tree[node].children.size()) < m) {
                    candidates.push_back(node);
                }
            }

            int parent = rnd.any(candidates);
            tree[parent].children.push_back(nextNode);
            tree.push_back(Node{});
            ++nextNode;
        }
    }

    return tree;
}

void preorder(int node, const vector<Node>& tree, const string& labels,
              string& result) {
    result.push_back(labels[node]);
    for (int child : tree[node].children) {
        preorder(child, tree, labels, result);
    }
}

void postorder(int node, const vector<Node>& tree, const string& labels,
               string& result) {
    for (int child : tree[node].children) {
        postorder(child, tree, labels, result);
    }
    result.push_back(labels[node]);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCaseCount = rnd.next(5, 12);
    for (int tc = 0; tc < testCaseCount; ++tc) {
        int m = rnd.next(1, 20);
        int n = rnd.next(1, 18);
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            m = 1;
            n = rnd.next(2, 12);
        } else if (tc == 2) {
            m = rnd.next(10, 20);
            n = rnd.next(10, 18);
        }

        string labels = "abcdefghijklmnopqrstuvwxyz";
        labels.resize(n);
        shuffle(labels.begin(), labels.end());

        vector<Node> tree = makeTree(n, m, rnd.next(0, 2));
        string pre, post;
        preorder(0, tree, labels, pre);
        postorder(0, tree, labels, post);

        println(m, pre, post);
    }
    println(0);

    return 0;
}
