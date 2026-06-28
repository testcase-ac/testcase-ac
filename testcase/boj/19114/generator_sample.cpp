#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long grundy(long long x) {
    if (x % 8 == 0) return x - 1;
    if (x % 8 == 7) return x + 1;
    return x;
}

long long valueWithGrundy(long long g) {
    if (g > 1 && g % 8 == 0) return g - 1;
    if (g % 8 == 7) return g + 1;
    return g;
}

long long randomNearBoundary() {
    int block = rnd.next(0, 12);
    int offset = rnd.any(vector<int>{-2, -1, 0, 1, 6, 7, 8, 9});
    long long x = 8LL * block + offset;
    if (x < 1) x = rnd.next(1, 16);
    return min(x, 1000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<long long> s;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(1, 20));
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) s.push_back(randomNearBoundary());
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        long long x = 0;
        for (int i = 0; i + 1 < n; ++i) {
            long long v = rnd.next(1, 80);
            s.push_back(v);
            x ^= grundy(v);
        }
        long long last = valueWithGrundy(x);
        if (last < 1 || last > 1000000000LL) last = 1;
        s.push_back(last);
    } else if (mode == 3) {
        n = rnd.next(2, 24);
        long long base = rnd.any(vector<long long>{1, 2, 4, 7, 8, 15, 16, 31, 32});
        for (int i = 0; i < n; ++i) s.push_back(base + rnd.next(0, 3));
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            long long block = rnd.next(0, 1000000);
            long long offset = rnd.any(vector<long long>{0, 1, 6, 7});
            s.push_back(min(1000000000LL, 8LL * block + offset + 1));
        }
    } else {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(1, 1000000000));
    }

    shuffle(s.begin(), s.end());
    println((int)s.size());
    println(s);

    return 0;
}
