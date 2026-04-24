#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checking
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Prepare column hearing sets
    vector<vector<bool>> cols(M, vector<bool>(N, false));

    // With some probability, all columns identical
    if (rnd.next() < 0.2) {
        // Generate one random base set
        vector<bool> base(N);
        for (int i = 0; i < N; i++) {
            base[i] = rnd.next(0, 1) == 1;
        }
        for (int j = 0; j < M; j++) {
            cols[j] = base;
        }
    } else {
        // Build a nested chain of sets: cols[0] ⊆ cols[1] ⊆ ... ⊆ cols[M-1]
        vector<bool> prev(N, false);
        for (int j = 0; j < M; j++) {
            vector<bool> cur = prev;
            // Collect persons not yet in prev
            vector<int> remain;
            for (int i = 0; i < N; i++) {
                if (!prev[i]) remain.push_back(i);
            }
            // Randomly decide how many new persons to add
            int to_add = remain.empty() ? 0 : rnd.next(0, (int)remain.size());
            shuffle(remain.begin(), remain.end());
            for (int k = 0; k < to_add; k++) {
                cur[remain[k]] = true;
            }
            cols[j] = cur;
            prev = cur;
        }
    }

    // Permute column order for diversity
    vector<int> perm(M);
    for (int i = 0; i < M; i++) perm[i] = i;
    shuffle(perm.begin(), perm.end());

    // Build the output matrix by applying permuted columns
    vector<vector<int>> a(N, vector<int>(M));
    for (int j = 0; j < M; j++) {
        int orig = perm[j];
        for (int i = 0; i < N; i++) {
            a[i][j] = cols[orig][i] ? 1 : 0;
        }
    }

    // Print result
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }
    return 0;
}
