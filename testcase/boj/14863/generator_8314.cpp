#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N: sometimes small [3,5], sometimes medium [6,12]
    int N = (rnd.next(0, 1) == 0 ? rnd.next(3, 5) : rnd.next(6, 12));

    // Time range hyper-parameter
    bool time_large = rnd.next(0.0, 1.0) < 0.3;
    int lo_t = time_large ? 5000 : 1;
    int hi_t = time_large ? 10000 : 500;

    // Money range hyper-parameter
    bool money_large = rnd.next(0.0, 1.0) < 0.3;
    int lo_m = money_large ? 50000 : 1;
    int hi_m = money_large ? 1000000 : 1000;

    int mid_t = (lo_t + hi_t) / 2;
    int mid_m = (lo_m + hi_m) / 2;

    vector<int> w_t(N), b_t(N), w_m(N), b_m(N);
    for (int i = 0; i < N; i++) {
        int type = rnd.next(0, 4);
        if (type == 0) {
            // walking slower but more money (trade-off)
            b_t[i] = rnd.next(lo_t, mid_t);
            w_t[i] = rnd.next(mid_t + 1, hi_t);
            b_m[i] = rnd.next(lo_m, mid_m);
            w_m[i] = rnd.next(mid_m + 1, hi_m);
        } else if (type == 1) {
            // walking faster but less money (trade-off)
            w_t[i] = rnd.next(lo_t, mid_t);
            b_t[i] = rnd.next(mid_t + 1, hi_t);
            w_m[i] = rnd.next(lo_m, mid_m);
            b_m[i] = rnd.next(mid_m + 1, hi_m);
        } else if (type == 2) {
            // walking dominates (always optimal)
            w_t[i] = rnd.next(lo_t, mid_t);
            b_t[i] = rnd.next(mid_t + 1, hi_t);
            w_m[i] = rnd.next(mid_m + 1, hi_m);
            b_m[i] = rnd.next(lo_m, mid_m);
        } else if (type == 3) {
            // biking dominates (always optimal)
            b_t[i] = rnd.next(lo_t, mid_t);
            w_t[i] = rnd.next(mid_t + 1, hi_t);
            b_m[i] = rnd.next(mid_m + 1, hi_m);
            w_m[i] = rnd.next(lo_m, mid_m);
        } else {
            // fully random
            w_t[i] = rnd.next(lo_t, hi_t);
            b_t[i] = rnd.next(lo_t, hi_t);
            w_m[i] = rnd.next(lo_m, hi_m);
            b_m[i] = rnd.next(lo_m, hi_m);
        }
    }

    // Compute minimal and maximal possible total times
    long long min_sum = 0, max_sum_time = 0;
    for (int i = 0; i < N; i++) {
        min_sum += min(w_t[i], b_t[i]);
        max_sum_time += max(w_t[i], b_t[i]);
    }
    int avg = int((min_sum + max_sum_time) / 2);

    // Choose K mode: tight, medium, or loose
    int K;
    int kmode = rnd.next(0, 2);
    if (kmode == 0) {
        K = int(min_sum);
    } else if (kmode == 1) {
        if (min_sum < avg) K = rnd.next(int(min_sum), avg);
        else K = int(min_sum);
    } else {
        if (avg + 1 <= max_sum_time) K = rnd.next(avg + 1, int(max_sum_time));
        else K = int(max_sum_time);
    }
    // Cap to constraint
    K = min(K, 100000);

    // Output
    println(N, K);
    for (int i = 0; i < N; i++) {
        println(w_t[i], w_m[i], b_t[i], b_m[i]);
    }
    return 0;
}
