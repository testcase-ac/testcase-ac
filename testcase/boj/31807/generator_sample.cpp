#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int period;
    int l;
    if (mode == 0) {
        period = 1;
        l = rnd.next(2, 12);
    } else if (mode == 1) {
        period = rnd.next(1, 4);
        l = 2 * period;
    } else if (mode == 2) {
        period = rnd.next(2, 6);
        l = rnd.next(2 * period, 4 * period + period - 1);
    } else {
        period = rnd.next(1, 10);
        l = rnd.next(2 * period, 30);
    }

    vector<long long> base(period);
    int value_mode = rnd.next(0, 3);
    for (int i = 0; i < period; ++i) {
        if (value_mode == 0) {
            base[i] = rnd.next(-5, 5);
        } else if (value_mode == 1) {
            base[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 20);
        } else if (value_mode == 2) {
            base[i] = rnd.next(-1000, 1000);
        } else {
            base[i] = (i == 0 ? rnd.next(-1000000000LL, 1000000000LL) : rnd.next(-9, 9));
        }
    }

    if (period > 1 && rnd.next(0, 2) == 0) {
        vector<int> order(period);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());
        vector<long long> shuffled(period);
        for (int i = 0; i < period; ++i) {
            shuffled[i] = base[order[i]];
        }
        base = shuffled;
    }

    vector<long long> values(l);
    int offset = rnd.next(0, period - 1);
    for (int i = 0; i < l; ++i) {
        values[i] = base[(i + offset) % period];
    }

    long long a;
    long long b;
    int query_mode = rnd.next(0, 5);
    if (query_mode == 0) {
        a = rnd.next(-20, 20);
        b = a;
    } else if (query_mode == 1) {
        a = rnd.next(-30, 30);
        b = a + rnd.next(1, 2 * period + 5);
    } else if (query_mode == 2) {
        a = rnd.next(-100, -1);
        b = rnd.next(0, 100);
    } else if (query_mode == 3) {
        a = rnd.next(-1000000000LL, -999999900LL);
        b = a + rnd.next(0, 200);
    } else if (query_mode == 4) {
        b = rnd.next(999999800LL, 1000000000LL);
        a = b - rnd.next(0, 200);
    } else {
        a = rnd.next(-100000, 100000);
        b = a + rnd.next(0, 200000);
    }

    println(l);
    println(values);
    println(a, b);

    return 0;
}
