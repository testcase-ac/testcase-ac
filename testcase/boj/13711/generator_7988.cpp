#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N: occasionally small, sometimes moderate
    int N = (rnd.next(0, 3) == 0 ? rnd.next(1, 5) : rnd.next(6, 15));
    // Build a random permutation A of [1..N]
    vector<int> A(N);
    iota(A.begin(), A.end(), 1);
    shuffle(A.begin(), A.end());
    // Prepare B starting from A
    vector<int> B = A;
    // Define available patterns based on N
    vector<int> patterns;
    patterns.push_back(0); // pure shuffle
    if (N >= 2) {
        patterns.push_back(1); // reverse
        patterns.push_back(2); // random few swaps
        patterns.push_back(3); // block shuffle
    }
    int pattern = rnd.any(patterns);
    if (pattern == 0) {
        // Completely random permutation
        shuffle(B.begin(), B.end());
    } else if (pattern == 1) {
        // Reverse
        reverse(B.begin(), B.end());
    } else if (pattern == 2) {
        // A few random swaps
        int swaps = rnd.next(1, max(1, N/3));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(0, N-1), y = rnd.next(0, N-1);
            swap(B[x], B[y]);
        }
    } else {
        // Block shuffle: split into 2..min(N,4) blocks and permute them
        int maxBlocks = min(N, 4);
        int blocks = rnd.next(2, maxBlocks);
        vector<int> sizes(blocks, 1);
        int rem = N - blocks;
        for (int i = 0; i < rem; ++i)
            sizes[rnd.next(0, blocks-1)]++;
        vector<vector<int>> blks;
        int idx = 0;
        for (int sz : sizes) {
            vector<int> blk;
            for (int j = 0; j < sz; ++j)
                blk.push_back(B[idx++]);
            blks.push_back(blk);
        }
        shuffle(blks.begin(), blks.end());
        vector<int> newB;
        for (auto &blk : blks)
            for (int v : blk)
                newB.push_back(v);
        B = newB;
    }
    // Output
    println(N);
    println(A);
    println(B);
    return 0;
}
