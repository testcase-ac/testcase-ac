#include "testlib.h"

#include <vector>

using namespace std;

int boundedValue(int value) {
    if (value < -1000) {
        return -1000;
    }
    if (value > 1000) {
        return 1000;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);

    if (mode == 0) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (mode == 1) {
        n = rnd.any(vector<int>{2, 3, rnd.next(4, 8)});
        m = rnd.next(8, 18);
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        m = rnd.any(vector<int>{2, 3, rnd.next(4, 8)});
    } else if (mode == 6) {
        n = rnd.next(15, 30);
        m = rnd.next(15, 30);
    }

    vector<vector<int>> d(n, vector<int>(m, 0));

    if (mode == 0) {
        vector<int> palette = {-1000, -5, -1, 0, 1, 5, 1000};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                d[i][j] = rnd.any(palette);
            }
        }
    } else if (mode == 1 || mode == 2) {
        int base = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                d[i][j] = base + rnd.next(-3, 3);
            }
        }
        for (int i = 0; i < n; ++i) {
            d[i][rnd.next(0, m - 1)] = rnd.any(vector<int>{-1000, 1000});
        }
        for (int j = 0; j < m; ++j) {
            d[rnd.next(0, n - 1)][j] = rnd.any(vector<int>{-1000, 1000});
        }
    } else if (mode == 3) {
        int value = rnd.any(vector<int>{-1000, -1, 0, 1, 1000, rnd.next(-30, 30)});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                d[i][j] = value;
            }
        }
    } else if (mode == 4) {
        vector<int> rowBias(n), colBias(m);
        for (int i = 0; i < n; ++i) {
            rowBias[i] = rnd.next(-40, 40);
        }
        for (int j = 0; j < m; ++j) {
            colBias[j] = rnd.next(-40, 40);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                d[i][j] = boundedValue(rowBias[i] + colBias[j] + rnd.next(-5, 5));
            }
        }
    } else if (mode == 5) {
        int high = rnd.next(20, 200);
        int low = -rnd.next(20, 200);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                d[i][j] = ((i + j + rnd.next(0, 1)) % 2 == 0 ? high : low);
            }
        }
    } else {
        int lo = rnd.next(-1000, 0);
        int hi = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(0, 5) == 0) {
                    d[i][j] = rnd.any(vector<int>{-1000, 1000});
                } else {
                    d[i][j] = rnd.next(lo, hi);
                }
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(d[i]);
    }

    return 0;
}
