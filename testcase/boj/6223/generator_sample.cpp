#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> makeValues(int n) {
    int mode = rnd.next(0, 3);
    int base = rnd.next(1, 100000 - n + 1);
    vector<int> values;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) values.push_back(base + i);
    } else if (mode == 1) {
        int step = rnd.next(2, max(2, 100000 / n));
        base = rnd.next(1, 100000 - step * (n - 1));
        for (int i = 0; i < n; ++i) values.push_back(base + i * step);
    } else {
        set<int> used;
        while ((int)values.size() < n) {
            int x = rnd.next(1, 100000);
            if (used.insert(x).second) values.push_back(x);
        }
        sort(values.begin(), values.end());
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0) ? 1 : rnd.next(2, 16);
    vector<int> values = makeValues(n);
    vector<int> order = values;

    if (mode == 0) {
        // Single cow.
    } else if (mode == 1) {
        // Already sorted.
    } else if (mode == 2) {
        reverse(order.begin(), order.end());
    } else if (mode == 3) {
        int shift = rnd.next(1, n - 1);
        rotate(order.begin(), order.begin() + shift, order.end());
    } else if (mode == 4) {
        int len = rnd.next(2, n);
        rotate(order.begin(), order.begin() + 1, order.begin() + len);
    } else if (mode == 5) {
        for (int i = 0; i + 1 < n; i += 2) {
            if (rnd.next(0, 1)) swap(order[i], order[i + 1]);
        }
    } else {
        shuffle(order.begin(), order.end());
    }

    println(n);
    for (int x : order) println(x);

    return 0;
}
