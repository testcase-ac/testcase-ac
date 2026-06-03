#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Node {
    vector<int> children;
};

void dfsTraversal(const vector<Node>& tree, int u, string& traversal) {
    traversal.push_back('0');
    for (int v : tree[u].children) {
        dfsTraversal(tree, v, traversal);
    }
    traversal.push_back('1');
}

void expandLeaf(vector<Node>& tree, vector<int>& leaves, int leafIndex, int childCount) {
    int parent = leaves[leafIndex];
    leaves.erase(leaves.begin() + leafIndex);

    for (int i = 0; i < childCount; ++i) {
        int child = (int)tree.size();
        tree[parent].children.push_back(child);
        tree.push_back(Node{});
        leaves.push_back(child);
    }

    shuffle(tree[parent].children.begin(), tree[parent].children.end());
}

vector<Node> makeTree(int n, int mode) {
    vector<Node> tree(1);
    vector<int> leaves{0};

    if (n == 1) {
        return tree;
    }

    while ((int)tree.size() < n) {
        int remaining = n - (int)tree.size();
        int leafIndex = rnd.next((int)leaves.size());

        if (mode == 1) {
            int deepest = leaves[0];
            int bestDepth = -1;
            for (int i = 0; i < (int)leaves.size(); ++i) {
                int depth = 0;
                for (int u = leaves[i]; u > 0;) {
                    bool found = false;
                    for (int p = 0; p < (int)tree.size() && !found; ++p) {
                        for (int v : tree[p].children) {
                            if (v == u) {
                                u = p;
                                found = true;
                                break;
                            }
                        }
                    }
                    ++depth;
                    if (!found) {
                        break;
                    }
                }
                if (depth > bestDepth) {
                    bestDepth = depth;
                    deepest = leaves[i];
                    leafIndex = i;
                }
            }
            (void)deepest;
        } else if (mode == 2) {
            leafIndex = 0;
        }

        int limit = min(remaining, mode == 0 ? 8 : 4);
        vector<int> choices;
        for (int k = 2; k <= limit; ++k) {
            if (remaining - k != 1) {
                choices.push_back(k);
            }
        }
        int childCount = choices[rnd.next((int)choices.size())];
        expandLeaf(tree, leaves, leafIndex, childCount);
    }

    return tree;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 28);
    } else if (mode == 1) {
        n = rnd.next(3, 31);
    } else if (mode == 2) {
        n = rnd.next(3, 18);
    } else {
        n = rnd.next(1, 45);
    }
    if (n == 2) {
        n = 3;
    }

    vector<Node> tree = makeTree(n, mode);
    string traversal;
    dfsTraversal(tree, 0, traversal);

    int x = rnd.next(1, 2 * n);
    int y;
    if (rnd.next(0, 4) == 0) {
        y = x;
    } else {
        y = rnd.next(1, 2 * n);
    }

    println(n);
    println(traversal);
    println(x, y);
    return 0;
}
