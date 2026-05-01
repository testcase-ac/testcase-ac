#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

void buildBalanced(int l, int r, int parent, vector<pair<int,int>> &edges) {
    if (l > r) return;
    int mid = (l + r) / 2;
    if (parent != -1) edges.emplace_back(parent, mid);
    buildBalanced(l, mid - 1, mid, edges);
    buildBalanced(mid + 1, r, mid, edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 12);
    vector<pair<int,int>> edges;
    int type = rnd.next(0, 4);
    if (type == 0) {
        // Chain
        for (int i = 1; i < N; i++)
            edges.emplace_back(i, i+1);
    } else if (type == 1) {
        // Star
        int c = rnd.next(1, N);
        for (int i = 1; i <= N; i++)
            if (i != c) edges.emplace_back(c, i);
    } else if (type == 2) {
        // Balanced tree
        buildBalanced(1, N, -1, edges);
    } else if (type == 3) {
        // Random attachment
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    } else {
        // Comb: spine + leaves
        int spine = N/2;
        if (spine < 1) spine = 1;
        for (int i = 1; i < spine; i++)
            edges.emplace_back(i, i+1);
        for (int i = spine+1; i <= N; i++) {
            int attach = rnd.next(1, spine);
            edges.emplace_back(attach, i);
        }
    }
    // Shuffle labels
    vector<int> perm(N+1);
    for (int i = 1; i <= N; i++) perm[i] = i;
    shuffle(perm.begin()+1, perm.end());
    for (auto &e : edges) {
        e.first = perm[e.first];
        e.second = perm[e.second];
    }
    // Shuffle edges
    shuffle(edges.begin(), edges.end());
    // Output
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
