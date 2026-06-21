#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(long long x) {
    if (x < 1) return 1;
    if (x > 100000000) return 100000000;
    return static_cast<int>(x);
}

vector<int> makeCluster(int count, int center, int spread) {
    vector<int> values;
    values.reserve(count);
    for (int i = 0; i < count; ++i) {
        values.push_back(clampValue(center + rnd.next(-spread, spread)));
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    vector<int> bait;
    vector<int> fish;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
        int base = rnd.next(1, 12);
        bait = makeCluster(n, base, 2);
        fish = makeCluster(m, base, 2);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        int base = rnd.next(1, 30);
        bait = makeCluster(n, base, 1);
        fish = makeCluster(m, base + rnd.next(0, 3), 1);
    } else if (mode == 2) {
        n = rnd.next(1, 10);
        m = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) bait.push_back(rnd.any(vector<int>{1, 2, 3, 99999999, 100000000}));
        for (int i = 0; i < m; ++i) fish.push_back(rnd.any(vector<int>{1, 2, 3, 99999999, 100000000}));
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        m = rnd.next(6, 18);
        int low = rnd.next(1, 100);
        int high = rnd.next(low, low + 200);
        for (int i = 0; i < n; ++i) bait.push_back(rnd.next(low, high));
        for (int i = 0; i < m; ++i) fish.push_back(rnd.next(low, high));
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        int value = rnd.next(1, 100000000);
        bait.assign(n, value);
        fish.assign(m, value);
        if (rnd.next(0, 1) == 1) {
            fish[rnd.next(m)] = clampValue(static_cast<long long>(value) + rnd.next(1, 5));
        }
    } else {
        n = rnd.next(10, 30);
        m = rnd.next(10, 30);
        int center = rnd.next(10, 1000000);
        int spread = rnd.next(5, 1000);
        bait = makeCluster(n, center, spread);
        fish = makeCluster(m, center + rnd.next(-spread, spread), spread);
    }

    if (rnd.next(0, 1) == 1) shuffle(bait.begin(), bait.end());
    if (rnd.next(0, 1) == 1) shuffle(fish.begin(), fish.end());

    println(n, m);
    println(bait);
    println(fish);

    return 0;
}
