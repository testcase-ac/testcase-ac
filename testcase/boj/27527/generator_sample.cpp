#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int need(int m) {
    return (9 * m + 9) / 10;
}

void fillDistinct(vector<int>& a, int base) {
    for (int i = 0; i < (int)a.size(); ++i) {
        a[i] = base + i;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int m = rnd.next(1, n);
    vector<int> a(n);
    int common = rnd.next(1, 20);
    int noiseBase = rnd.next(100, 900000);

    if (mode == 0) {
        fillDistinct(a, noiseBase);
        int start = rnd.next(0, n - m);
        int cnt = need(m);
        vector<int> pos(m);
        for (int i = 0; i < m; ++i) {
            pos[i] = start + i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < cnt; ++i) {
            a[pos[i]] = common;
        }
    } else if (mode == 1) {
        fillDistinct(a, noiseBase);
        int limit = max(0, need(m) - 1);
        for (int start = 0; start + m <= n; start += m) {
            int cnt = rnd.next(0, min(limit, m));
            vector<int> pos(m);
            for (int i = 0; i < m; ++i) {
                pos[i] = start + i;
            }
            shuffle(pos.begin(), pos.end());
            int value = common + start + 1;
            for (int i = 0; i < cnt; ++i) {
                a[pos[i]] = value;
            }
        }
    } else if (mode == 2) {
        fillDistinct(a, noiseBase);
        int start = rnd.next(0, n - m);
        int cnt = max(0, need(m) - 1);
        for (int i = 0; i < cnt; ++i) {
            a[start + i] = common;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 6);
        }
    } else if (mode == 4) {
        int block = rnd.next(1, max(1, min(n, 8)));
        for (int i = 0; i < n; ++i) {
            a[i] = common + (i / block) % 3;
        }
    } else {
        fillDistinct(a, noiseBase);
        int cnt = rnd.next(1, n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < cnt; ++i) {
            a[pos[i]] = 1000000;
        }
    }

    println(n, m);
    println(a);
    return 0;
}
