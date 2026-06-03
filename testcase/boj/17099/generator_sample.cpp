#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

using Contest = tuple<long long, long long, int>;

int prize() {
    return rnd.next(1, 1000);
}

void addContest(vector<Contest>& contests, long long s, long long e) {
    contests.emplace_back(s, e, prize());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Contest> contests;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 18);
        long long t = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 8);
            addContest(contests, t, t + len);
            t += len + rnd.next(0, 2);
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 22);
        long long base = rnd.next(0, 50);
        int width = rnd.next(8, 28);
        for (int i = 0; i < n; ++i) {
            long long s = base + rnd.next(0, width - 1);
            long long e = s + rnd.next(1, width);
            addContest(contests, s, e);
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 16);
        long long left = rnd.next(0, 30);
        long long right = left + rnd.next(n + 1, n + 30);
        for (int i = 0; i < n; ++i) {
            long long s = left + rnd.next(0, i);
            long long e = right - rnd.next(0, i);
            if (s >= e) e = s + 1;
            addContest(contests, s, e);
        }
    } else if (mode == 3) {
        int blocks = rnd.next(2, 5);
        long long t = rnd.next(0, 10);
        for (int b = 0; b < blocks; ++b) {
            int count = rnd.next(2, 7);
            int span = rnd.next(5, 15);
            for (int i = 0; i < count; ++i) {
                long long s = t + rnd.next(0, span - 1);
                long long e = s + rnd.next(1, span);
                addContest(contests, s, e);
            }
            t += span + rnd.next(1, 5);
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 20);
        long long base = 1000000000LL - rnd.next(100, 10000);
        for (int i = 0; i < n; ++i) {
            long long s = base + rnd.next(0, 80);
            long long e = s + rnd.next(1, 100);
            if (e > 1000000000LL) e = 1000000000LL;
            if (s >= e) s = e - 1;
            addContest(contests, s, e);
        }
    } else {
        int n = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            long long s = rnd.next(0, 120);
            long long e = s + rnd.next(1, 30);
            addContest(contests, s, e);
        }
    }

    shuffle(contests.begin(), contests.end());

    println(static_cast<int>(contests.size()));
    for (auto [s, e, c] : contests) {
        println(s, e, c);
    }

    return 0;
}
