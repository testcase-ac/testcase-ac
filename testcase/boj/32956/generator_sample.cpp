#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long k;
    vector<pair<long long, long long>> items;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1LL, 1000000000LL);
        long long a = rnd.next(1LL, 20LL);
        long long b = rnd.next(1LL, 1000000000LL);
        items.push_back({a, b});
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.next(1LL, 20LL);
        long long b = rnd.next(5LL, 40LL);
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(1LL, 6LL);
            items.push_back({a, b});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        k = rnd.next(10LL, 80LL);
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(1LL, 4LL);
            long long b = rnd.next(1LL, 25LL);
            items.push_back({a, b});
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        k = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(900000000LL, 1000000000LL);
            long long b = rnd.next(1LL, 1000000000LL);
            items.push_back({a, b});
        }
    } else if (mode == 4) {
        n = rnd.next(5, 30);
        k = rnd.next(1LL, 200LL);
        long long baseB = rnd.next(100LL, 10000LL);
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(1LL, 100LL);
            long long b = max(1LL, baseB + rnd.next(-20LL, 20LL));
            items.push_back({a, b});
        }
    } else {
        n = rnd.next(10, 60);
        k = rnd.next(500LL, 5000LL);
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(1LL, 1000000000LL);
            long long b = rnd.next(1LL, 1000000000LL);
            items.push_back({a, b});
        }
    }

    shuffle(items.begin(), items.end());

    println(n, k);
    for (const auto& item : items) {
        println(item.first, item.second);
    }

    return 0;
}
