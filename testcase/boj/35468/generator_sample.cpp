#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 25);
    vector<int> b(n, 1);

    auto setPair = [&](int i, int left, int right) {
        b[i] = left;
        b[n - 1 - i] = right;
    };

    int pairs = n / 2;
    vector<int> order(pairs);
    for (int i = 0; i < pairs; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    if (mode == 0) {
        for (int i = 0; i < pairs; ++i) setPair(i, 0, 0);
        if (n % 2 == 1) b[pairs] = rnd.next(0, 1);
    } else if (mode == 1) {
        int count = min(pairs, rnd.next(1, 2));
        for (int k = 0; k < count; ++k) {
            int bit = rnd.next(0, 1);
            setPair(order[k], bit, 1 - bit);
        }
    } else if (mode == 2) {
        int count = min(pairs, rnd.next(3, 6));
        for (int k = 0; k < count; ++k) {
            int bit = rnd.next(0, 1);
            setPair(order[k], bit, 1 - bit);
        }
    } else if (mode == 3) {
        if (pairs > 0) setPair(order[0], 0, 1);
        int zeros = min(pairs - (pairs > 0 ? 1 : 0), rnd.next(1, 4));
        for (int k = 0; k < zeros; ++k) setPair(order[(pairs > 0 ? 1 : 0) + k], 0, 0);
    } else if (mode == 4) {
        for (int i = 0; i < pairs; ++i) {
            int bit = rnd.next(0, 1);
            setPair(i, bit, bit);
        }
        if (n % 2 == 1) b[pairs] = 0;
    } else if (mode == 5) {
        if (n % 2 == 0) ++n;
        b.assign(n, 1);
        pairs = n / 2;
        order.resize(pairs);
        for (int i = 0; i < pairs; ++i) order[i] = i;
        shuffle(order.begin(), order.end());
        b[pairs] = 0;
        int mismatches = min(pairs, rnd.next(2, 4));
        for (int k = 0; k < mismatches; ++k) {
            int bit = rnd.next(0, 1);
            setPair(order[k], bit, 1 - bit);
        }
    } else {
        double zeroProb = rnd.next(0.0, 1.0);
        for (int i = 0; i < n; ++i) b[i] = rnd.next() < zeroProb ? 0 : 1;
    }

    println(n);
    println(b);

    return 0;
}
