#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long maxReachableSum(int n) {
    return 1LL * n * (n - 1) / 2;
}

long long boundedSum(long long value) {
    return max(-50000000LL, min(50000000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long s;

    if (mode == 0) {
        n = rnd.next(1, 20);
        s = rnd.next(-50, 50);
    } else if (mode == 1) {
        n = rnd.next(1, 80);
        long long reach = maxReachableSum(n);
        long long magnitude = rnd.next(0LL, reach);
        if ((magnitude & 1) != (reach & 1)) --magnitude;
        if (magnitude < 0) magnitude = 0;
        s = rnd.next(0, 1) ? magnitude : -magnitude;
    } else if (mode == 2) {
        n = rnd.next(1, 80);
        long long reach = maxReachableSum(n);
        long long magnitude = rnd.next(0LL, reach);
        if ((magnitude & 1) == (reach & 1)) {
            if (magnitude < reach) ++magnitude;
            else --magnitude;
        }
        s = rnd.next(0, 1) ? magnitude : -magnitude;
    } else if (mode == 3) {
        n = rnd.any(vector<int>{1, 2, 3, 4, 10000});
        long long reach = maxReachableSum(n);
        vector<long long> candidates = {
            0,
            1,
            -1,
            boundedSum(reach),
            boundedSum(-reach),
            50000000,
            -50000000,
        };
        s = rnd.any(candidates);
    } else if (mode == 4) {
        n = rnd.next(80, 500);
        long long reach = maxReachableSum(n);
        s = rnd.next(-reach, reach);
    } else {
        n = rnd.next(1, 10000);
        s = rnd.next(-50000000, 50000000);
    }

    println(n);
    println(s);

    return 0;
}
