#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> shirts;

    int type = rnd.next(0, 7);

    if (type == 0) {
        // Tiny random, very small counts
        int C = rnd.next(1, 6);
        shirts.resize(C);
        for (int i = 0; i < C; i++)
            shirts[i] = rnd.next(1, 6);
    } else if (type == 1) {
        // Edge: fewer than 5 colors
        int C = rnd.next(1, 4);
        shirts.resize(C);
        // Mix very small and somewhat larger counts
        for (int i = 0; i < C; i++) {
            if (rnd.next(0, 1))
                shirts[i] = rnd.next(1, 3);
            else
                shirts[i] = rnd.next(4, 15);
        }
    } else if (type == 2) {
        // Balanced moderate counts
        int C = rnd.next(5, 10);
        int base = rnd.next(1, 5);
        shirts.resize(C);
        for (int i = 0; i < C; i++)
            shirts[i] = base + rnd.next(0, 1); // base or base+1
    } else if (type == 3) {
        // One dominant color, others small
        int C = rnd.next(5, 10);
        shirts.resize(C);
        int bigIndex = rnd.next(0, C - 1);
        for (int i = 0; i < C; i++) {
            if (i == bigIndex)
                shirts[i] = rnd.next(8, 20);
            else
                shirts[i] = rnd.next(1, 4);
        }
    } else if (type == 4) {
        // Random, ensure total sum not multiple of 5 (emphasize partial last week)
        int C = rnd.next(5, 10);
        shirts.resize(C);
        int sum = 0;
        for (int i = 0; i < C; i++) {
            shirts[i] = rnd.next(1, 10);
            sum += shirts[i];
        }
        if (sum % 5 == 0) {
            int idx = rnd.next(0, C - 1);
            if (shirts[idx] < 20) shirts[idx]++;
            else shirts[idx]--;
        }
    } else if (type == 5) {
        // Many colors but some bottlenecks (many 1s)
        int C = rnd.next(5, 10);
        shirts.resize(C);
        for (int i = 0; i < C; i++) {
            int mode = rnd.next(0, 2);
            if (mode == 0)
                shirts[i] = 1;
            else if (mode == 1)
                shirts[i] = rnd.next(2, 4);
            else
                shirts[i] = rnd.next(5, 10);
        }
    } else if (type == 6) {
        // Many colors, each with very small count
        int C = rnd.next(8, 12);
        shirts.resize(C);
        for (int i = 0; i < C; i++)
            shirts[i] = rnd.next(1, 3);
    } else {
        // Hand-crafted tricky patterns (including samples)
        vector<vector<int>> presets = {
            // Sample tests from statement
            {4, 4, 3},                 // Example 1
            {4, 2, 2, 2, 2, 3},        // Example 2
            {3, 3, 4, 3, 2},           // Example 3

            // Fewer than 5 colors, plenty of shirts
            {10, 10, 10},
            {2, 2, 2, 2},

            // Strongly skewed
            {10, 1, 1, 1, 1},
            {7, 1, 1, 1, 1, 1},

            // Slightly skewed with interesting remainders
            {2, 1, 1, 1, 1},
            {3, 3, 3, 1, 1},
            {5, 4, 4, 4, 4},

            // Many small counts
            {1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2},
            {3, 2, 2, 1, 1, 1},

            // Uneven mid-sized
            {6, 5, 3, 2, 2},
            {8, 3, 3, 3, 1}
        };
        shirts = rnd.any(presets);
    }

    int C = (int)shirts.size();
    println(C);
    for (int i = 0; i < C; i++)
        println(shirts[i]);

    return 0;
}
