#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<long long> s(n, 1);
    long long slack = 0;

    if (mode == 0) {
        // Tight schedule: sum S_i equals K.
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(1, 8);
        }
    } else if (mode == 1) {
        // Sparse schedule with many possible empty slots.
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(1, 3);
        }
        slack = rnd.next(1, 60);
    } else if (mode == 2) {
        // All durations equal, often exposing duplicate-handling mistakes.
        long long value = rnd.next(1, 7);
        fill(s.begin(), s.end(), value);
        slack = rnd.next(0, 25);
    } else if (mode == 3) {
        // Mostly tiny tasks with one longer task.
        int longIndex = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            s[i] = (i == longIndex) ? rnd.next(10, 40) : rnd.next(1, 2);
        }
        slack = rnd.next(0, 40);
    } else if (mode == 4) {
        // Larger K while keeping the line hand-readable.
        n = rnd.next(1, 8);
        s.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(1, 20);
        }
        slack = rnd.next(1000000LL, 1000000000LL - accumulate(s.begin(), s.end(), 0LL));
    } else {
        // Random composition of a modest total time.
        long long total = rnd.next((long long)n, (long long)n + 80);
        for (int i = 0; i < n; ++i) {
            long long add = rnd.next(0LL, total - n);
            s[i] += add;
            total -= add;
        }
        s.back() += total - n;
        slack = rnd.next(0, 30);
    }

    shuffle(s.begin(), s.end());
    long long sum = accumulate(s.begin(), s.end(), 0LL);
    long long k = sum + slack;

    println(n, k);
    println(s);

    return 0;
}
