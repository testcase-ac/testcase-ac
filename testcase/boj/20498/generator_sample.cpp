#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int height = rnd.next(1, 7);
    if (mode == 4) height = rnd.next(8, 10);
    int n = (1 << height) - 1;

    vector<long long> w(n + 1);
    long long low = rnd.next(1, 20);
    long long high = rnd.next(50, 100000000);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) w[i] = rnd.next(1, 100);
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            int depth = 31 - __builtin_clz(i);
            w[i] = rnd.next(1, 9) * (depth + 1);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) w[i] = low;
        int boosted = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < boosted; ++i) w[rnd.next(1, n)] = high;
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            bool isLeaf = i * 2 > n;
            w[i] = isLeaf ? rnd.next(1, 100000000) : rnd.next(1, 30);
        }
    } else if (mode == 4) {
        for (int i = 1; i <= n; ++i) w[i] = rnd.next(1, 1000);
    } else {
        for (int i = 1; i <= n; ++i) w[i] = rnd.next(1, 10);
        int cur = rnd.next(1, n);
        while (cur <= n) {
            w[cur] = rnd.next(1000000, 100000000);
            cur = cur * 2 + rnd.next(0, 1);
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << w[i];
    }
    cout << '\n';

    return 0;
}
