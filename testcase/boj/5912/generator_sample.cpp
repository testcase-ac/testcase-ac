#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int oddInRange(int lo, int hi) {
    int n = rnd.next(lo, hi);
    if (n % 2 == 0) {
        if (n == hi) {
            --n;
        } else {
            ++n;
        }
    }
    return n;
}

pair<int, int> randomInterval(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(a, n);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> ranges;

    if (mode == 0) {
        n = oddInRange(1, 15);
        int k = rnd.next(1, 10);
        for (int i = 0; i < k; ++i) {
            ranges.push_back(randomInterval(n));
        }
    } else if (mode == 1) {
        n = oddInRange(3, 25);
        int k = rnd.next(2, 12);
        for (int i = 0; i < k; ++i) {
            int a = rnd.next(1, (n + 1) / 2);
            int b = rnd.next((n + 1) / 2, n);
            ranges.push_back({a, b});
        }
    } else if (mode == 2) {
        n = oddInRange(3, 31);
        int k = rnd.next(3, 15);
        for (int i = 0; i < k; ++i) {
            int center = rnd.next(1, n);
            int radius = rnd.next(0, min(4, n - 1));
            int a = max(1, center - radius);
            int b = min(n, center + radius);
            ranges.push_back({a, b});
        }
    } else if (mode == 3) {
        n = oddInRange(5, 41);
        int k = rnd.next(4, 18);
        for (int i = 0; i < k; ++i) {
            if (i % 3 == 0) {
                ranges.push_back({1, n});
            } else if (i % 3 == 1) {
                int p = rnd.next(1, n);
                ranges.push_back({p, p});
            } else {
                ranges.push_back(randomInterval(n));
            }
        }
    } else {
        n = oddInRange(51, 101);
        int k = rnd.next(20, 80);
        for (int i = 0; i < k; ++i) {
            int a = rnd.next(1, n);
            int len = rnd.next(1, min(20, n - a + 1));
            ranges.push_back({a, a + len - 1});
        }
    }

    shuffle(ranges.begin(), ranges.end());

    println(n, (int)ranges.size());
    for (auto [a, b] : ranges) {
        println(a, b);
    }

    return 0;
}
