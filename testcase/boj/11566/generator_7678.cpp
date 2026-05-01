#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n and m
    int n = rnd.next(2, 8);
    int m = rnd.next(n, 30);

    // Generate a distinct base sequence A of length n
    vector<int> pool(20);
    for (int i = 0; i < 20; ++i) pool[i] = i + 1;
    shuffle(pool.begin(), pool.end());
    vector<int> A(pool.begin(), pool.begin() + n);

    // Compute maximum possible depth
    int max_k = (m - 1) / (n - 1);
    if (max_k < 0) max_k = 0;

    // Choose up to 3 candidate depths
    int e = rnd.next(0, min(3, max_k + 1));
    vector<int> depths;
    for (int i = 0; i < e; ++i) {
        if (max_k == 0) break;
        int d = rnd.next(0, max_k);
        if (find(depths.begin(), depths.end(), d) == depths.end())
            depths.push_back(d);
    }

    // Prepare B with random noise
    vector<int> B(m);
    for (int i = 0; i < m; ++i)
        B[i] = rnd.next(1, 20);

    // Attempt to embed A for each chosen depth without overlap
    vector<bool> used(m, false);
    shuffle(depths.begin(), depths.end());
    for (int d : depths) {
        int L = (n - 1) * (d + 1) + 1;
        if (L > m) continue;
        bool placed = false;
        for (int it = 0; it < 10 && !placed; ++it) {
            int st = rnd.next(0, m - L);
            bool ok = true;
            for (int j = 0; j < n; ++j) {
                int pos = st + j * (d + 1);
                if (used[pos]) { ok = false; break; }
            }
            if (!ok) continue;
            // place A at this depth
            for (int j = 0; j < n; ++j) {
                int pos = st + j * (d + 1);
                B[pos] = A[j];
                used[pos] = true;
            }
            placed = true;
        }
    }

    // Output
    println(n);
    println(A);
    println(m);
    println(B);

    return 0;
}
