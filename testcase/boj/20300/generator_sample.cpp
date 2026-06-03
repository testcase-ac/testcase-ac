#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long randomValue(long long high) {
    return rnd.next(0LL, high);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<long long> t;

    if (mode == 0) {
        n = 1;
        t.push_back(rnd.any(vector<long long>{0LL, 1LL, randomValue(100), LIMIT}));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        if (n % 2 == 1) ++n;
        long long high = rnd.any(vector<long long>{10LL, 1000LL, LIMIT});
        for (int i = 0; i < n; ++i) t.push_back(randomValue(high));
    } else if (mode == 2) {
        n = rnd.next(3, 13);
        if (n % 2 == 0) ++n;
        long long high = rnd.any(vector<long long>{10LL, 1000LL, LIMIT});
        for (int i = 0; i < n - 1; ++i) t.push_back(randomValue(high / 2));
        t.push_back(rnd.next(max(0LL, high - 1000), high));
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        for (int i = 0; i < n; ++i) {
            t.push_back(rnd.any(vector<long long>{0LL, 0LL, 1LL, LIMIT, LIMIT - rnd.next(0LL, 1000LL)}));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 18);
        long long base = rnd.next(0LL, LIMIT - 1000);
        for (int i = 0; i < n; ++i) t.push_back(base + rnd.next(0LL, 1000LL));
    } else if (mode == 5) {
        n = rnd.next(4, 20);
        long long target = rnd.next(5LL, 1000000LL);
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(0LL, target);
            t.push_back(i % 2 == 0 ? x : target - x);
        }
    } else {
        n = rnd.next(20, 80);
        long long high = rnd.any(vector<long long>{100LL, 1000000LL, LIMIT});
        for (int i = 0; i < n; ++i) t.push_back(randomValue(high));
    }

    shuffle(t.begin(), t.end());
    println(n);
    println(t);
    return 0;
}
