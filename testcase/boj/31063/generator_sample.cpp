#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long smallHeight(int limit) {
    return rnd.next(1, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 16);

    vector<long long> cows(n);
    vector<long long> candies(m);

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 4);
        cows.assign(n, 1);
        candies.assign(m, 1);
        if (rnd.next(0, 1)) {
            cows[rnd.next(n)] = rnd.next(1, 5);
        }
    } else if (mode == 1) {
        long long cur = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 5);
            cows[i] = cur;
        }
        for (int i = 0; i < m; ++i) {
            candies[i] = rnd.next(1, static_cast<int>(cur + 8));
        }
    } else if (mode == 2) {
        long long cur = rnd.next(8, 35);
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0, 3);
            cows[i] = max(1LL, cur);
        }
        for (int i = 0; i < m; ++i) {
            candies[i] = rnd.next(1, 40);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            cows[i] = smallHeight(30);
        }
        shuffle(cows.begin(), cows.end());
        for (int i = 0; i < m; ++i) {
            candies[i] = rnd.next(1, 35);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            cows[i] = rnd.next(999999900LL, 1000000000LL);
        }
        for (int i = 0; i < m; ++i) {
            candies[i] = rnd.next(999999900LL, 1000000000LL);
        }
    } else {
        int low = rnd.next(1, 12);
        int high = rnd.next(low, low + 30);
        for (int i = 0; i < n; ++i) {
            cows[i] = rnd.next(low, high);
        }
        for (int i = 0; i < m; ++i) {
            candies[i] = rnd.next(low, high + 10);
        }
        if (rnd.next(0, 1)) {
            shuffle(candies.begin(), candies.end());
        }
    }

    println(n, m);
    println(cows);
    println(candies);

    return 0;
}
