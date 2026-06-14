#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Interval = pair<long long, long long>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Interval> programs;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        long long t = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 8);
            programs.push_back({t, t + len});
            t += len + rnd.next(0, 3);
        }
    } else if (mode == 1) {
        int n = rnd.next(6, 24);
        long long base = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) {
            long long start = base + rnd.next(0, 12);
            long long end = start + rnd.next(1, 25);
            programs.push_back({start, end});
        }
    } else if (mode == 2) {
        int n = rnd.next(8, 30);
        long long t = rnd.next(0, 15);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 6);
            programs.push_back({t, t + len});
            if (i % 3 == 2) {
                t += len;
            } else {
                t += rnd.next(0LL, len - 1);
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 14);
        programs.push_back({0, 1000000000LL});
        programs.push_back({0, rnd.next(1, 1000)});
        programs.push_back({1000000000LL - rnd.next(1, 1000), 1000000000LL});
        while ((int)programs.size() < n) {
            long long start = rnd.next(0LL, 999999990LL);
            long long end = start + rnd.next(1LL, min(1000000000LL - start, 10000LL));
            programs.push_back({start, end});
        }
    } else if (mode == 4) {
        int clusters = rnd.next(2, 5);
        for (int c = 0; c < clusters; ++c) {
            long long base = c * rnd.next(15, 35) + rnd.next(0, 5);
            int cnt = rnd.next(2, 8);
            for (int i = 0; i < cnt; ++i) {
                long long start = base + rnd.next(0, 10);
                programs.push_back({start, start + rnd.next(1, 15)});
            }
        }
    } else {
        int n = rnd.next(120, 150);
        long long t = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 20);
            programs.push_back({t, t + len});
            t += rnd.next(0, 3);
        }
    }

    shuffle(programs.begin(), programs.end());

    println((int)programs.size());
    for (const auto& p : programs) {
        println(p.first, p.second);
    }

    return 0;
}
