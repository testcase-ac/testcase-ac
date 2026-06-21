#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<pair<int, int>> cows;

    if (mode == 0) {
        n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 3);
            int x = rnd.next(0, 3);
            cows.push_back({v, x});
        }
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        int x = rnd.next(0, 50000);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 50000);
            cows.push_back({v, x});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        int base = rnd.next(0, 49990);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 50000);
            int x = base + rnd.next(0, 10);
            cows.push_back({v, x});
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        for (int i = 0; i < n; ++i) {
            int v = (i % 3 == 0) ? 0 : rnd.next(1, 50000);
            int x = (i % 4 == 0) ? rnd.next(0, 1) * 50000 : rnd.next(0, 50000);
            cows.push_back({v, x});
        }
    } else if (mode == 4) {
        n = rnd.next(4, 16);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 6) == 0 ? 50000 : rnd.next(0, 30);
            int x = rnd.next(0, 6) == 0 ? rnd.next(0, 1) * 50000 : rnd.next(0, 30);
            cows.push_back({v, x});
        }
    } else {
        n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(0, 50000);
            int x = rnd.next(0, 50000);
            cows.push_back({v, x});
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(cows.begin(), cows.end());
    } else {
        sort(cows.begin(), cows.end());
    }

    println(n);
    for (const auto& cow : cows) {
        println(cow.first, cow.second);
    }

    return 0;
}
