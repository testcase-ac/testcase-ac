#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

int boundedMultiple(int base, int minMul, int maxMul) {
    int hi = min(maxMul, 1000000 / base);
    return base * rnd.next(minMul, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 40);
    int q = rnd.next(1, 35);

    vector<int> values;
    values.reserve(n);

    if (mode == 0) {
        int base = rnd.next(1, 120);
        for (int i = 0; i < n; ++i) {
            values.push_back(boundedMultiple(base, 1, 80));
        }
    } else if (mode == 1) {
        vector<int> pool = {1, 2, 3, 4, 6, 8, 9, 12, 18, 24, 36, 72, 144, 1000000};
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        int anchor = rnd.next(2, 200);
        for (int i = 0; i < n; ++i) {
            int factor = rnd.next(1, 30);
            int noise = rnd.next(0, 3);
            values.push_back(min(1000000, anchor * factor + noise));
        }
    } else if (mode == 3) {
        vector<int> pool = {999983, 999979, 999961, 499991, 333331, 250000, 500000, 750000, 1000000};
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(pool));
        }
    } else {
        n = rnd.next(25, 80);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(1, 1000000));
        }
    }

    shuffle(values.begin(), values.end());

    set<int> interesting;
    interesting.insert(1);
    interesting.insert(1000000);
    for (int x : values) {
        interesting.insert(x);
        for (int d = 1; d * d <= x; ++d) {
            if (x % d == 0 && rnd.next(4) == 0) {
                interesting.insert(d);
                interesting.insert(x / d);
            }
        }
    }

    vector<int> queries;
    queries.reserve(q);
    vector<int> choices(interesting.begin(), interesting.end());
    while ((int)queries.size() < q) {
        int roll = rnd.next(100);
        if (roll < 65 && !choices.empty()) {
            queries.push_back(rnd.any(choices));
        } else if (roll < 85) {
            queries.push_back(rnd.next(1, 250));
        } else {
            queries.push_back(rnd.next(1, 1000000));
        }
    }

    println((int)values.size());
    println(values);
    println((int)queries.size());
    for (int k : queries) {
        println(k);
    }

    return 0;
}
