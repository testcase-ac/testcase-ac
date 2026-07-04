#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 12);
    int k;
    if (mode == 5 || rnd.next(0, 4) == 0) {
        k = rnd.next(max(3, n * n), 1000000000);
    } else {
        k = rnd.next(3, 12);
    }

    vector<vector<int>> a(n, vector<int>(n, 1));

    if (mode == 0) {
        int base = rnd.next(1, k);
        for (int i = 0; i < n; ++i) {
            fill(a[i].begin(), a[i].end(), base);
        }
        int changes = rnd.next(1, min(n * n, 6));
        for (int t = 0; t < changes; ++t) {
            a[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = rnd.next(1, k);
        }
    } else if (mode == 1) {
        int c1 = rnd.next(1, k);
        int c2 = rnd.next(1, k);
        int c3 = rnd.next(1, k);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(0, 1) == 0) {
                    a[i][j] = (i % 2 == 0 ? c1 : c2);
                } else {
                    a[i][j] = (j % 2 == 0 ? c2 : c3);
                }
            }
        }
    } else if (mode == 2) {
        int c1 = rnd.next(1, k);
        int c2 = rnd.next(1, k);
        int c3 = rnd.next(1, k);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = ((i + j) % 2 == 0 ? c1 : c2);
            }
        }
        for (int t = 0; t < rnd.next(1, min(n, 5)); ++t) {
            a[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = c3;
        }
    } else if (mode == 3) {
        int block = rnd.next(1, max(1, n / 3));
        int palette = rnd.next(3, min(k, 8));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int bucket = (i / block + j / block) % palette;
                a[i][j] = bucket + 1;
            }
        }
    } else if (mode == 4) {
        int palette = rnd.next(3, min(k, 10));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int local = rnd.next(0, 3);
                if (local == 0 && i > 0) {
                    a[i][j] = a[i - 1][j];
                } else if (local == 1 && j > 0) {
                    a[i][j] = a[i][j - 1];
                } else {
                    a[i][j] = rnd.next(1, palette);
                }
            }
        }
    } else if (mode == 5) {
        vector<int> values;
        for (int x = 1; x <= n * n; ++x) {
            values.push_back(x);
        }
        shuffle(values.begin(), values.end());
        int at = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = values[at++];
            }
        }
    } else {
        int palette = rnd.next(3, min(k, 20));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(1, palette);
            }
        }
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
