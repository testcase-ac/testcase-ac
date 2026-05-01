#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);
    int n;
    vector<vector<int>> tri;

    if (scenario == 0) {
        // Edge case: n = 1, with special values
        n = 1;
        int choice = rnd.next(0, 3);
        int v;
        if (choice == 0) v = 0;
        else if (choice == 1) v = 1;
        else if (choice == 2) v = 9999;
        else v = rnd.next(0, 50);
        tri = {{v}};
    } else if (scenario == 1) {
        // Small random triangle with small values
        n = rnd.next(2, 6);
        int limitVal = rnd.any(vector<int>{5, 9, 20, 50});
        tri.assign(n, {});
        for (int i = 0; i < n; ++i) {
            tri[i].resize(i + 1);
            for (int j = 0; j <= i; ++j) {
                tri[i][j] = rnd.next(0, limitVal);
            }
        }
    } else if (scenario == 2) {
        // Medium random triangle (still small enough to read)
        n = rnd.next(7, 10);
        int limitVal = rnd.any(vector<int>{9, 20, 50, 100, 500});
        tri.assign(n, {});
        for (int i = 0; i < n; ++i) {
            tri[i].resize(i + 1);
            for (int j = 0; j <= i; ++j) {
                tri[i][j] = rnd.next(0, limitVal);
            }
        }
    } else if (scenario == 3) {
        // One clearly dominant path: all off-path values tiny
        n = rnd.next(3, 8);
        tri.assign(n, {});
        vector<int> pos(n);
        pos[0] = 1; // positions are 1-based conceptually

        for (int i = 1; i < n; ++i) {
            if (pos[i - 1] == i) {
                pos[i] = pos[i - 1];
            } else {
                int shift = rnd.next(0, 1);
                pos[i] = pos[i - 1] + shift;
            }
        }

        int baseLarge = rnd.next(5, 20);
        int delta = rnd.next(0, 5);

        for (int i = 0; i < n; ++i) {
            tri[i].resize(i + 1);
            for (int j = 0; j <= i; ++j) {
                int idx = j + 1; // 1-based index in row
                if (idx == pos[i]) {
                    tri[i][j] = baseLarge + rnd.next(0, delta);
                } else {
                    tri[i][j] = rnd.next(0, 1);
                }
            }
        }
    } else if (scenario == 4) {
        // Fixed "greedy trap" triangle where local-greedy is wrong
        n = 4;
        tri = {
            {5},
            {9, 1},
            {1, 1, 100},
            {1, 1, 1, 1}
        };
        // Explanation (for human, not printed):
        // Greedy picks: 5 -> 9 -> 1 -> 1 = 16
        // Optimal:      5 -> 1 -> 100 -> 1 = 107
    } else if (scenario == 5) {
        // Values near upper bound to test handling of large numbers
        n = rnd.next(2, 6);
        tri.assign(n, {});
        for (int i = 0; i < n; ++i) {
            tri[i].resize(i + 1);
            for (int j = 0; j <= i; ++j) {
                tri[i][j] = rnd.next(9000, 9999);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(tri[i]);
    }

    return 0;
}
