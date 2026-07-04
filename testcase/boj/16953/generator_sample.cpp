#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static long long appendOne(long long x) {
    return x * 10 + 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000LL;
    int mode = rnd.next(0, 5);
    long long A = 1;
    long long B = 2;

    if (mode <= 2) {
        vector<long long> path;
        A = rnd.next(1LL, 1000000LL);
        long long cur = A;
        int steps = rnd.next(1, 12);
        for (int i = 0; i < steps; ++i) {
            vector<long long> nexts;
            if (cur * 2 <= LIMIT) nexts.push_back(cur * 2);
            if (appendOne(cur) <= LIMIT) nexts.push_back(appendOne(cur));
            if (nexts.empty()) break;
            cur = rnd.any(nexts);
            path.push_back(cur);
        }
        if (path.empty()) {
            B = A * 2;
        } else {
            B = rnd.any(path);
        }
    } else if (mode == 3) {
        A = rnd.next(1LL, 100000LL);
        B = rnd.next(A + 1, min(LIMIT, A + rnd.next(1LL, 1000000LL)));
        if (B == A * 2 || B == appendOne(A)) {
            B = min(LIMIT, B + 1);
            if (B <= A) B = A + 1;
        }
    } else if (mode == 4) {
        B = rnd.next(900000000LL, LIMIT);
        A = rnd.next(1LL, B - 1);
    } else {
        A = rnd.next(1LL, 20LL);
        long long cur = A;
        while (true) {
            vector<long long> nexts;
            if (cur * 2 <= LIMIT) nexts.push_back(cur * 2);
            if (appendOne(cur) <= LIMIT) nexts.push_back(appendOne(cur));
            if (nexts.empty() || rnd.next(0, 3) == 0) break;
            cur = rnd.any(nexts);
        }
        if (cur == A) cur = A * 2;
        B = cur;
    }

    ensure(A >= 1 && A < B && B <= LIMIT);
    println(A, B);
    return 0;
}
