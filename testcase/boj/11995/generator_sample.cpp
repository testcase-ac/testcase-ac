#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<long long> randomDistinct(int count, long long limit, int mode) {
    set<long long> chosen;

    while ((int)chosen.size() < count) {
        long long x;
        if (mode == 0) {
            x = rnd.next(1LL, limit - 1);
        } else if (mode == 1) {
            long long span = min(limit - 1, (long long)max(3, count * 3));
            x = rnd.next(1LL, span);
        } else if (mode == 2) {
            long long span = min(limit - 1, (long long)max(3, count * 4));
            x = limit - rnd.next(1LL, span);
        } else {
            long long step = max(1LL, limit / (count + 1));
            int k = (int)chosen.size() + 1;
            long long jitter = rnd.next(0LL, min(step - 1, 5LL));
            x = min(limit - 1, max(1LL, step * k + jitter));
        }
        chosen.insert(x);
    }

    vector<long long> values(chosen.begin(), chosen.end());
    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n, m;
    long long a, b;

    if (mode == 0) {
        n = rnd.next(0, 1);
        m = rnd.next(0, 1);
        a = rnd.next((long long)n + 1, 10LL);
        b = rnd.next((long long)m + 1, 10LL);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = 0;
        a = rnd.next((long long)n + 1, 40LL);
        b = rnd.next(1LL, 40LL);
    } else if (mode == 2) {
        n = 0;
        m = rnd.next(1, 8);
        a = rnd.next(1LL, 40LL);
        b = rnd.next((long long)m + 1, 40LL);
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        a = rnd.next((long long)n + 1, 50LL);
        b = rnd.next((long long)m + 1, 50LL);
    } else if (mode == 4) {
        n = rnd.next(4, 20);
        m = rnd.next(4, 20);
        a = rnd.next(900000000LL, 1000000000LL);
        b = rnd.next(900000000LL, 1000000000LL);
    } else if (mode == 5) {
        n = rnd.next(10, 35);
        m = rnd.next(10, 35);
        a = rnd.next((long long)n + 1, 150LL);
        b = rnd.next((long long)m + 1, 150LL);
    } else {
        n = rnd.next(1, 25);
        m = rnd.next(1, 25);
        a = rnd.next(1000LL, 1000000000LL);
        b = rnd.next(1000LL, 1000000000LL);
    }

    int xMode = rnd.next(0, 3);
    int yMode = rnd.next(0, 3);
    vector<long long> vertical = randomDistinct(n, a, xMode);
    vector<long long> horizontal = randomDistinct(m, b, yMode);

    println(a, b, n, m);
    for (long long x : vertical) {
        println(x);
    }
    for (long long y : horizontal) {
        println(y);
    }

    return 0;
}
