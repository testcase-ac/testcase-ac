#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    long long x;
    long long y;
    long long a;
    long long b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 25);
    vector<Case> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        long long x, y, a, b;

        if (mode == 0) {
            a = rnd.next(1LL, 20LL);
            b = rnd.next(1LL, 20LL);
            long long seconds = rnd.next(1LL, 20LL);
            long long distance = (a + b) * seconds;
            x = rnd.next(0LL, 1000LL);
            y = x + distance;
        } else if (mode == 1) {
            a = rnd.next(1LL, 30LL);
            b = rnd.next(1LL, 30LL);
            long long distance = rnd.next(1LL, 400LL);
            if (distance % (a + b) == 0) ++distance;
            x = rnd.next(0LL, 1000LL);
            y = x + distance;
        } else if (mode == 2) {
            x = rnd.next(0LL, 50LL);
            y = x + rnd.next(1LL, 5LL);
            a = rnd.next(1LL, 10LL);
            b = rnd.next(1LL, 10LL);
        } else if (mode == 3) {
            y = rnd.next(999999900LL, 1000000000LL);
            x = rnd.next(max(0LL, y - 200LL), y - 1);
            a = rnd.next(1LL, 1000000000LL);
            b = rnd.next(1LL, 1000000000LL);
        } else if (mode == 4) {
            a = rnd.next(900000000LL, 1000000000LL);
            b = rnd.next(900000000LL, 1000000000LL);
            x = rnd.next(0LL, 100LL);
            y = x + rnd.next(1LL, 1000LL);
        } else {
            long long sum = rnd.next(2LL, 100LL);
            a = rnd.next(1LL, sum - 1);
            b = sum - a;
            long long distance = sum * rnd.next(1LL, 10LL) + rnd.next(0LL, sum - 1);
            x = rnd.next(0LL, 1000000000LL - distance);
            y = x + distance;
        }

        cases.push_back({x, y, a, b});
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const Case& tc : cases) {
        println(tc.x, tc.y, tc.a, tc.b);
    }

    return 0;
}
