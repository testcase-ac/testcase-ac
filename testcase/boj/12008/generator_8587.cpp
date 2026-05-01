#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6); // 7 different pattern modes
    int N;
    vector<int> a;

    if (mode == 0) {
        // Mode 0: very small random sequence
        N = rnd.next(2, 5);
        a.resize(N);
        for (int i = 0; i < N; ++i)
            a[i] = rnd.next(1, 5); // small values, some duplicates likely
    } else if (mode == 1) {
        // Mode 1: small to medium, with bias toward equal neighbors
        N = rnd.next(6, 10);
        a.resize(N);
        a[0] = rnd.next(1, 10);
        for (int i = 1; i < N; ++i) {
            if (rnd.next(0, 99) < 60)
                a[i] = a[i - 1];           // 60% chance to repeat previous (enable merges)
            else
                a[i] = rnd.next(1, 10);
        }
    } else if (mode == 2) {
        // Mode 2: power-of-two block of identical numbers
        int e = rnd.next(1, 5); // 2,4,8,16,32
        N = 1 << e;
        int v = rnd.next(1, 10);
        a.assign(N, v);
    } else if (mode == 3) {
        // Mode 3: handcrafted tricky patterns where merge order matters
        vector<vector<int>> patterns = {
            {1, 1, 1, 2},
            {1, 2, 2, 2, 1},
            {2, 2, 1, 1, 2, 2},
            {1, 1, 2, 2, 2, 2, 1, 1},
            {3, 3, 2, 2, 2, 2, 3, 3},
            {1, 2, 1, 2, 1, 2}
        };
        a = rnd.any(patterns);
        // Randomly shift values up a bit while staying ≤ 40
        int add = rnd.next(0, 3);
        for (int &x : a) {
            x = min(40, x + add);
        }
        N = (int)a.size();
    } else if (mode == 4) {
        // Mode 4: big-merge case where optimal answer > 40
        // e.g., 32 copies of 40 → maximum possible value is 45
        int lenOptions[2] = {16, 32};
        N = lenOptions[rnd.next(0, 1)];
        a.assign(N, 40);
    } else if (mode == 5) {
        // Mode 5: ascending or descending sequences, mostly non-mergeable
        N = rnd.next(5, 15);
        a.resize(N);
        bool ascending = rnd.next(0, 1);
        if (ascending) {
            int start = rnd.next(1, max(1, 40 - N + 1));
            for (int i = 0; i < N; ++i)
                a[i] = start + i; // strictly increasing
        } else {
            int start = rnd.next(N, 40);
            for (int i = 0; i < N; ++i)
                a[i] = start - i; // strictly decreasing
        }
    } else {
        // Mode 6: sequence built from several equal-number blocks
        // encourages multiple merge options and interactions
        while (true) {
            a.clear();
            int blocks = rnd.next(2, 5);
            for (int b = 0; b < blocks; ++b) {
                int v = rnd.next(1, 10);
                int len = rnd.next(1, 4);          // base length 1..4
                if (rnd.next(0, 99) < 50) len++;   // 50% chance to extend (more merges)
                if ((int)a.size() + len > 40) {
                    // trim to not exceed 40
                    len = max(1, 40 - (int)a.size());
                }
                for (int i = 0; i < len; ++i)
                    a.push_back(v);
                if ((int)a.size() >= 40) break;
            }
            N = (int)a.size();
            if (N >= 2) break;
        }
        // Occasionally shuffle blocks a little to avoid too-regular patterns
        if (rnd.next(0, 99) < 40) {
            // Randomly pick a subsegment and reverse it
            int l = rnd.next(0, N - 1);
            int r = rnd.next(l, N - 1);
            while (l < r) {
                swap(a[l], a[r]);
                ++l; --r;
            }
        }
    }

    println(N);
    for (int x : a)
        println(x);

    return 0;
}
