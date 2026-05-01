#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 9);

    int n;
    if (scenario == 0) {
        n = 1;
    } else if (scenario <= 2) {
        n = rnd.next(2, 5);
    } else if (scenario <= 5) {
        n = rnd.next(4, 10);
    } else {
        n = rnd.next(8, 20);
    }

    int total = n * n;

    vector<int> parent(n + 1, 0);

    if (n == 1) {
        parent[1] = 0;
    } else {
        // Choose tree shape
        int shape = rnd.next(0, 3); // 0=chain,1=star,2=binary-ish,3=random tree

        // Random permutation of node labels
        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i + 1;
        shuffle(order.begin(), order.end());

        int root = order[0];
        parent[root] = 0;

        if (shape == 0) {
            // Chain: order[0] -> order[1] -> ... -> order[n-1]
            for (int i = 1; i < n; i++) {
                int v = order[i];
                int par = order[i - 1];
                parent[v] = par;
            }
        } else if (shape == 1) {
            // Star: root with all other nodes as children
            for (int i = 1; i < n; i++) {
                int v = order[i];
                parent[v] = root;
            }
        } else if (shape == 2) {
            // Binary-heap-like structure on permuted labels
            for (int i = 1; i < n; i++) {
                int v = order[i];
                int par = order[(i - 1) / 2];
                parent[v] = par;
            }
        } else {
            // Random tree: each new node connects to a previous one
            for (int i = 1; i < n; i++) {
                int v = order[i];
                int par = order[rnd.next(0, i - 1)];
                parent[v] = par;
            }
        }
    }

    int q;
    if (scenario == 0) {
        q = rnd.next(1, 5);
    } else if (scenario == 1) {
        q = rnd.next(1, min(total, 10));
    } else if (scenario == 2) {
        q = total; // query all positions
    } else if (scenario == 3) {
        q = rnd.next(n, min(total, 20));
    } else if (scenario == 4) {
        q = rnd.next(1, min(total, 30));
    } else {
        int lo = min(total, 10);
        int hi = min(total, 80);
        if (lo > hi) lo = hi; // when total < 10
        q = rnd.next(lo, hi);
    }

    vector<int> ks(q);
    int pattern = rnd.next(0, 3); // 0..3

    if (pattern == 0) {
        // Fully random queries
        for (int i = 0; i < q; i++) {
            ks[i] = rnd.next(1, total);
        }
    } else if (pattern == 1) {
        // Emphasize edges and near-edges, shuffled
        vector<int> base;
        base.push_back(1);
        if (total >= 2) base.push_back(2);
        if (total >= 3) base.push_back(3);
        if (total > 3) base.push_back(total - 2);
        if (total > 2) base.push_back(total - 1);
        if (total > 1) base.push_back(total);

        for (int i = 0; i < q; i++) {
            ks[i] = base[i % (int)base.size()];
        }
        shuffle(ks.begin(), ks.end());
    } else if (pattern == 2) {
        // Arithmetic progression modulo total
        int start = rnd.next(1, total);
        int step = rnd.next(1, total);
        for (int i = 0; i < q; i++) {
            long long val = (long long)(start - 1) + (long long)step * i;
            ks[i] = (int)(val % total) + 1;
        }
    } else {
        // Concentrate around extremes and middle
        int mid = (total + 1) / 2;
        for (int i = 0; i < q; i++) {
            int t = rnd.next(0, 4);
            if (t == 0) ks[i] = 1;
            else if (t == 1) ks[i] = total;
            else if (t == 2) ks[i] = mid;
            else if (t == 3) ks[i] = max(1, mid - 1);
            else ks[i] = min(total, mid + 1);
        }
    }

    // Output
    println(n, q);
    vector<int> parOut(n);
    for (int i = 1; i <= n; i++) parOut[i - 1] = parent[i];
    println(parOut);
    for (int i = 0; i < q; i++) {
        println(ks[i]);
    }

    return 0;
}
