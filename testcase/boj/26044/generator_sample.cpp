#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long chooseCapped(int n, int k) {
    if (k > n - k) k = n - k;

    long long value = 1;
    for (int i = 1; i <= k; ++i) {
        value = value * (n - k + i) / i;
        if (value > 1000000000LL) return value;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> queries = {1, 2, 3, 4, 5, 10, 66, 330, 999999999, 1000000000};

    int extra = rnd.next(8, 30);
    for (int i = 0; i < extra; ++i) {
        int mode = rnd.next(5);
        if (mode == 0) {
            queries.push_back(rnd.next(1, 30));
        } else if (mode == 1) {
            int base = rnd.next(1, 31623);
            int delta = rnd.next(-2, 2);
            long long value = 1LL * base * base + delta;
            value = max(1LL, min(1000000000LL, value));
            queries.push_back(static_cast<int>(value));
        } else if (mode == 2) {
            int n = rnd.next(2, 80);
            int k = rnd.next(2, min(18, n));
            long long value = chooseCapped(n, k);
            if (value <= 1000000000LL) queries.push_back(static_cast<int>(value));
            else queries.push_back(rnd.next(1, 1000000000));
        } else if (mode == 3) {
            queries.push_back(rnd.next(999999900, 1000000000));
        } else {
            queries.push_back(rnd.next(1, 1000000000));
        }
    }

    shuffle(queries.begin(), queries.end());

    println(static_cast<int>(queries.size()));
    for (int value : queries) println(value);

    return 0;
}
