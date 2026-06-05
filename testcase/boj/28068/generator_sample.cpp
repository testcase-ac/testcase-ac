#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 18);
    vector<pair<long long, long long>> books;

    if (mode == 0) {
        n = 1;
        books.push_back({rnd.next(0, 1), rnd.next(0, 1000000000)});
    } else if (mode == 1) {
        long long joy = 0;
        for (int i = 0; i < n; ++i) {
            long long cost = rnd.next(0LL, min(joy, 30LL));
            long long gain = cost + rnd.next(0, 20);
            books.push_back({cost, gain});
            joy = joy - cost + gain;
        }
    } else if (mode == 2) {
        books.push_back({0, rnd.next(0, 5)});
        for (int i = 1; i < n; ++i) {
            long long cost = rnd.next(1, 40);
            long long gain = rnd.next(0LL, cost - 1);
            books.push_back({cost, gain});
        }
    } else if (mode == 3) {
        int starters = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < starters; ++i) {
            books.push_back({0, rnd.next(0, 60)});
        }
        for (int i = starters; i < n; ++i) {
            long long cost = rnd.next(0, 80);
            long long gain = rnd.next(0, 80);
            books.push_back({cost, gain});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        long long joy = 0;
        for (int i = 0; i + 1 < n; ++i) {
            long long cost = rnd.next(0LL, min(joy, 100LL));
            long long gain = rnd.next(cost, cost + 100);
            books.push_back({cost, gain});
            joy = joy - cost + gain;
        }
        books.push_back({joy + rnd.next(1, 100), rnd.next(0, 100)});
    } else if (mode == 5) {
        n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) {
            long long value = rnd.next(0, 100);
            books.push_back({value, value});
        }
    } else if (mode == 6) {
        n = rnd.next(2, 10);
        books.push_back({0, 1000000000LL});
        for (int i = 1; i < n; ++i) {
            long long cost = rnd.next(0LL, 1000000000LL);
            long long gain = rnd.next(0LL, 1000000000LL);
            books.push_back({cost, gain});
        }
    } else {
        n = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            long long cost = rnd.wnext(1000000001LL, -3);
            long long gain = rnd.wnext(1000000001LL, -3);
            books.push_back({cost, gain});
        }
    }

    shuffle(books.begin(), books.end());

    println((int)books.size());
    for (auto [cost, gain] : books) {
        println(cost, gain);
    }

    return 0;
}
