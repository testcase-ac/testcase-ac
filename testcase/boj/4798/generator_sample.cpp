#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

using Case = tuple<long long, long long, long long, long long>;

const long long LIMIT = 1000000000000LL;

void addCase(vector<Case>& cases, long long a, long long b, long long l, long long len) {
    long long u = l + len - 1;
    cases.emplace_back(a, b, l, u);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Case> cases;
    long long remainingWindow = 1000001;
    int targetCases = rnd.next(7, 14);

    for (int i = 0; i < targetCases && remainingWindow > 0; ++i) {
        int mode = rnd.next(0, 5);
        long long len = 1;
        long long l = 0;
        long long a = 1;
        long long b = 0;

        if (mode == 0) {
            len = rnd.next(1LL, min(80LL, remainingWindow));
            l = rnd.next(0LL, 60LL);
            a = rnd.next(1LL, 40LL);
            b = rnd.next(0LL, 80LL);
        } else if (mode == 1) {
            len = rnd.next(1LL, min(120LL, remainingWindow));
            l = rnd.next(0LL, 100LL);
            a = rnd.next(1LL, 80LL);
            b = rnd.next(0, 1) == 0 ? 0 : rnd.next(0LL, 3LL);
        } else if (mode == 2) {
            len = rnd.next(1LL, min(200LL, remainingWindow));
            l = rnd.next(0LL, 200LL);
            long long g = rnd.next(2LL, 25LL);
            a = g * rnd.next(1LL, 30LL);
            b = g * rnd.next(0LL, 30LL);
        } else if (mode == 3) {
            long long maxLen = min(remainingWindow, rnd.next(1000LL, 20000LL));
            len = rnd.next(1LL, maxLen);
            l = rnd.next(0LL, 5000LL);
            a = rnd.next(1LL, 1000LL);
            b = rnd.next(0LL, 100000LL);
        } else if (mode == 4) {
            len = rnd.next(1LL, min(60LL, remainingWindow));
            l = rnd.next(0LL, 1000000LL);
            long long u = l + len - 1;
            b = rnd.next(0LL, 1000000LL);
            long long maxA = max(1LL, (LIMIT - b) / max(1LL, u));
            a = rnd.next(max(1LL, maxA - 1000000LL), maxA);
        } else {
            len = rnd.next(1LL, min(100LL, remainingWindow));
            l = rnd.next(0LL, 1000LL);
            long long u = l + len - 1;
            a = rnd.next(1LL, 1000000LL);
            long long maxB = LIMIT - a * u;
            b = rnd.next(max(0LL, maxB - 1000000LL), maxB);
        }

        long long u = l + len - 1;
        while (static_cast<__int128>(a) * u + b > LIMIT) {
            if (a > 1) {
                a = (a + 1) / 2;
            } else {
                b /= 2;
            }
        }

        addCase(cases, a, b, l, len);
        remainingWindow -= len;
    }

    if (remainingWindow >= 100000) {
        long long len = rnd.next(50000LL, min(1000000LL, remainingWindow));
        long long a = rnd.next(1LL, 1000000LL);
        addCase(cases, a, rnd.next(0LL, 1000LL), 0, len);
    }

    for (const auto& [a, b, l, u] : cases) {
        println(a, b, l, u);
    }
    println(0);

    return 0;
}
