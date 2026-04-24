#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int N = rnd.next(1, 10);
    int K = rnd.next(1, N);
    int H = rnd.next(1, 20);
    int W = rnd.next(1, 20);
    // D must be at least 1
    int D = rnd.next(1, 5);

    int cheatHlo = max(1, H - D), cheatHhi = H + D;
    int cheatWlo = max(1, W - D), cheatWhi = W + D;
    double coverRate = rnd.next(); // fraction of rides covering the cheat range

    vector<array<int,4>> rides;
    rides.reserve(N);
    for (int i = 0; i < N; i++) {
        bool cover = (rnd.next() < coverRate);
        int h_lo, h_hi, w_lo, w_hi;
        // height interval
        if (cover) {
            h_lo = rnd.next(cheatHlo, cheatHhi);
            h_hi = rnd.next(h_lo, cheatHhi + rnd.next(0, 3));
        } else {
            bool canBelow = cheatHlo > 1;
            bool chooseBelow = canBelow && (rnd.next() < 0.5);
            if (chooseBelow) {
                int hi_max = cheatHlo - 1;
                h_hi = rnd.next(1, hi_max);
                h_lo = rnd.next(1, h_hi);
            } else {
                int lo_min = cheatHhi + 1;
                int lo_max = cheatHhi + rnd.next(1, 3);
                h_lo = rnd.next(lo_min, lo_max);
                h_hi = rnd.next(h_lo, lo_max + rnd.next(0, 2));
            }
        }
        // weight interval
        if (cover) {
            w_lo = rnd.next(cheatWlo, cheatWhi);
            w_hi = rnd.next(w_lo, cheatWhi + rnd.next(0, 3));
        } else {
            bool canBelowW = cheatWlo > 1;
            bool chooseBelowW = canBelowW && (rnd.next() < 0.5);
            if (chooseBelowW) {
                int hi_max = cheatWlo - 1;
                w_hi = rnd.next(1, hi_max);
                w_lo = rnd.next(1, w_hi);
            } else {
                int lo_min = cheatWhi + 1;
                int lo_max = cheatWhi + rnd.next(1, 3);
                w_lo = rnd.next(lo_min, lo_max);
                w_hi = rnd.next(w_lo, lo_max + rnd.next(0, 2));
            }
        }
        rides.push_back({h_lo, h_hi, w_lo, w_hi});
    }

    // Output the test case
    println(N, K, H, W, D);
    for (auto &r : rides) {
        println(r[0], r[1], r[2], r[3]);
    }
    return 0;
}
