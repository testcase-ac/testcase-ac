#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of nodes
    int N = rnd.next(1, 10);

    // Node labels 1..N
    vector<int> ids(N);
    for (int i = 0; i < N; i++) ids[i] = i + 1;
    // Choose root
    int root = rnd.any(ids);

    // Child pointers, initialize to -1
    vector<pair<int,int>> child(N+1, {-1, -1});

    // Available parents: those with at least one free slot
    vector<int> avail;
    avail.push_back(root);

    // Prepare other nodes to insert
    vector<int> others;
    for (int x : ids) if (x != root) others.push_back(x);
    shuffle(others.begin(), others.end());

    // Hyper-parameter: bias for picking parent: t controls wnext
    int t = rnd.next(-2, 2);

    // Build random binary tree
    for (int u : others) {
        // pick a parent index from avail with bias
        int idx = rnd.wnext((int)avail.size(), t);
        int p = avail[idx];
        // choose which side
        bool leftFree = (child[p].first == -1);
        bool rightFree = (child[p].second == -1);
        if (leftFree && rightFree) {
            if (rnd.next(0,1) == 0) child[p].first = u;
            else child[p].second = u;
        } else if (leftFree) {
            child[p].first = u;
        } else {
            child[p].second = u;
        }
        // if p now full, remove from avail
        if (child[p].first != -1 && child[p].second != -1) {
            avail.erase(avail.begin() + idx);
        }
        // new node u has two free slots
        avail.push_back(u);
    }

    // Prepare lines for output
    vector<tuple<int,int,int>> lines;
    for (int i = 1; i <= N; i++) {
        lines.emplace_back(i, child[i].first, child[i].second);
    }
    // Shuffle output order a bit
    shuffle(lines.begin(), lines.end());

    // Print the test case
    println(N);
    for (auto &tp : lines) {
        int v, l, r;
        tie(v, l, r) = tp;
        // if no child, print -1
        printf("%d %d %d\n", v, l, r);
    }
    return 0;
}
