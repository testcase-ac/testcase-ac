#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> bottles;

    if (mode == 0) {
        int n = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            bottles.push_back({rnd.next(1, 5), rnd.next(1, 10)});
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 10);
        int ratio = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 12);
            bottles.push_back({w, min(100000, w * ratio)});
        }
    } else if (mode == 2) {
        int n = rnd.next(5, 12);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(2, 30);
            int base = rnd.next(1, 20);
            int delta = rnd.next(-1, 1);
            int v = max(1, min(100000, w * base + delta));
            bottles.push_back({w, v});
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 12);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 20);
            int v = rnd.next(1, 100);
            if (i % 3 == 0) v = rnd.next(50000, 100000);
            bottles.push_back({w, v});
        }
    } else if (mode == 4) {
        int n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 100000);
            int v = rnd.next(1, 100000);
            bottles.push_back({w, v});
        }
    } else {
        int n = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            int w = (i == 0 ? 100000 : rnd.next(1, 10));
            int v = (i == 0 ? rnd.next(1, 100000) : rnd.next(1, 50));
            bottles.push_back({w, v});
        }
    }

    shuffle(bottles.begin(), bottles.end());

    long long totalVolume = 0;
    for (auto [w, v] : bottles) totalVolume += w;

    long long m;
    int choice = rnd.next(0, 4);
    if (choice == 0) {
        m = 1;
    } else if (choice == 1) {
        m = totalVolume;
    } else if (choice == 2 && totalVolume > 1) {
        m = rnd.next(2LL, totalVolume);
    } else {
        long long prefix = 0;
        int take = rnd.next(0, (int)bottles.size() - 1);
        for (int i = 0; i < take; ++i) prefix += bottles[i].first;
        m = min(totalVolume, prefix + rnd.next(1, bottles[take].first));
    }

    println((int)bottles.size(), m);
    for (auto [w, v] : bottles) {
        println(w, v);
    }

    return 0;
}
