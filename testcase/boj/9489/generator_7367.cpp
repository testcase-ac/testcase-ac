#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 8);
    for (int tc = 0; tc < T; ++tc) {
        // Choose n with variability: small, medium, large
        int n;
        int mode = rnd.next(0, 2);
        if (mode == 0) n = rnd.next(1, 5);
        else if (mode == 1) n = rnd.next(6, 15);
        else n = rnd.next(16, 30);

        // Number of blocks (after root)
        int b = (n <= 1 ? 0 : rnd.next(1, n - 1));

        // Generate split points to partition n-1 into b positive sizes
        vector<int> splits;
        if (b >= 2) {
            splits.resize(b - 1);
            for (int i = 0; i < b - 1; ++i)
                splits[i] = rnd.next(1, n - 2);
            sort(splits.begin(), splits.end());
        }

        // Compute block sizes
        vector<int> block_sizes;
        int remaining = n - 1;
        int last = 0;
        for (int i = 0; i < b; ++i) {
            int sz;
            if (i == b - 1) sz = remaining;
            else {
                sz = splits[i] - last;
                last = splits[i];
            }
            block_sizes.push_back(sz);
            remaining -= sz;
        }

        // Build the sequence with gaps ≥ 2 between blocks
        int root = rnd.next(1, 1000);
        vector<int> seq;
        seq.push_back(root);
        int cur = 0;
        if (!block_sizes.empty())
            cur = root + rnd.next(2, 5);
        for (int sz : block_sizes) {
            for (int j = 0; j < sz; ++j)
                seq.push_back(cur + j);
            cur = cur + sz + rnd.next(1, 3);
        }

        // Choose k from the sequence
        int k = rnd.any(seq);

        // Output this test case
        println((int)seq.size(), k);
        println(seq);
    }

    // Terminate input
    println(0, 0);

    return 0;
}
