#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Start from the target configuration (solved board)
    vector<vector<int>> g(4, vector<int>(4));
    int val = 1;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            g[i][j] = val++;

    auto applyRowShift = [&](int r, int k) {
        // shift row r (0-based) to the right by k (1..3)
        vector<int> tmp(4);
        for (int c = 0; c < 4; ++c)
            tmp[(c + k) % 4] = g[r][c];
        for (int c = 0; c < 4; ++c)
            g[r][c] = tmp[c];
    };

    auto applyColShift = [&](int c, int k) {
        // shift column c (0-based) down by k (1..3)
        vector<int> tmp(4);
        for (int r = 0; r < 4; ++r)
            tmp[(r + k) % 4] = g[r][c];
        for (int r = 0; r < 4; ++r)
            g[r][c] = tmp[r];
    };

    // Choose a test pattern type for diversity
    int pattern = rnd.next(0, 5);

    if (pattern == 0) {
        // Pattern 0: Already solved or very close to solved
        int kind = rnd.next(0, 2);
        if (kind == 0) {
            // Exactly solved (0 moves applied)
        } else if (kind == 1) {
            // Apply 1 random move
            int o = rnd.next(1, 2);
            int idx = rnd.next(0, 3);
            int k = rnd.next(1, 3);
            if (o == 1) applyRowShift(idx, k);
            else applyColShift(idx, k);
        } else {
            // Apply 2 random moves
            int moves = 2;
            while (moves--) {
                int o = rnd.next(1, 2);
                int idx = rnd.next(0, 3);
                int k = rnd.next(1, 3);
                if (o == 1) applyRowShift(idx, k);
                else applyColShift(idx, k);
            }
        }
    } else if (pattern == 1) {
        // Pattern 1: Only row shifts, each row independent
        for (int r = 0; r < 4; ++r) {
            if (rnd.next(0, 1)) {
                int k = rnd.next(1, 3);
                applyRowShift(r, k);
            }
        }
    } else if (pattern == 2) {
        // Pattern 2: Only column shifts, each column independent
        for (int c = 0; c < 4; ++c) {
            if (rnd.next(0, 1)) {
                int k = rnd.next(1, 3);
                applyColShift(c, k);
            }
        }
    } else if (pattern == 3) {
        // Pattern 3: Small random sequence of moves (1..4)
        int moves = rnd.next(1, 4);
        while (moves--) {
            int o = rnd.next(1, 2);
            int idx = rnd.next(0, 3);
            int k = rnd.next(1, 3);
            if (o == 1) applyRowShift(idx, k);
            else applyColShift(idx, k);
        }
    } else if (pattern == 4) {
        // Pattern 4: Medium random sequence of moves (5..10)
        int moves = rnd.next(5, 10);
        while (moves--) {
            int o = rnd.next(1, 2);
            int idx = rnd.next(0, 3);
            int k = rnd.next(1, 3);
            if (o == 1) applyRowShift(idx, k);
            else applyColShift(idx, k);
        }
    } else {
        // Pattern 5: Longer random sequence of moves (10..20)
        int moves = rnd.next(10, 20);
        while (moves--) {
            int o = rnd.next(1, 2);
            int idx = rnd.next(0, 3);
            int k = rnd.next(1, 3);
            if (o == 1) applyRowShift(idx, k);
            else applyColShift(idx, k);
        }
    }

    // Output the resulting grid as a single test case
    for (int i = 0; i < 4; ++i)
        println(g[i]);

    return 0;
}
