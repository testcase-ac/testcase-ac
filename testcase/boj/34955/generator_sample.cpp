#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = 100000000;

int bounded(int value) {
    return max(1, min(MAX_VALUE, value));
}

vector<int> randomValues(int count, int low, int high) {
    vector<int> values;
    values.reserve(count);
    for (int i = 0; i < count; ++i) values.push_back(rnd.next(low, high));
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 18);
    vector<int> bait;
    vector<int> fish;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
        int x = rnd.next(1, 40);
        bait = {x};
        fish = randomValues(m, 1, x);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        int base = rnd.next(1, 80);
        bait = randomValues(n, 1, base);
        fish = randomValues(m, base + 1, base + 80);
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        m = rnd.next(2, 14);
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            bait.push_back(bounded(base + rnd.next(0, 3)));
        }
        for (int i = 0; i < m; ++i) {
            fish.push_back(bounded(base + rnd.next(0, 6)));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        m = rnd.next(2, 16);
        int base = rnd.next(2, 100);
        bait = randomValues(n, 1, base);
        for (int i = 0; i < m; ++i) {
            int source = bait[rnd.next(0, n - 1)];
            fish.push_back(bounded(source + rnd.next(-1, 3)));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        int high = MAX_VALUE - rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            bait.push_back(bounded(high - rnd.next(0, 50)));
        }
        for (int i = 0; i < m; ++i) {
            fish.push_back(bounded(high - rnd.next(0, 50)));
        }
    } else {
        n = rnd.next(10, 35);
        m = rnd.next(10, 35);
        int high = rnd.next(20, 1000);
        bait = randomValues(n, 1, high);
        fish = randomValues(m, 1, high);
    }

    shuffle(bait.begin(), bait.end());
    shuffle(fish.begin(), fish.end());

    println(n, m);
    println(bait);
    println(fish);
    return 0;
}
