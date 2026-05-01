#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 7);

    int n;
    int p0;
    vector<vector<int>> s(2), v(2);

    switch (type) {
        case 0: {
            // Tiny, low values
            n = rnd.next(1, 4);
            p0 = rnd.next(0, 3);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            for (int j = 0; j < n; ++j) {
                s[0][j] = rnd.next(0, 5);
                s[1][j] = rnd.next(0, 5);
                v[0][j] = rnd.next(0, 5);
                v[1][j] = rnd.next(0, 5);
            }
            break;
        }
        case 1: {
            // Large p0, high v
            n = rnd.next(5, 12);
            p0 = rnd.next(10000000, 100000000);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            for (int j = 0; j < n; ++j) {
                s[0][j] = rnd.next(0, 1000000);
                s[1][j] = rnd.next(0, 1000000);
                v[0][j] = rnd.next(500000, 1000000);
                v[1][j] = rnd.next(500000, 1000000);
            }
            break;
        }
        case 2: {
            // One employee dominates on all tasks
            n = rnd.next(4, 12);
            p0 = rnd.next(0, 50);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            int good = rnd.next(0, 1);
            int bad = 1 - good;
            for (int j = 0; j < n; ++j) {
                int sLow = rnd.next(0, 500000);
                int sExtra = rnd.next(0, 500000);
                int vLow = rnd.next(0, 500000);
                int vExtra = rnd.next(0, 500000);
                s[bad][j] = sLow;
                s[good][j] = sLow + sExtra;
                v[bad][j] = vLow;
                v[good][j] = vLow + vExtra;
            }
            break;
        }
        case 3: {
            // Each task good for exactly one employee
            n = rnd.next(3, 10);
            p0 = rnd.next(0, 20);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            for (int j = 0; j < n; ++j) {
                int winner = rnd.next(0, 1);
                int loser = 1 - winner;
                v[winner][j] = rnd.next(100, 100000);
                v[loser][j] = rnd.next(0, 5);
                s[winner][j] = rnd.next(0, 500000);
                s[loser][j] = rnd.next(0, 20);
            }
            break;
        }
        case 4: {
            // Training vs earning tasks
            n = rnd.next(5, 12);
            p0 = rnd.next(0, 10);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            for (int j = 0; j < n; ++j) {
                int pattern = rnd.next(0, 3);
                if (pattern == 0) {
                    // both training
                    for (int i = 0; i < 2; ++i) {
                        s[i][j] = rnd.next(50000, 200000);
                        v[i][j] = rnd.next(0, 10);
                    }
                } else if (pattern == 1) {
                    // both earning
                    for (int i = 0; i < 2; ++i) {
                        s[i][j] = rnd.next(0, 3);
                        v[i][j] = rnd.next(1000, 100000);
                    }
                } else if (pattern == 2) {
                    // emp1 training, emp2 earning
                    s[0][j] = rnd.next(50000, 200000);
                    v[0][j] = rnd.next(0, 10);
                    s[1][j] = rnd.next(0, 3);
                    v[1][j] = rnd.next(1000, 100000);
                } else {
                    // emp1 earning, emp2 training
                    s[1][j] = rnd.next(50000, 200000);
                    v[1][j] = rnd.next(0, 10);
                    s[0][j] = rnd.next(0, 3);
                    v[0][j] = rnd.next(1000, 100000);
                }
            }
            break;
        }
        case 5: {
            // Symmetric employees
            n = rnd.next(3, 10);
            p0 = rnd.next(0, 50);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            for (int j = 0; j < n; ++j) {
                int sb = rnd.next(0, 1000000);
                int vb = rnd.next(0, 1000000);
                s[0][j] = s[1][j] = sb;
                v[0][j] = v[1][j] = vb;
            }
            break;
        }
        case 6: {
            // Fully random within constraints (with extra zeros)
            n = rnd.next(1, 12);
            p0 = rnd.next(0, 100000000);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < n; ++j) {
                    int sval = rnd.next(0, 1000000);
                    if (rnd.next(0, 4) == 0) sval = 0; // more zeros
                    int vval = rnd.next(0, 1000000);
                    if (rnd.next(0, 4) == 0) vval = 0;
                    s[i][j] = sval;
                    v[i][j] = vval;
                }
            }
            break;
        }
        case 7: {
            // Degenerate: all-s-zero or all-v-zero, etc.
            n = rnd.next(1, 8);
            p0 = rnd.next(0, 100);
            s[0].assign(n, 0);
            s[1].assign(n, 0);
            v[0].assign(n, 0);
            v[1].assign(n, 0);
            int variant = rnd.next(0, 2);
            if (variant == 0) {
                // all s = 0, random v
                for (int i = 0; i < 2; ++i)
                    for (int j = 0; j < n; ++j)
                        v[i][j] = rnd.next(0, 1000000);
            } else if (variant == 1) {
                // all v = 0, random s
                for (int i = 0; i < 2; ++i)
                    for (int j = 0; j < n; ++j)
                        s[i][j] = rnd.next(0, 1000000);
            } else {
                // one employee has v>0, s=0; the other only s>0, v=0
                int earn = rnd.next(0, 1);
                int train = 1 - earn;
                for (int j = 0; j < n; ++j) {
                    s[earn][j] = 0;
                    v[earn][j] = rnd.next(0, 1000000);
                    s[train][j] = rnd.next(0, 1000000);
                    v[train][j] = 0;
                }
            }
            break;
        }
    }

    // Output
    println(n, p0);
    println(s[0]);
    println(s[1]);
    println(v[0]);
    println(v[1]);

    return 0;
}
