#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;
    int mode = rnd.next(0, 5);
    vector<pair<long long, long long>> contests;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            long long p = rnd.next(1, 2000);
            long long slack = rnd.next(0, 3000);
            contests.push_back({max(1LL, min(LIM, sum + slack)), p});
            sum += p;
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 12);
        int fail = rnd.next(1, n - 2);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            long long p = rnd.next(50, 2000);
            long long x = sum + rnd.next(0, 500);
            if (i == fail) x = max(1LL, sum - rnd.next(1LL, min(sum, 1000LL)));
            contests.push_back({max(1LL, min(LIM, x)), p});
            if (i != fail) sum += p;
        }
    } else if (mode == 2) {
        int n = rnd.next(5, 12);
        int big = rnd.next(0, n - 3);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            long long p = (i == big ? rnd.next(5000, 20000) : rnd.next(100, 2500));
            long long x = sum + rnd.next(0, 700);
            contests.push_back({max(1LL, min(LIM, x)), p});
            if (i != big) sum += p;
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 12);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            long long p = rnd.next(1000, 5000);
            long long x = (i < 2 ? sum + rnd.next(0, 100) : max(1LL, sum - rnd.next(1LL, min(sum, 500LL))));
            contests.push_back({max(1LL, min(LIM, x)), p});
            sum += p;
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 10);
        long long p = rnd.next(700000000LL, LIM);
        for (int i = 0; i < n; ++i) {
            long long x = (i == 0 ? LIM : rnd.next(1LL, LIM));
            contests.push_back({x, p});
        }
    } else {
        int n = rnd.next(2, 30);
        long long lowX = rnd.next(1, 100);
        long long highX = rnd.next(1000000LL, LIM);
        for (int i = 0; i < n; ++i) {
            long long x = (rnd.next(0, 3) == 0 ? lowX : rnd.next(1LL, highX));
            long long p = rnd.next(1, 1000000);
            contests.push_back({x, p});
        }
    }

    println((int)contests.size());
    for (auto [x, p] : contests) {
        println(x, p);
    }

    return 0;
}
