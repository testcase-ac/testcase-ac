#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000000000LL;

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<long long> a;
    a.reserve(n);

    if (mode == 0) {
        long long mass = 2;
        while ((int)a.size() < n) {
            long long upper = min(mass - 1, LIMIT);
            long long value = rnd.next(1LL, upper);
            a.push_back(value);
            if (mass <= LIMIT - value) {
                mass += value;
            }
        }
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        int smallCount = rnd.next(0, n - 1);
        long long mass = 2;
        for (int i = 0; i < smallCount; ++i) {
            long long value = rnd.next(1LL, max(1LL, mass - 1));
            a.push_back(value);
            if (mass <= LIMIT - value) {
                mass += value;
            }
        }
        long long blocker = rnd.next(mass, min(LIMIT, mass + rnd.next(0LL, 20LL)));
        while ((int)a.size() < n) {
            a.push_back(rnd.next(blocker, min(LIMIT, blocker + 50)));
        }
    } else if (mode == 2) {
        n = rnd.next(1, 25);
        long long base = rnd.next(1LL, 8LL);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(base + rnd.next(0LL, 3LL));
            } else {
                a.push_back(base);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        long long x = 1;
        for (int i = 0; i < n; ++i) {
            a.push_back(x);
            if (x <= LIMIT / 2 && rnd.next(0, 2) != 0) {
                x *= 2;
            } else {
                x = rnd.next(max(1LL, x - 2), min(LIMIT, x + 5));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            long long offset = rnd.next(0LL, 1000LL);
            a.push_back(LIMIT - offset);
        }
    } else {
        n = rnd.next(10, 40);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                a.push_back(rnd.next(1LL, 3LL));
            } else if (bucket == 1) {
                a.push_back(rnd.next(4LL, 50LL));
            } else if (bucket == 2) {
                a.push_back(rnd.next(51LL, 1000000LL));
            } else {
                a.push_back(rnd.next(999999999999999000LL, LIMIT));
            }
        }
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
