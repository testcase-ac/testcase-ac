#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checkability
    int N = rnd.next(4, 10);
    vector<pair<int,int>> edges;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        // Pure chain: 1-2-...-N
        for (int i = 1; i < N; i++)
            edges.emplace_back(i, i+1);
    } else if (mode == 1) {
        // Pure star: 1 connected to everyone else
        for (int i = 2; i <= N; i++)
            edges.emplace_back(1, i);
    } else if (mode == 2) {
        // Random tree via Prufer sequence
        vector<int> prufer(N - 2);
        for (int &x : prufer)
            x = rnd.next(1, N);
        vector<int> deg(N + 1, 1);
        for (int x : prufer)
            deg[x]++;
        vector<int> leaves;
        for (int i = 1; i <= N; i++)
            if (deg[i] == 1)
                leaves.push_back(i);
        for (int x : prufer) {
            int idx = rnd.next(0, int(leaves.size()) - 1);
            int u = leaves[idx];
            leaves[idx] = leaves.back();
            leaves.pop_back();
            edges.emplace_back(u, x);
            deg[u]--; deg[x]--;
            if (deg[x] == 1)
                leaves.push_back(x);
        }
        // connect the last two leaves
        edges.emplace_back(leaves[0], leaves[1]);
    } else if (mode == 3) {
        // Chain among 1..N-1, then attach N to a middle node
        for (int i = 1; i < N - 1; i++)
            edges.emplace_back(i, i+1);
        int attach_to = rnd.next(1, N - 1);
        edges.emplace_back(attach_to, N);
    } else {
        // Random attachment tree
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    }

    // Shuffle edge order for diversity
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
