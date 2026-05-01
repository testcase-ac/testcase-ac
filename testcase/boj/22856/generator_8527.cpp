#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5); // 6 different structure scenarios [0..5]

    int N = 0;
    vector<int> L, R; // children: L[i] = left child of i, R[i] = right child of i

    if (scenario == 0) {
        // Single node tree
        N = 1;
        L.assign(N + 1, -1);
        R.assign(N + 1, -1);
    } else if (scenario == 1) {
        // Left chain: 1 -> 2 -> 3 -> ... as left children
        N = rnd.next(2, 15);
        L.assign(N + 1, -1);
        R.assign(N + 1, -1);
        for (int i = 1; i <= N; ++i) {
            if (i < N) L[i] = i + 1;
            else L[i] = -1;
            R[i] = -1;
        }
    } else if (scenario == 2) {
        // Right chain: 1 -> 2 -> 3 -> ... as right children
        N = rnd.next(2, 15);
        L.assign(N + 1, -1);
        R.assign(N + 1, -1);
        for (int i = 1; i <= N; ++i) {
            if (i < N) R[i] = i + 1;
            else R[i] = -1;
            L[i] = -1;
        }
    } else if (scenario == 3) {
        // Right spine with random left chains hanging off the spine
        // Total N between 2 and 15
        N = rnd.next(2, 15);
        int k = rnd.next(1, N); // length of right spine (nodes 1..k)
        int rem = N - k;        // remaining nodes to distribute as left chains

        vector<int> len(k, 0);  // len[i] = length of left chain starting at node (i+1)
        for (int t = 0; t < rem; ++t) {
            int idx = rnd.next(0, k - 1);
            len[idx]++;
        }

        L.assign(N + 1, -1);
        R.assign(N + 1, -1);

        // Build right spine 1 -> 2 -> ... -> k
        for (int i = 1; i <= k; ++i) {
            if (i < k) R[i] = i + 1;
            else R[i] = -1;
        }

        int id = k;
        // Attach left chains
        for (int i = 0; i < k; ++i) {
            int node = i + 1;
            int prev = node;
            for (int j = 0; j < len[i]; ++j) {
                ++id;
                L[prev] = id;
                prev = id;
            }
        }
    } else if (scenario == 4) {
        // Perfect (full) binary tree of height h (1..4), N = 2^h - 1
        int h = rnd.next(1, 4);
        N = (1 << h) - 1;
        L.assign(N + 1, -1);
        R.assign(N + 1, -1);

        int lastInternal = (N - 1) / 2;
        for (int i = 1; i <= lastInternal; ++i) {
            int lc = 2 * i;
            int rc = 2 * i + 1;
            if (lc <= N) L[i] = lc;
            if (rc <= N) R[i] = rc;
        }
        for (int i = lastInternal + 1; i <= N; ++i) {
            L[i] = -1;
            R[i] = -1;
        }
    } else if (scenario == 5) {
        // Random binary tree with arbitrary shape (parent index < child index)
        N = rnd.next(2, 20);
        L.assign(N + 1, -1);
        R.assign(N + 1, -1);

        for (int v = 2; v <= N; ++v) {
            while (true) {
                int p = rnd.next(1, v - 1);
                int side = rnd.next(0, 1); // try random side first
                if (side == 0) {
                    if (L[p] == -1) {
                        L[p] = v;
                        break;
                    } else if (R[p] == -1) {
                        R[p] = v;
                        break;
                    }
                } else {
                    if (R[p] == -1) {
                        R[p] = v;
                        break;
                    } else if (L[p] == -1) {
                        L[p] = v;
                        break;
                    }
                }
            }
        }
    }

    // Decide whether to shuffle the order of node descriptions
    bool shuffleLines = rnd.next(0, 1); // 0 or 1
    vector<int> order(N);
    for (int i = 0; i < N; ++i) order[i] = i + 1;
    if (shuffleLines) shuffle(order.begin(), order.end());

    // Output
    println(N);
    for (int idx = 0; idx < N; ++idx) {
        int a = order[idx];
        println(a, L[a], R[a]);
    }

    return 0;
}
