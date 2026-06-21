#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);

    long long n;
    int m;
    int k;

    if (mode == 0) {
        n = rnd.next(2, 18);
        m = rnd.next(2, (int)min<long long>(n, 8));
        k = rnd.next(m, (int)min<long long>(n, 12));
    } else if (mode == 1) {
        n = rnd.next(20, 80);
        m = rnd.next(2, 10);
        k = rnd.next(m, min(20, (int)n));
    } else if (mode == 2) {
        n = rnd.next(100000000LL, 1000000000LL);
        m = rnd.next(2, 9);
        k = rnd.next(m, 60);
    } else if (mode == 3) {
        n = rnd.next(2, 300);
        m = rnd.next(2, (int)min<long long>(n, 40));
        k = rnd.next(m, (int)min<long long>(n, 80));
    } else if (mode == 4) {
        n = rnd.next(2500, 6000);
        m = rnd.next(2000, (int)min<long long>(n, 3000));
        k = rnd.next(m, (int)min<long long>(n, 3000));
    } else {
        n = 1000000000LL;
        m = rnd.next(2, 12);
        k = rnd.next(m, 3000);
    }

    long long b = rnd.next(1LL, 1000000LL);
    long long c = b + rnd.next(1LL, 1000000LL);
    long long a = c + rnd.next(1LL, 1000000LL);
    if (mode == 5 && rnd.next(0, 1)) {
        b = 1;
        c = 2;
        a = rnd.next(900000000LL, 1000000000LL);
    }

    long long span = n - 1;
    long long fastest = min(1000000000000000000LL, b * min(span, 1000000000LL));
    long long slowish = min(1000000000000000000LL, a * min(span, 1000000000LL));
    long long t;
    int timeMode = rnd.next(0, 4);
    if (timeMode == 0) {
        t = rnd.next(1LL, min(1000000000000000000LL, max(1LL, c * min(span, 1000000LL))));
    } else if (timeMode == 1) {
        t = max(1LL, fastest - rnd.next(0LL, min(fastest - 1, 1000000LL)));
    } else if (timeMode == 2) {
        t = min(1000000000000000000LL, fastest + rnd.next(0LL, 1000000LL));
    } else if (timeMode == 3) {
        t = min(1000000000000000000LL, slowish);
    } else {
        t = rnd.next(1LL, 1000000000000000000LL);
    }

    vector<long long> stops;
    stops.push_back(1);
    stops.push_back(n);

    if (mode == 4) {
        while ((int)stops.size() < m) {
            stops.push_back(rnd.next(2LL, n - 1));
            sort(stops.begin(), stops.end());
            stops.erase(unique(stops.begin(), stops.end()), stops.end());
        }
    } else {
        long long cursor = 1;
        int inner = m - 2;
        for (int i = 0; i < inner; ++i) {
            long long remainingSlots = inner - i;
            long long remainingGap = n - cursor - remainingSlots;
            long long step;
            if (mode == 1 || mode == 2 || mode == 5) {
                step = rnd.next(1LL, max(1LL, remainingGap / remainingSlots * 2 + 1));
            } else {
                step = rnd.next(1LL, max(1LL, min(remainingGap, 10LL)));
            }
            step = min(step, remainingGap);
            cursor += step;
            stops.push_back(cursor);
        }
        sort(stops.begin(), stops.end());
    }

    println(n, m, k);
    println(a, b, c);
    println(t);
    for (long long s : stops) {
        println(s);
    }

    return 0;
}
