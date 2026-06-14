#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(12, 30);
    } else if (mode == 0) {
        n = 2;
    } else {
        n = rnd.next(3, 10);
    }

    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        vector<int> values = {0, 1, 999, 1000};
        shuffle(values.begin(), values.end());
        int pos = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = values[pos++];
            }
        }
    } else if (mode == 1) {
        int high = rnd.next(700, 1000);
        int low = rnd.next(0, 80);
        for (int i = 0; i < n; ++i) {
            bool oddPreferred = rnd.next(0, 1);
            for (int j = 0; j < n; ++j) {
                bool preferred = (j % 2 == 1) == oddPreferred;
                a[i][j] = preferred ? high - rnd.next(0, 50) : low + rnd.next(0, 50);
            }
        }
    } else if (mode == 2) {
        int high = rnd.next(700, 1000);
        int low = rnd.next(0, 80);
        for (int j = 0; j < n; ++j) {
            bool oddPreferred = rnd.next(0, 1);
            for (int i = 0; i < n; ++i) {
                bool preferred = (i % 2 == 1) == oddPreferred;
                a[i][j] = preferred ? high - rnd.next(0, 50) : low + rnd.next(0, 50);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = max(0, min(1000, base + rnd.next(-3, 3)));
            }
        }
    } else if (mode == 4) {
        int high = rnd.next(800, 1000);
        int low = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = ((i + j) % 2 == 0) ? high : low;
                if (rnd.next(0, 5) == 0) a[i][j] = rnd.next(0, 1000);
            }
        }
    } else if (mode == 5) {
        vector<int> palette = {0, 0, 1, 2, 10, 100, 999, 1000, 1000};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.any(palette);
            }
        }
    } else {
        int lo = rnd.next(0, 700);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(lo, hi);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
