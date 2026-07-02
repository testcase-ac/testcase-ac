#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

using Item = tuple<int, int, long long>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int s = 1;
    int n = 1;
    vector<Item> items;

    if (mode == 0) {
        s = rnd.next(1, 12);
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, s);
            int v = rnd.next(1, 40);
            long long k = rnd.next(1, 6);
            items.emplace_back(v, w, k);
        }
    } else if (mode == 1) {
        s = rnd.next(20, 80);
        n = rnd.next(8, 25);
        int baseWeight = rnd.next(1, min(s, 10));
        for (int i = 0; i < n; ++i) {
            int w = min(s, baseWeight + rnd.next(0, 3));
            int v = rnd.next(1, 200);
            long long k = rnd.next(1, 30);
            items.emplace_back(v, w, k);
        }
    } else if (mode == 2) {
        s = rnd.next(30, 150);
        n = rnd.next(5, 20);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, s);
            int v = rnd.next(1, 1000000);
            long long k = rnd.next(100000000LL, 1000000000LL);
            items.emplace_back(v, w, k);
        }
    } else if (mode == 3) {
        s = rnd.next(40, 200);
        n = rnd.next(10, 35);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, min(s, 30));
            int v = w * rnd.next(1, 20) + rnd.next(0, 5);
            long long k = rnd.next(1, 1000);
            items.emplace_back(v, w, k);
        }
    } else if (mode == 4) {
        s = 2000;
        n = rnd.next(15, 45);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 2000);
            int v = rnd.next(900000, 1000000);
            long long k = rnd.next(1LL, 1000000000LL);
            items.emplace_back(v, w, k);
        }
    } else {
        s = rnd.next(100, 500);
        n = rnd.next(30, 80);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, s);
            int v = rnd.next(1, 1000000);
            long long k = rnd.next(1, 1000000);
            items.emplace_back(v, w, k);
        }
    }

    shuffle(items.begin(), items.end());

    println(s, n);
    for (auto [v, w, k] : items) {
        println(v, w, k);
    }

    return 0;
}
