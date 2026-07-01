#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    string s;

    if (mode == 0) {
        n = 2 * rnd.next(1, 20);
        s = string(n / 2, '+') + string(n / 2, '-');
        shuffle(s.begin(), s.end());
    } else if (mode == 1) {
        s.assign(n, rnd.next(0, 1) == 0 ? '+' : '-');
    } else if (mode == 2) {
        int plus = rnd.next(1, 8);
        int minus = rnd.next(1, 8);
        while (plus == minus) {
            minus = rnd.next(1, 8);
        }
        int scale = rnd.next(1, 4);
        n = (plus + minus) * scale;
        s = string(plus * scale, '+') + string(minus * scale, '-');
        shuffle(s.begin(), s.end());
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        s.reserve(n);
        for (int i = 0; i < n; ++i) {
            s += rnd.next(0, 3) == 0 ? '-' : '+';
        }
    } else {
        n = rnd.next(20, 80);
        s.reserve(n);
        for (int i = 0; i < n; ++i) {
            s += rnd.next(0, 1) == 0 ? '+' : '-';
        }
    }

    int plusCount = count(s.begin(), s.end(), '+');
    int minusCount = n - plusCount;
    int q = rnd.next(8, 28);
    vector<pair<long long, long long>> queries;

    auto addQuery = [&](long long a, long long b) {
        a = max(1LL, min(1000000000LL, a));
        b = max(1LL, min(1000000000LL, b));
        queries.push_back({a, b});
    };

    addQuery(1, 1);
    addQuery(1000000000LL, 1000000000LL);
    addQuery(1, 1000000000LL);
    addQuery(1000000000LL, 1);

    if (plusCount > 0 && minusCount > 0 && plusCount != minusCount) {
        long long g = __gcd(plusCount, minusCount);
        addQuery(plusCount / g, minusCount / g);
        addQuery(minusCount / g, plusCount / g);
        long long scale = rnd.next(1, 1000000);
        addQuery(scale * (plusCount / g), scale * (minusCount / g));
    }

    while ((int)queries.size() < q) {
        int kind = rnd.next(0, 4);
        if (kind == 0) {
            long long x = rnd.next(1, 30);
            addQuery(x, x);
        } else if (kind == 1) {
            addQuery(rnd.next(1, 30), rnd.next(1, 30));
        } else if (kind == 2) {
            addQuery(rnd.next(999999950LL, 1000000000LL),
                     rnd.next(1, 50));
        } else if (kind == 3) {
            addQuery(rnd.next(1, 50),
                     rnd.next(999999950LL, 1000000000LL));
        } else {
            long long base = rnd.next(1, 1000);
            addQuery(base, base + rnd.next(1, 1000));
        }
    }

    shuffle(queries.begin(), queries.end());

    println(n);
    println(s);
    println(q);
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
