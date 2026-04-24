#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size n
    int n = rnd.next(3, 10);

    // Generate n distinct positive integers up to 1e9
    set<int> s;
    while (int(s.size()) < n) {
        s.insert(rnd.next(1, 1000000000));
    }
    vector<int> pool(s.begin(), s.end());
    sort(pool.begin(), pool.end());

    // Choose a pattern for diversity
    // 0: fully random
    // 1: strictly increasing
    // 2: strictly decreasing
    // 3: composed of sorted blocks (randomly ascending/descending)
    int pattern = rnd.next(0, 3);
    vector<int> Q;

    if (pattern == 0) {
        // Random permutation
        shuffle(pool.begin(), pool.end());
        Q = pool;
    }
    else if (pattern == 1) {
        // Increasing
        Q = pool;
    }
    else if (pattern == 2) {
        // Decreasing
        Q = pool;
        reverse(Q.begin(), Q.end());
    }
    else {
        // Block-wise sorted segments
        int B = rnd.next(2, min(n, 5));
        // Initialize block sizes to 1
        vector<int> blk(B, 1);
        int rem = n - B;
        // Distribute the remaining positions randomly
        for (int i = 0; i < rem; i++) {
            int b = rnd.next(0, B - 1);
            blk[b]++;
        }
        // Assign elements from the sorted pool into blocks
        Q.reserve(n);
        int ptr = 0;
        for (int i = 0; i < B; i++) {
            vector<int> segment(pool.begin() + ptr, pool.begin() + ptr + blk[i]);
            // Randomly choose ascending or descending within block
            if (rnd.next(0, 1) == 1) {
                reverse(segment.begin(), segment.end());
            }
            for (int x : segment) Q.push_back(x);
            ptr += blk[i];
        }
    }

    // Output
    println(n);
    println(Q);

    return 0;
}
