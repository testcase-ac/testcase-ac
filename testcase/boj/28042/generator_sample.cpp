#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long limitFor(int n) {
    return 1LL << n;
}

long long randomValue(long long limit) {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return rnd.any(vector<long long>{1, 2, max(1LL, limit / 2), limit});
    }
    if (mode == 1) {
        long long tail = rnd.next(0LL, min(1000LL, limit - 1));
        return limit - tail;
    }
    if (mode == 2) {
        long long head = rnd.next(0LL, min(1000LL, limit - 1));
        return 1 + head;
    }
    if (mode == 3) {
        int bit = rnd.next(0, 60);
        long long value = 1LL << bit;
        return min(value, limit);
    }
    return rnd.next(1LL, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 20);
    } else if (mode == 3) {
        n = rnd.next(50, 60);
    } else if (mode == 4) {
        n = rnd.any(vector<int>{30, 40, 50, 59, 60});
    } else {
        n = rnd.next(1, 60);
    }

    long long limit = limitFor(n);
    long long p = randomValue(limit);
    long long h = randomValue(limit);

    if (mode == 5) {
        p = limit + 1 - p;
    } else if (mode == 6) {
        h = limit + 1 - p;
    }

    println(n, p, h);
    return 0;
}
