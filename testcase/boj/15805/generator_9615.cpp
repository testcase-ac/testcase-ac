#include "testlib.h"
using namespace std;

vector<vector<int>> g;
vector<int> tour;

void dfs(int u) {
    for (int v : g[u]) {
        tour.push_back(v);
        dfs(v);
        tour.push_back(u);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxK = 70;

    int type = rnd.next(0, 4); // 5 types: tiny, path, star, balanced-ish, random
    int K;

    if (type == 0) { // very small trees
        K = rnd.next(1, 6);
    } else if (type == 1) { // path
        K = rnd.next(2, maxK);
    } else if (type == 2) { // star
        K = rnd.next(2, maxK);
    } else if (type == 3) { // balanced-ish (heap-shaped)
        K = rnd.next(2, maxK);
    } else { // random tree
        K = rnd.next(1, maxK);
    }

    g.assign(K, vector<int>());

    if (K >= 2) {
        if (type == 1) {
            // path: 0-1-2-...-(K-1)
            for (int i = 1; i < K; i++) {
                int p = i - 1;
                g[p].push_back(i);
            }
        } else if (type == 2) {
            // star centered at 0
            for (int i = 1; i < K; i++) {
                int p = 0;
                g[p].push_back(i);
            }
        } else if (type == 3) {
            // heap-like binary tree: parent(i) = (i-1)/2
            for (int i = 1; i < K; i++) {
                int p = (i - 1) / 2;
                g[p].push_back(i);
            }
        } else {
            // random tree: each node attaches to some previous node
            for (int i = 1; i < K; i++) {
                // bias parameter t in [-3,3] to vary shape
                int t = rnd.next(-3, 3);
                int p = rnd.wnext(i, t);
                g[p].push_back(i);
            }
        }
    }

    // Shuffle children order to vary DFS traversal
    for (int u = 0; u < K; u++) {
        shuffle(g[u].begin(), g[u].end());
    }

    // Build Euler tour (minimal DFS walk) starting and ending at root 0
    tour.clear();
    tour.push_back(0);
    if (K > 0)
        dfs(0);

    // Optional permutation of labels, keeping root as 0
    vector<int> perm(K);
    for (int i = 0; i < K; i++) perm[i] = i;

    bool doPermute = (K > 1) ? rnd.next(0, 1) : false;
    if (doPermute) {
        vector<int> labels;
        for (int i = 1; i < K; i++) labels.push_back(i);
        shuffle(labels.begin(), labels.end());
        int idx = 0;
        for (int i = 1; i < K; i++) {
            perm[i] = labels[idx++];
        }
    }

    vector<int> A(tour.size());
    for (int i = 0; i < (int)tour.size(); i++) {
        A[i] = perm[tour[i]];
    }

    int N = (int)A.size();
    println(N);
    println(A);

    return 0;
}
