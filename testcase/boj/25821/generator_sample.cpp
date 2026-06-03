#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long makeOddPalindrome(int left, int middle) {
    string s = to_string(left);
    string r = s;
    reverse(r.begin(), r.end());
    s += char('0' + middle);
    s += r;
    return stoll(s);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000000LL;
    int mode = rnd.next(0, 7);
    long long l = 2;
    long long h = 2;

    if (mode == 0) {
        l = rnd.next(2LL, 200LL);
        h = rnd.next(l, min(LIM, l + rnd.next(0LL, 300LL)));
    } else if (mode == 1) {
        l = rnd.next(2LL, 100000LL);
        h = rnd.next(l, min(LIM, l + rnd.next(0LL, 5000LL)));
    } else if (mode == 2) {
        long long center = rnd.next(2LL, 1000000000000LL);
        long long radius = rnd.next(0LL, 20000LL);
        l = max(2LL, center - radius);
        h = min(LIM, center + radius);
    } else if (mode == 3) {
        int digits = rnd.next(1, 5);
        int lo = 1;
        for (int i = 1; i < digits; ++i) lo *= 10;
        int hi = lo * 10 - 1;
        long long p = makeOddPalindrome(rnd.next(lo, hi), rnd.next(0, 9));
        long long radius = rnd.next(0LL, 5000LL);
        l = max(2LL, p - radius);
        h = min(LIM, p + radius);
    } else if (mode == 4) {
        vector<long long> anchors = {
            2LL, 3LL, 5LL, 7LL, 11LL, 101LL, 131LL, 727LL,
            10301LL, 93139LL, 97879LL, 1000000000000LL
        };
        long long a = rnd.any(anchors);
        long long left = rnd.next(0LL, min(1000LL, max(0LL, a - 2)));
        long long right = rnd.next(0LL, min(1000LL, LIM - a));
        l = max(2LL, a - left);
        h = min(LIM, a + right);
    } else if (mode == 5) {
        l = rnd.next(999999000000LL, LIM);
        h = rnd.next(l, LIM);
    } else if (mode == 6) {
        long long start = rnd.next(2LL, 999999999999LL);
        l = start;
        h = start;
    } else {
        long long a = rnd.next(2LL, 999999999999LL);
        long long b = rnd.next(2LL, 1000000000000LL);
        l = min(a, b);
        h = max(a, b);
    }

    println(l, h);
    return 0;
}
