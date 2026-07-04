#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(2, 5);
    if (rnd.next(8) == 0) {
        m = rnd.next(6, 10);
    }
    int n = rnd.next(3, 18);
    if (rnd.next(8) == 0) {
        n = rnd.next(19, 40);
    }

    vector<vector<vector<int>>> f(
        m + 1, vector<vector<int>>(m + 1, vector<int>(m + 1)));
    int mode = rnd.next(7);
    int constantValue = rnd.next(1, m);
    vector<int> weight = {rnd.next(0, m - 1), rnd.next(0, m - 1),
                          rnd.next(0, m - 1)};

    for (int x = 1; x <= m; ++x) {
        for (int y = 1; y <= m; ++y) {
            for (int z = 1; z <= m; ++z) {
                int value;
                if (mode == 0) {
                    value = y;
                } else if (mode == 1) {
                    value = x;
                } else if (mode == 2) {
                    value = z;
                } else if (mode == 3) {
                    value = ((x + y + z - 3) % m) + 1;
                } else if (mode == 4) {
                    value = ((weight[0] * (x - 1) + weight[1] * (y - 1) +
                              weight[2] * (z - 1)) %
                             m) +
                            1;
                } else if (mode == 5) {
                    value = constantValue;
                } else {
                    value = rnd.next(1, m);
                }
                f[x][y][z] = value;
            }
        }
    }

    vector<int> s0(n);
    if (rnd.next(2) == 0) {
        vector<int> previous(n);
        for (int i = 0; i < n; ++i) {
            previous[i] = rnd.next(1, m);
        }
        for (int i = 0; i < n; ++i) {
            int left = previous[(i + n - 1) % n];
            int self = previous[i];
            int right = previous[(i + 1) % n];
            s0[i] = f[left][self][right];
        }
    } else {
        int stateMode = rnd.next(4);
        for (int i = 0; i < n; ++i) {
            if (stateMode == 0) {
                s0[i] = rnd.next(1, m);
            } else if (stateMode == 1) {
                s0[i] = (i % m) + 1;
            } else if (stateMode == 2) {
                s0[i] = (i % 2 == 0) ? 1 : m;
            } else {
                s0[i] = rnd.next(1, min(m, 3));
            }
        }
    }

    println(n, m);
    for (int x = 1; x <= m; ++x) {
        for (int y = 1; y <= m; ++y) {
            for (int z = 1; z <= m; ++z) {
                println(f[x][y][z]);
            }
        }
    }
    println(s0);

    return 0;
}
