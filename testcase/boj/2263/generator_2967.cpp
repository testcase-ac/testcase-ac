#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Node {
    int label;
    Node* left;
    Node* right;
    Node(): label(0), left(nullptr), right(nullptr) {}
};

Node* build(int size, int skew) {
    if (size == 0) return nullptr;
    int leftSize = rnd.wnext(size, skew);
    int rightSize = size - 1 - leftSize;
    Node* root = new Node();
    root->left = build(leftSize, skew);
    root->right = build(rightSize, skew);
    return root;
}

void collectNodes(Node* u, vector<Node*>& v) {
    if (!u) return;
    v.push_back(u);
    collectNodes(u->left, v);
    collectNodes(u->right, v);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of nodes
    int n = rnd.next(1, 10);
    // Skew parameter for tree shape diversity
    vector<int> skews = {-2, -1, 0, 1, 2};
    int skew = rnd.any(skews);

    // Build a random binary tree structure
    Node* root = build(n, skew);

    // Collect all nodes to assign labels
    vector<Node*> nodes;
    collectNodes(root, nodes);

    // Assign random labels 1..n
    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());
    for (int i = 0; i < n; i++) {
        nodes[i]->label = labels[i];
    }

    // Compute inorder and postorder traversals
    vector<int> inorder, postorder;
    auto dfsIn = [&](auto self, Node* u) -> void {
        if (!u) return;
        self(self, u->left);
        inorder.push_back(u->label);
        self(self, u->right);
    };
    auto dfsPost = [&](auto self, Node* u) -> void {
        if (!u) return;
        self(self, u->left);
        self(self, u->right);
        postorder.push_back(u->label);
    };
    dfsIn(dfsIn, root);
    dfsPost(dfsPost, root);

    // Output in required format
    println(n);
    println(inorder);
    println(postorder);

    return 0;
}
