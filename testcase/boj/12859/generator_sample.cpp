#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 18);
    vector<long long> lengths;
    vector<int> costs;

    auto add = [&](long long length, int cost) {
        lengths.push_back(length);
        costs.push_back(cost);
    };

    if (mode == 0) {
        n = 1;
        add(rnd.next(1, 2) == 1 ? 1 : rnd.next(2, 1000000000), rnd.next(1, 100000));
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) {
            add(2LL * rnd.next(1, 500000000), rnd.next(1, 100000));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 16);
        add(1, rnd.next(1, 100000));
        for (int i = 1; i < n; ++i) {
            add(rnd.next(2, 1000000000), rnd.next(1, 100000));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 16);
        long long a = 2LL * rnd.next(1, 500000000);
        long long b = 2LL * rnd.next(1, 500000000) + 1;
        if (std::gcd(a, b) != 1) b = 999999937;
        add(a, rnd.next(1, 100000));
        add(b, rnd.next(1, 100000));
        for (int i = 2; i < n; ++i) {
            add(rnd.next(2, 1000000000), rnd.next(1, 100000));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 18);
        vector<long long> pool = {6, 10, 15, 21, 35, 77};
        for (int i = 0; i < n; ++i) {
            long long factor = rnd.next(1, 1000);
            add(rnd.any(pool) * factor, rnd.next(1, 100000));
        }
    } else if (mode == 5) {
        n = rnd.next(6, 18);
        vector<long long> pool;
        for (int i = 0; i < 4; ++i) pool.push_back(rnd.next(1, 1000000000));
        for (int i = 0; i < n; ++i) {
            add(rnd.any(pool), rnd.next(1, 100000));
        }
    } else {
        n = rnd.next(12, 30);
        for (int i = 0; i < n; ++i) {
            long long length = rnd.next(1, 1000000000);
            if (rnd.next(0, 4) == 0) length = 1000000000LL - rnd.next(0, 1000);
            add(length, rnd.next(1, 100000));
        }
    }

    vector<int> order(lengths.size());
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<long long> shuffledLengths;
    vector<int> shuffledCosts;
    for (int idx : order) {
        shuffledLengths.push_back(lengths[idx]);
        shuffledCosts.push_back(costs[idx]);
    }

    println(static_cast<int>(shuffledLengths.size()));
    println(shuffledLengths);
    println(shuffledCosts);

    return 0;
}
