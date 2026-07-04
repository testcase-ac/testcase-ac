#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int ceilDiv(int a, int b) {
    return (a + b - 1) / b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 15);
    int m;

    if (mode == 0) {
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        m = rnd.next(2, 8);
    } else if (mode == 2) {
        m = rnd.next(3, 12);
    } else if (mode == 3) {
        m = rnd.next(1, 20);
    } else {
        m = rnd.next(20, 80);
    }

    vector<int> c(m);
    vector<vector<int>> r(n, vector<int>(m));

    if (mode == 0) {
        for (int j = 0; j < m; ++j) {
            c[j] = rnd.next(1, 40);
            int fullShare = ceilDiv(c[j], n);
            for (int i = 0; i < n; ++i) {
                int around = rnd.next(max(0, fullShare - 2), fullShare + 2);
                r[i][j] = min(10000000, around);
            }
        }
        if (rnd.next(0, 1) == 0) {
            int student = rnd.next(0, n - 1);
            for (int j = 0; j < m; ++j) r[student][j] = 0;
        }
    } else if (mode == 1) {
        for (int j = 0; j < m; ++j) {
            c[j] = rnd.next(1, 200);
            int groupSize = rnd.next(1, n);
            int need = ceilDiv(c[j], groupSize);
            for (int i = 0; i < n; ++i) {
                int delta = rnd.next(-1, 1);
                r[i][j] = max(0, need + delta);
            }
        }
    } else if (mode == 2) {
        for (int j = 0; j < m; ++j) {
            c[j] = rnd.next(1, 500);
            int cheapFor = rnd.next(0, n - 1);
            for (int i = 0; i < n; ++i) {
                if (i == cheapFor || rnd.next(0, 3) == 0) {
                    r[i][j] = rnd.next(ceilDiv(c[j], n), c[j]);
                } else {
                    r[i][j] = rnd.next(0, max(0, ceilDiv(c[j], n) - 1));
                }
            }
        }
    } else if (mode == 3) {
        for (int j = 0; j < m; ++j) {
            c[j] = rnd.next(1, 10000000);
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 4) == 0) {
                    r[i][j] = rnd.next(0, 3);
                } else if (rnd.next(0, 4) == 0) {
                    r[i][j] = 10000000;
                } else {
                    r[i][j] = rnd.next(0, 10000000);
                }
            }
        }
    } else {
        for (int j = 0; j < m; ++j) {
            c[j] = rnd.next(1, 1000);
            int base = rnd.next(0, 1000);
            for (int i = 0; i < n; ++i) {
                int span = rnd.next(0, 30);
                r[i][j] = min(10000000, max(0, base + rnd.next(-span, span)));
            }
        }
    }

    vector<int> order(m);
    for (int j = 0; j < m; ++j) order[j] = j;
    shuffle(order.begin(), order.end());

    vector<int> outC(m);
    for (int idx = 0; idx < m; ++idx) outC[idx] = c[order[idx]];

    println(n, m);
    println(outC);
    for (int i = 0; i < n; ++i) {
        vector<int> row(m);
        for (int idx = 0; idx < m; ++idx) row[idx] = r[i][order[idx]];
        println(row);
    }

    return 0;
}
