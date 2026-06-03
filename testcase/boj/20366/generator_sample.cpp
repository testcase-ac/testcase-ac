#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(4, 18);
    vector<long long> h;

    if (mode == 0) {
        long long base = rnd.next(1LL, 100LL);
        int span = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            h.push_back(base + rnd.next(0, span));
        }
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        long long target = rnd.next(20LL, 200LL);
        for (int i = 0; i < n / 2; ++i) {
            long long a = rnd.next(1LL, target - 1);
            h.push_back(a);
            h.push_back(target - a);
        }
        if ((int)h.size() < n) {
            h.push_back(rnd.next(1LL, 200LL));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 10);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                h.push_back(rnd.next(1LL, 8LL));
            } else {
                h.push_back(1000000000LL - rnd.next(0LL, 8LL));
            }
        }
    } else if (mode == 3) {
        long long start = rnd.next(1LL, 50LL);
        long long step = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            h.push_back(start + step * i + rnd.next(0LL, 2LL));
        }
    } else if (mode == 4) {
        n = rnd.next(4, 30);
        long long center = rnd.next(1000LL, 1000000LL);
        for (int i = 0; i < n; ++i) {
            h.push_back(center + rnd.next(-50LL, 50LL));
        }
    } else {
        n = rnd.next(4, 25);
        for (int i = 0; i < n; ++i) {
            h.push_back(rnd.next(1LL, 1000000000LL));
        }
    }

    for (long long& x : h) {
        x = max(1LL, min(1000000000LL, x));
    }

    if (rnd.next(0, 2) == 0) {
        sort(h.begin(), h.end());
    } else {
        shuffle(h.begin(), h.end());
    }

    println((int)h.size());
    println(h);

    return 0;
}
