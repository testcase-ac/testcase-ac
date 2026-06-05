#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int q = rnd.next(1, 12);
    long long h = rnd.next(1, 200);
    vector<long long> initial;
    vector<long long> added;

    auto addSmall = [&]() {
        return rnd.next(1LL, max(1LL, min(30LL, h)));
    };

    if (mode == 0) {
        h = rnd.next(20, 120);
        for (int i = 0; i < n; ++i) initial.push_back(rnd.next(1, 9));
        for (int i = 0; i < q; ++i) added.push_back(rnd.next(1, 9));
    } else if (mode == 1) {
        h = rnd.next(40, 180);
        for (int i = 0; i < n + q; ++i) {
            long long value = rnd.next(1, 25);
            if (i % 4 == 0) value = rnd.next(1, 5);
            if (i % 5 == 0) value = rnd.next(20, 60);
            (i < n ? initial : added).push_back(value);
        }
    } else if (mode == 2) {
        h = rnd.next(50, 200);
        long long remaining = h;
        vector<long long> cards;
        while (remaining > 0 && (int)cards.size() < n + q) {
            long long value = rnd.next(1LL, min(remaining, 35LL));
            cards.push_back(value);
            remaining -= value;
        }
        while ((int)cards.size() < n + q) cards.push_back(addSmall());
        shuffle(cards.begin(), cards.end());
        for (int i = 0; i < n; ++i) initial.push_back(cards[i]);
        for (int i = n; i < n + q; ++i) added.push_back(cards[i]);
    } else if (mode == 3) {
        h = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            initial.push_back(rnd.next(1, 1000000000));
        }
        for (int i = 0; i < q; ++i) {
            added.push_back(rnd.next(1, 1000000000));
        }
    } else if (mode == 4) {
        h = rnd.next(30, 150);
        long long big = rnd.next(h, min(1000000000LL, h + 100));
        for (int i = 0; i < n; ++i) initial.push_back(i == 0 ? big : addSmall());
        for (int i = 0; i < q; ++i) added.push_back(i % 3 == 0 ? big : addSmall());
        shuffle(initial.begin(), initial.end());
    } else {
        h = rnd.next(2, 200);
        long long total = 0;
        for (int i = 0; i < n + q; ++i) {
            long long value = rnd.next(1, 20);
            if (i == n + q - 1 && total < h) value = min(1000000000LL, h - total);
            total += value;
            (i < n ? initial : added).push_back(value);
        }
    }

    println(h);
    println(n, q);
    println(initial);
    for (long long x : added) {
        println(x);
    }

    return 0;
}
