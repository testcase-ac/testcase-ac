#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small size
    int N = rnd.next(1, 10);
    vector<pair<int,int>> edges;
    // Decide shape: chain (~20%), full-like (~20%), random (~60%)
    int s = rnd.next(0, 9);
    if (N >= 2 && s < 2) {
        // Chain 1-2-3-...-N
        for (int i = 2; i <= N; i++)
            edges.emplace_back(i-1, i);
    } else if (N >= 2 && s < 4) {
        // Full-approx binary tree by levels
        int nextVal = 2;
        vector<int> q;
        q.push_back(1);
        for (size_t i = 0; i < q.size() && nextVal <= N; i++) {
            int u = q[i];
            // left child
            if (nextVal <= N) {
                edges.emplace_back(u, nextVal);
                q.push_back(nextVal);
                nextVal++;
            }
            // right child
            if (nextVal <= N) {
                edges.emplace_back(u, nextVal);
                q.push_back(nextVal);
                nextVal++;
            }
        }
    } else {
        // Random binary tree: each node has <=2 children
        if (N >= 2) {
            vector<int> avail;
            avail.push_back(1);
            vector<int> childCount(N+1, 0);
            for (int v = 2; v <= N; v++) {
                // pick random parent with <2 children
                int idx = rnd.next(0, int(avail.size()) - 1);
                int p = avail[idx];
                // attach v to p
                edges.emplace_back(p, v);
                childCount[p]++;
                if (childCount[p] == 2) {
                    // remove p from avail
                    avail.erase(avail.begin() + idx);
                }
                // v has 0 children initially
                avail.push_back(v);
            }
        }
    }
    // Shuffle edges order
    shuffle(edges.begin(), edges.end());
    // Randomly flip orientation
    for (auto &e : edges) {
        if (rnd.next(0, 1) == 0)
            swap(e.first, e.second);
    }
    // Output
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
