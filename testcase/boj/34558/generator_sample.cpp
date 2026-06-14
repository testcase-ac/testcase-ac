#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

static const int MAXV = 1000000;

static vector<int> buildPrimes() {
    vector<int> primes;
    vector<bool> composite(MAXV + 1, false);
    for (int i = 2; i <= MAXV; ++i) {
        if (!composite[i]) {
            primes.push_back(i);
            if ((long long)i * i <= MAXV) {
                for (long long j = (long long)i * i; j <= MAXV; j += i) {
                    composite[(int)j] = true;
                }
            }
        }
    }
    return primes;
}

static pair<int, int> clampInterval(int a, int b) {
    a = max(a, 2);
    b = min(b, MAXV);
    if (a > b) swap(a, b);
    a = max(a, 2);
    b = min(b, MAXV);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = buildPrimes();
    vector<pair<int, int>> intervals;
    int mode = rnd.next(0, 5);

    auto addInterval = [&](int a, int b) {
        intervals.push_back(clampInterval(a, b));
    };

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(2, 35);
            int b = rnd.next(a, min(MAXV, a + rnd.next(0, 20)));
            addInterval(a, b);
        }
    } else if (mode == 1) {
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(2, MAXV);
            int len = rnd.next(0, 2);
            addInterval(x, min(MAXV, x + len));
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 18);
        for (int i = 0; i < n; ++i) {
            int p = primes[rnd.next(0, (int)primes.size() - 1)];
            int leftPad = rnd.next(0, 8);
            int rightPad = rnd.next(0, 8);
            addInterval(p - leftPad, p + rightPad);
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 18);
        for (int i = 0; i < n; ++i) {
            int center = rnd.next(2, MAXV);
            int radius = rnd.next(0, 80);
            addInterval(center - radius, center + radius);
        }
    } else if (mode == 4) {
        int n = rnd.next(4, 16);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                int a = rnd.next(2, 200);
                addInterval(a, rnd.next(a, 200));
            } else {
                int b = rnd.next(MAXV - 200, MAXV);
                addInterval(rnd.next(MAXV - 200, b), b);
            }
        }
    } else {
        int n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(2, MAXV);
            int width = rnd.next(0, 1000);
            addInterval(a, min(MAXV, a + width));
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println((int)intervals.size());
    for (auto [a, b] : intervals) {
        println(a, b);
    }

    return 0;
}
