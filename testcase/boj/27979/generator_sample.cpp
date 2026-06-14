#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 40);
    vector<int> w(n);

    if (mode == 0) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 5);
            w[i] = cur;
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 20) + n * 5;
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0, 5);
            w[i] = max(1, cur);
        }
    } else if (mode == 2) {
        int distinct = rnd.next(1, min(n, 7));
        vector<int> values(distinct);
        for (int i = 0; i < distinct; ++i) values[i] = rnd.next(1, 30);
        sort(values.begin(), values.end());
        for (int i = 0; i < n; ++i) w[i] = rnd.any(values);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            w[i] = (i % 2 == 0 ? rnd.next(900000, 1000000) : rnd.next(1, 100000));
        }
    } else if (mode == 4) {
        int cur = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 3);
            w[i] = cur;
        }
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(n);
            int b = rnd.next(n);
            swap(w[a], w[b]);
        }
    } else if (mode == 5) {
        int prefix = rnd.next(0, n);
        for (int i = 0; i < prefix; ++i) w[i] = rnd.next(1, 100);
        int cur = rnd.next(1, 100);
        for (int i = prefix; i < n; ++i) {
            cur += rnd.next(0, 8);
            w[i] = cur;
        }
    } else {
        for (int i = 0; i < n; ++i) w[i] = rnd.next(1, 1000000);
    }

    println(n);
    println(w);

    return 0;
}
