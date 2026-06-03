#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_C = (1LL << 31) - 1;
    int mode = rnd.next(0, 5);
    int n;
    int k;
    long long m;
    vector<pair<int, long long>> beers;

    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(n, 8);
        int base = rnd.next(1, 20);
        long long threshold = rnd.next(1, 30);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(base, base + 15);
            sum += v;
            beers.push_back({v, rnd.next(1LL, threshold)});
        }
        for (int i = n; i < k; ++i) {
            int v = rnd.next(0, base + 20);
            long long c = rnd.next(threshold, threshold + 20);
            beers.push_back({v, c});
        }
        m = rnd.next(max(1LL, sum - rnd.next(0, 10)), sum);
    } else if (mode == 1) {
        n = rnd.next(1, 5);
        k = rnd.next(n, 9);
        for (int i = 0; i < k; ++i) {
            int v = rnd.next(0, 30);
            long long c = rnd.next(1LL, 40LL);
            beers.push_back({v, c});
        }
        m = min(MAX_C, 1LL + 10000LL * n + rnd.next(1, 100));
    } else if (mode == 2) {
        n = rnd.next(2, 6);
        k = rnd.next(n, 10);
        long long lowC = rnd.next(1LL, 5LL);
        long long highC = rnd.next(6LL, 60LL);
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            int v = (i % 3 == 0) ? 0 : rnd.next(1, 100);
            long long c = (i < n - 1) ? lowC : highC;
            if (i >= n - 1 && i < 2 * n - 1) sum += v;
            beers.push_back({v, c});
        }
        m = max(1LL, sum - rnd.next(0, 20));
    } else if (mode == 3) {
        n = rnd.next(1, 7);
        k = rnd.next(n, 12);
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            int v = rnd.next(9000, 10000);
            long long c = (rnd.next(0, 1) == 0) ? MAX_C : rnd.next(MAX_C - 1000, MAX_C);
            beers.push_back({v, c});
            if (i < n) sum += v;
        }
        m = rnd.next(max(1LL, sum - 1000), min(MAX_C, sum));
    } else if (mode == 4) {
        n = rnd.next(8, 20);
        k = rnd.next(n, 30);
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            int v = rnd.next(0, 10000);
            long long c = rnd.next(1LL, 200LL);
            beers.push_back({v, c});
            if (i < n) sum += v;
        }
        m = rnd.next(1LL, min(MAX_C, max(1LL, sum)));
    } else {
        n = rnd.next(1, 8);
        k = n;
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            int v = rnd.next(0, 10000);
            long long c = rnd.next(1LL, 1000000000LL);
            beers.push_back({v, c});
            sum += v;
        }
        m = rnd.next(1LL, min(MAX_C, max(1LL, sum + rnd.next(-20, 20))));
    }

    shuffle(beers.begin(), beers.end());
    println(n, m, k);
    for (auto beer : beers) {
        println(beer.first, beer.second);
    }

    return 0;
}
